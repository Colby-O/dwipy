#include <cstdlib>
#include <vector>
#include <numeric>
#include <cassert>
#include <cmath>
#include "dwipy/math/include/regression/LinearRegression.h"

using namespace LinearRegression;

Result LinearRegression::leastSqaures(const std::vector<double>& x, const std::vector<double>& y) {
    // Check if the depandent variable and response variable are of equal size
    assert(x.size() == y.size());

    // Store the total number of data point in the fit
    int N = x.size();

    // Finds the sum and mean of the depandant variable
    double xsum = std::accumulate(x.begin(), x.end(), 0.0);
    double xmean =  xsum / N;

    // Finds the sum and mean of the response variable
    double ysum = std::accumulate(y.begin(), y.end(), 0.0);
    double ymean =  ysum / N;

    // Compute the co-varience matrix elements
    double ssym = 0;
    double ssxm = 0;
    double ssxym = 0;

    // Sums varience 
    for (int i = 0 ; i < N; ++i) {
        ssym += pow(y[i] - ymean, 2.0);
        ssxm += pow(x[i] - xmean, 2.0);
        ssxym += (y[i] - ymean) * (x[i] - xmean);
    }
    
    // Compute mean varience
    ssym /= N;
    ssxm /= N;
    ssxym /= N;

    // Calculate the slope and intercept
    double slope = ssxym / ssxm;
    double intercept = ymean - slope * xmean;

    // Calculate R-value
    double r = (ssxm == 0 && ssym == 0) ? 0 : ssxym / sqrt(ssxm * ssym);
    // Caps the R-value bewteen -1 < R < R
    r = (r > 1.0) ? 1.0  : r;
    r = (r < -1.0) ? -1.0 : r; 

    // Computes the Degrees of Freedom
    int df = N - 2;

    // Computes the slopes standard error
    double slopeStderr = sqrt((1 - pow(r,2.0)) * ssym / ssxm / df);

    // Computes the intercept standard error
    double interceptStderr = slopeStderr * sqrt(ssxm + pow(xmean, 2.0));

    // Constructs a Linear Regression Result
    Result res(slope, intercept, r, slopeStderr, interceptStderr);
    
    return res;
}

/*
Result LinearRegression::leastTrimmedSqaured(std::vector<double> x, std::vector<double> y, float alpha) {
    

    return Result(0, 0, 0, 0, 0);
}

int main() {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector<double> y = {10.0, 9.4, 8.3, 7.0, 6.2, 5.3, 4.9, 3.3};
    for (int i = 0; i < 100000; ++i) {
        Result res = leastSqaures(x, y);
    }
    //std::cout << res << std::endl;
    return 0;
}
*/
