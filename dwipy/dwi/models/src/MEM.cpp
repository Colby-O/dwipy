#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <thread>
#include <cmath>
#include <numeric>
#include "dwipy/dwi/models/include/MEM.h"
#include "dwipy/math/include/regression/LinearRegression.h"

using namespace DWIModels;

void DWIModels::fitMEMSlice(const Image::DWImage4D& img, int i, Image::Image3D& adcMap, Image::Image3D& S0Map, Image::Image3D& chiSquaredMap, std::vector<std::vector<double>>& res) {
    
    std::vector<double> adc;
    std::vector<double> S0;
    std::vector<double> chiSquared;

    for (int j = 0; j < img.getHeight(); ++j) {
        for (int k = 0; k < img.getWidth(); ++k) {
            std::vector<double> bVals;
            std::vector<double> singal;
            for (int imgID = 0; imgID < img.getNumberOfImages(); ++imgID) {
                singal.push_back(img(imgID, i, j, k));
                bVals.push_back(img.getImages()[imgID]->getBValue());
            }

            LinearRegression::Result res = LinearRegression::leastSqaures(bVals, singal);
            // TODO: Move to regression function
            double chiSquaredVal = 0;
            for (int i = 0; i < bVals.size(); ++i) {
                chiSquaredVal += pow(singal[i] - (res.mslope * bVals[i] + res.mintercept), 2) / (res.mslope * bVals[i] + res.mintercept);
            }

            adcMap(i, j, k) =  -res.mslope;
            S0Map(i, j, k) = res.mintercept;
            chiSquaredMap(i, j, k) = chiSquaredVal;

            adc.push_back(-res.mslope);
            S0.push_back(res.mintercept);
            chiSquared.push_back(chiSquaredVal);
        }
    }

    res.push_back(adc);
    res.push_back(S0);
    res.push_back(chiSquared);
}


MEMFitResults DWIModels::fitMEM(const Image::DWImage4D& img, std::string regressionMethod) {
    Image::Image3D adcMap(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D S0Map(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D chiSquaredMap(img.getWidth(), img.getHeight(), img.getSlices());
    
    std::vector<double> adc;
    std::vector<double> S0;
    std::vector<double> chiSquared;

    std::vector<std::vector<std::vector<double>>> workerData(img.getSlices());
    std::vector<std::thread> workers(img.getSlices());

    for (int i = 0; i < img.getSlices(); ++i) {
        workers[i] = std::thread(
            fitMEMSlice, 
            std::ref(img), 
            i,
            std::ref(adcMap),
            std::ref(S0Map),
            std::ref(chiSquaredMap),
            std::ref(workerData[i])
        );
    }

    for (int i = 0; i < workers.size(); ++i) {
        workers[i].join();
        adc.insert(adc.end(), workerData[i][0].begin(), workerData[i][0].end());
        S0.insert(S0.end(), workerData[i][1].begin(), workerData[i][1].end());
        chiSquared.insert(chiSquared.end(), workerData[i][2].begin(), workerData[i][2].end());
    }

    double sumADC = std::accumulate(adc.begin(), adc.end(), 0.0);
    double sumS0 = std::accumulate(S0.begin(), S0.end(), 0.0);
    double sumChiSquared = std::accumulate(chiSquared.begin(), chiSquared.end(), 0.0);

    double avgADC = sumADC / adc.size();
    double avgS0 = sumS0 / S0.size();
    double avgChiSquared = sumChiSquared / chiSquared.size();

    return MEMFitResults(adcMap, S0Map, chiSquaredMap, avgADC, avgS0, avgChiSquared);
}


/*
//                                  Single Threaded Version

MEMFitResults DWIModels::fitMEM(const Image::DWImage4D& img, std::string regressionMethod) {
    Image::Image3D adcMap(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D S0Map(img.getWidth(), img.getHeight(), img.getSlices());
    Image::Image3D chiSquaredMap(img.getWidth(), img.getHeight(), img.getSlices());
    
    std::vector<double> adc;
    std::vector<double> S0;
    std::vector<double> chiSquared;

    for (int i = 0; i < img.getSlices(); ++i) {
        for (int j = 0; j < img.getHeight(); ++j) {
            for (int k = 0; k < img.getWidth(); ++k) {
                std::vector<double> bVals;
                std::vector<double> singal;
                for (int imgID = 0; imgID < img.getNumberOfImages(); ++imgID) {
                    singal.push_back(img(imgID, i, j, k));
                    bVals.push_back(img.getImages()[imgID]->getBValue());
                }

                LinearRegression::Result res = LinearRegression::leastSqaures(bVals, singal);
                // TODO: Move to regression function
                double chiSquaredVal = 0;
                for (int i = 0; i < bVals.size(); ++i) {
                    chiSquaredVal += pow(singal[i] - (res.mslope * bVals[i] + res.mintercept), 2) / (res.mslope * bVals[i] + res.mintercept);
                }

                adcMap(i, j, k) =  -res.mslope;
                S0Map(i, j, k) = res.mintercept;
                chiSquaredMap(i, j, k) = chiSquaredVal;

                adc.push_back(-res.mslope);
                S0.push_back(res.mintercept);
                chiSquared.push_back(chiSquaredVal);
            }
        }
    }

    double sumADC = std::accumulate(adc.begin(), adc.end(), 0.0);
    double sumS0 = std::accumulate(S0.begin(), S0.end(), 0.0);
    double sumChiSquared = std::accumulate(chiSquared.begin(), chiSquared.end(), 0.0);

    double avgADC = sumADC / adc.size();
    double avgS0 = sumS0 / S0.size();
    double avgChiSquared = sumChiSquared / chiSquared.size();

    return MEMFitResults(adcMap, S0Map, chiSquaredMap, avgADC, avgS0, avgChiSquared);
}
*/