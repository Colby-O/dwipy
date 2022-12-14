#include "dwipy/math/include/regression/CurveFit.h"

using namespace NonLinearRegression;

std::vector<double> NonLinearRegression::solveSystem(gsl_vector* p0, gsl_multifit_nlinear_fdf* fdf, gsl_multifit_nlinear_parameters* params) {
    const gsl_multifit_nlinear_type* T = gsl_multifit_nlinear_trust;
    const size_t maxIter = 200;
    const double xtol = 1.0e-8;
    const double gtol = 1.0e-8;
    const double ftol = 1.0e-8;

    auto* work = gsl_multifit_nlinear_alloc(T, params, fdf->n, fdf->p);
    int info;

    gsl_multifit_nlinear_init(p0, fdf, work);
    gsl_multifit_nlinear_driver(maxIter, xtol, gtol, ftol, nullptr, nullptr, &info, work);

    gsl_vector* y = gsl_multifit_nlinear_position(work);
    std::vector<double> res = std::vector<double>(p0->size);

    for (int i = 0; i < res.size(); ++i) {
        res[i] = gsl_vector_get(y, i);
    }

    size_t niter = gsl_multifit_nlinear_niter(work);
    size_t nfev = fdf->nevalf;
    size_t njev = fdf->nevaldf;
    size_t naev = fdf->nevalfvv;

    gsl_multifit_nlinear_free(work);
    gsl_vector_free(p0);

    return res;
}

gsl_vector* NonLinearRegression::makeGSLVector(const std::vector<double>& vec) {
    gsl_vector* gslVec = gsl_vector_alloc(vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        gsl_vector_set(gslVec, i, vec[i]);
    }
    return gslVec;
}