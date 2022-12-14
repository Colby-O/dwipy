#ifndef MEM_H_
#define MEM_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <vector>

#include "dwipy/core/include/images/Image3D.h"
#include "dwipy/core/include/images/DWImage.h"
#include "dwipy/core/include/images/DWImage4D.h"

namespace DWIModels {
    // Stores the fit results
    struct MEMFitResults;
    // Place ROI in sperate file
    //class ROI;

    void fitMEMSlice(const Image::DWImage4D& img, int i, Image::Image3D& adcMap, Image::Image3D& S0Map, Image::Image3D& chiSquaredMap, std::vector<std::vector<double>>& res);
    // Fits the MEM model to the whole DWI image
    MEMFitResults fitMEM(const Image::DWImage4D& img, std::string regressionMethod);
    // Fits the MEM model to the whole DWI image but calcuates seperate stats within the ROI
    //MEMFitResults fitMEM(const DWImage4D& DWISet, ROI roi, std::string regressionMethod);
    // Fits the MEM model only to a ROI
    //MEMFitResults roiFitMEM(const DWImage4D& DWISet, ROI roi, std::string regressionMethod);
}

struct DWIModels::MEMFitResults {
    Image::Image3D adcMap;
    Image::Image3D s0Map;
    Image::Image3D chiSquaredMap;

    double avgChiSqaured, stdChiSquared;
    double avgADC, stdADC;
    double avgS0, stdS0;

    MEMFitResults(Image::Image3D adcMap, Image::Image3D s0Map, Image::Image3D chiSquaredMap, double avgADC, double avgS0, double avgChiSqaured) {
        this->adcMap = adcMap;
        this->s0Map = s0Map;
        this->chiSquaredMap = chiSquaredMap;
        this->avgADC = avgADC;
        this->avgS0 = avgS0;
        this->avgChiSqaured = avgChiSqaured;
        this->stdADC = 0.0;
        this->stdS0 = 0.0;
        this->stdChiSquared = 0.0;
    }
};

#endif
