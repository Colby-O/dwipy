#include <thread>
#include <cmath>
#include <numeric>
#include "dwipy/dwi/models/include/IVIM.h"
#include "dwipy/math/include/regression/CurveFit.h"

using namespace DWIModels;

double DWIModels::ivim(double b, double S, double ADC, double D, double f) {
    return S * (f * std::exp(-b * (ADC + D)) + (1 - f) * std::exp(-b * ADC));
}

void DWIModels::fitIVIMSlice(const Image::DWImage4D& img, int i, Image::Image3D& adcMap, Image::Image3D& dMap, Image::Image3D& fMap, Image::Image3D& S0Map, Image::Image3D& chiSquared) {
    for (int j = 0; j < img.getHeight(); ++j) {
        for (int k = 0; k < img.getWidth(); ++k) {
            std::vector<double> bVals;
            std::vector<double> singal;
            for (int imgID = 0; imgID < img.getNumberOfImages(); ++imgID) {
                singal.push_back(img(imgID, i, j, k));
                bVals.push_back(img.getImages()[imgID]->getBValue());
            }

            std::vector<double> res = NonLinearRegression::curveFit(ivim, bVals, singal, {singal[0], 1e-5, 1e-5, 0.5});
             // TODO: Move to regression function
             double chiSquaredVal = 0;
             for (int i = 0; i < bVals.size(); ++i) {
                 chiSquaredVal += pow(singal[i] - ivim(bVals[i], res[0], res[1], res[2], res[3]), 2) / ivim(bVals[i], res[0], res[1], res[2], res[3]);
             }

            adcMap(i, j, k) =  res[1];
            S0Map(i, j, k) = res[0];
            dMap(i, j, k) = res[2];
            fMap(i, j, k) = res[3];
            chiSquared(i, j, k) = chiSquaredVal;
        }
    }
}

DWIModels::IVIMFitResults DWIModels::fitIVIM(const Image::DWImage4D& img) {
    Image::Image3D adcMap(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D S0Map(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D dMap(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D fMap(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D chiSquaredMap(img.getWidth(), img.getHeight(), img.getSlices());
    
    std::vector<double> adc;
    std::vector<double> S0;
    std::vector<double> chiSquared;

    //std::vector<std::vector<std::vector<double>>> workerData(img.getSlices());
    std::vector<std::thread> workers(img.getSlices());

    for (int i = 0; i < img.getSlices(); ++i) {
        workers[i] = std::thread(
            fitIVIMSlice, 
            std::ref(img), 
            i,
            std::ref(adcMap),
            std::ref(dMap),
            std::ref(fMap),
            std::ref(S0Map),
            std::ref(chiSquaredMap)
        );
    }

    for (int i = 0; i < workers.size(); ++i) {
        workers[i].join();
        // adc.insert(adc.end(), workerData[i][0].begin(), workerData[i][0].end());
        // S0.insert(S0.end(), workerData[i][1].begin(), workerData[i][1].end());
        // chiSquared.insert(chiSquared.end(), workerData[i][2].begin(), workerData[i][2].end());
    }

    // double sumADC = std::accumulate(adc.begin(), adc.end(), 0.0);
    // double sumS0 = std::accumulate(S0.begin(), S0.end(), 0.0);
    // double sumChiSquared = std::accumulate(chiSquared.begin(), chiSquared.end(), 0.0);

    // double avgADC = sumADC / adc.size();
    // double avgS0 = sumS0 / S0.size();
    // double avgChiSquared = sumChiSquared / chiSquared.size();

    return IVIMFitResults(adcMap, dMap, fMap, S0Map, chiSquaredMap);
}