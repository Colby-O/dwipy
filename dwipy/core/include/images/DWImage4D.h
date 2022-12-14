#ifndef DWIMAGE4D_H_
#define DWIMAGE4D_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <memory>
#include <vector>

#include "dwipy/core/include/generic/Object.h"
#include "dwipy/core/include/images/DWImage.h"
#include "dwipy/math/include/linalg/Vector3.h"

namespace Image {

    class DWImage4D;

    DWImage4D generateTraceWeightedDWImage4D(const DWImage4D& img);

    class DWImage4D : public ObjectManger::Object {
    private:
        std::vector<std::unique_ptr<DWImage>> mImages;
        int mWidth, mHeight , mSlices;

        double* loadDataFromPyObject(PyObject* obj, int numImages);
    public:
        DWImage4D () {}
        DWImage4D (int width, int height, int slices) : mWidth(width), mHeight(height), mSlices(slices) {}
        DWImage4D (const double* data, std::vector<double> bValues, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages);
        DWImage4D (PyObject* obj, std::vector<double> bValues, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages);
        DWImage4D(std::vector<DWImage*> images);
        DWImage4D (const DWImage4D& image) : mWidth(image.getWidth()), mHeight(image.getHeight()), mSlices(image.getSlices()) {
            for (auto& img : image.getImages()) {
                appendDWI(*img);
            }
        }
        DWImage4D (DWImage4D&& image) : mWidth(image.getWidth()), mHeight(image.getHeight()), mSlices(image.getSlices()) {
            for (auto& img : image.getImages()) {
                mImages.push_back(std::move(img));
            }
        }

        ~DWImage4D () {}
        
        PyObject* convertToPyObject() const;

        const std::vector<std::unique_ptr<DWImage>>& getImages() const { return mImages; }
        std::vector<std::unique_ptr<DWImage>>& getImages() { return mImages; }
        std::vector<DWImage*> getImages(double bValue) const;
        std::vector<DWImage*> getImages(linalg::Vector3<double> diffusionDirection) const;
        std::vector<DWImage*> getImages(double bValue, linalg::Vector3<double> diffusionDirection) const;

        int getNumberOfImages() const { return mImages.size(); }
        int getWidth() const { return mWidth; }
        int getHeight() const { return mHeight; }
        int getSlices() const { return mSlices; }
        int getSize() const { return mSlices * mHeight * mWidth * getNumberOfImages(); }

        std::vector<double> getBValues() const;
        std::vector<double> getBValues(linalg::Vector3<double> diffusionDirection) const;

        std::vector<linalg::Vector3<double>> getDiffusionDirections() const;
        std::vector<linalg::Vector3<double>> getDiffusionDirections(double bValue) const;

        void appendDWI(const DWImage& image);
        void appendDWI(DWImage&& image);

        double& operator()(int imgID, int s, int h, int w) const {
            return (*mImages[imgID])(s, h, w);
        }
    };
}
#endif