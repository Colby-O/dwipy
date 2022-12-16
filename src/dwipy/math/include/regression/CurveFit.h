#ifndef CURVEFIT_H_
#define CURVEFIT_H_

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multifit_nlinear.h>

#include <vector>
#include <cassert>
#include <functional>

namespace NonLinearRegression {
    template<typename Func>
    struct fitData {
        const std::vector<double>& x;
        const std::vector<double>& y;
        Func f;
    };

    using func_f_type = int (*) (const gsl_vector*, void*, gsl_vector*);
    using func_df_type = int (*) (const gsl_vector*, void*, gsl_matrix*);
    using func_fvv_type = int (*) (const gsl_vector*, const gsl_vector*, void*, gsl_vector*);

    gsl_vector* makeGSLVector(const std::vector<double>& vec);
    std::vector<double> solveSystem(gsl_vector* p0, gsl_multifit_nlinear_fdf* fdf, gsl_multifit_nlinear_parameters* params);

    template<typename Func, class... Args>
    struct functionRipper {
        static constexpr size_t n_args = sizeof...(Args);
    };

    template<typename Func, class... Args>
    auto getNumberOfParams(std::function<Func (Args...)>) {
        return functionRipper<Func, Args...>();
    }

     template<typename Func, class... Args>
    auto getNumberOfParams(Func (Args...)) {
        return functionRipper<Func, Args...>();
    }

    template<typename Func, size_t... Is>
    auto generateTuple(Func f, std::index_sequence<Is...>) {
        return std::make_tuple(f(Is)...);
    }

    template<size_t N, typename Func>
    auto gslToTuple(Func f) {
        return generateTuple(f, std::make_index_sequence<N>{});
    }

    template<typename FitData, int numParams>
    int gslFunction(const gsl_vector* x, void* params, gsl_vector* f) {
        FitData* data = static_cast<FitData*>(params);

        auto p0 = [x](int i) {
            return gsl_vector_get(x, i);
        };

        auto parameters = gslToTuple<numParams>(p0);

        for (size_t i = 0; i < data->x.size(); ++i) {
            double xi = data->x[i];
            double yi = data->y[i];
            auto func = [xi, &data](auto ...xs) {
                return data->f(xi, xs...);
            };
            auto y = std::apply(func, parameters);
            gsl_vector_set(f, i, yi - y);
        }

        return GSL_SUCCESS;
    }

    template<typename T>
    std::vector<double> gslCurveFit(func_f_type f, func_df_type df, func_fvv_type fvv, gsl_vector* p0, fitData<T>& fd) {
        assert(fd.x.size() == fd.y.size());

        gsl_multifit_nlinear_fdf fdf = gsl_multifit_nlinear_fdf();
        gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();

        fdf.f = f;
        fdf.df = df;
        fdf.fvv = fvv;
        fdf.n = fd.x.size();
        fdf.p = p0->size;
        fdf.params = &fd;

        // Nonlinear Least-Sqaures method: Levenberg-Marquart with Geodesic Accerlation
        fdf_params.trs = gsl_multifit_nlinear_trs_lmaccel;
        return solveSystem(p0, &fdf, &fdf_params);
    }


    template<typename Func> 
    std::vector<double> curveFit(Func f, const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& p0) {
        constexpr int N = decltype(getNumberOfParams(std::function(f)))::n_args - 1;

        assert(p0.size() == N);

        gsl_vector* params = makeGSLVector(p0);

        fitData fd = fitData<Func>{x, y, f};

        return gslCurveFit(gslFunction<decltype(fd), N>, nullptr, nullptr, params, fd);
    }
}

#endif