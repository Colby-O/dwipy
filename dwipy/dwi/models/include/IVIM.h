#ifndef IVIM_H_
#define IVIM_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <vector>

#include "dwipy/core/include/images/Image3D.h"
#include "dwipy/core/include/images/DWImage.h"
#include "dwipy/core/include/images/DWImage4D.h"

namespace DWIModels {
    struct IVIMFitResults {
        Image::Image3D adcMap;
        Image::Image3D dMap;
        Image::Image3D fMap;
        Image::Image3D s0Map;
        Image::Image3D chiSquaredMap;

        IVIMFitResults(Image::Image3D adcMap, Image::Image3D dMap, Image::Image3D fMap, Image::Image3D s0Map, Image::Image3D chiSquaredMap) {
            this->adcMap = adcMap;
            this->dMap = dMap;
            this->fMap = fMap;
            this->s0Map = s0Map;
            this->chiSquaredMap = chiSquaredMap;
        }
    };

    double ivim(double b, double S, double ADC, double D, double f);
    void fitIVIMSlice(const Image::DWImage4D& img, int i, Image::Image3D& adcMap, Image::Image3D& dMap, Image::Image3D& fMap, Image::Image3D& S0Map, Image::Image3D& chiSquared);
    IVIMFitResults fitIVIM(const Image::DWImage4D& img);

}


#endif