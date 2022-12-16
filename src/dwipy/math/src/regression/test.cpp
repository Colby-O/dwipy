#include <iostream>
#include <random>
#include "dwipy/math/include/regression/CurveFit.h"

// linspace from https://github.com/Eleobert/meth/blob/master/interpolators.hpp
template <typename Container>
auto linspace(typename Container::value_type a, typename Container::value_type b, size_t n)
{
    assert(b > a);
    assert(n > 1);

    Container res(n);
    const auto step = (b - a) / (n - 1);
    auto val = a;
    for(auto& e: res)
    {
        e = val;
        val += step;
    }
    return res;
}


double gaussian(double x, double a)
{
    return a * std::pow(x, 2);
}


int main()
{
    auto device = std::random_device();
    auto gen    = std::mt19937(device());

    auto xs = linspace<std::vector<double>>(0.0, 1.0, 300);
    auto ys = std::vector<double>(xs.size());

    double a = 1.0;

    for(size_t i = 0; i < xs.size(); i++)
    {
        auto y =  gaussian(xs[i], a);
        ys[i] = xs[i] * xs[i] * 10.0;
    }

    auto r = NonLinearRegression::curveFit(gaussian, xs, ys, {1.0});

    std::cout << "result: " << r[0] << ' ' << '\n';
    std::cout << "error : " << r[0] - 10 << ' ' << '\n';

}

