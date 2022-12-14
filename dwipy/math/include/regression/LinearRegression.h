#ifndef LINEARREGRESSION_H_
#define LINEARREGRESSION_H_

#include <iostream>

namespace LinearRegression {
    struct Result {
        double mslope, mintercept, mrvalue, mslopeStderr, minterceptStderr;

        Result(double slope, double intercept, double rvalue, double slopeStderr, double interceptStderr) {
            mslope = slope;
            mintercept = intercept;
            mrvalue = rvalue;
            mslopeStderr = slopeStderr;
            minterceptStderr = interceptStderr;
        }

        friend std::ostream& operator<<(std::ostream& os, const Result& res) {
            os << "Slope: " << res.mslope 
            << "\nIntercept: " << res.mintercept 
            << "\nR-Value: " << res.mrvalue 
            << "\nSlope stderr: " << res.mslopeStderr 
            << "\nIntercept stderr: " << res.minterceptStderr 
            << std::endl;

            return os;
        }
    }; 

    Result leastSqaures(const std::vector<double>& x, const std::vector<double>& y);

    Result weightedLeastSqaures(const std::vector<double>& x, const std::vector<double>& y);

    Result leastTrimmedSqaured(const std::vector<double>& x, const std::vector<double>& y, float alpha);
}

#endif
