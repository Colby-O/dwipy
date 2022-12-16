#ifndef DWIMAGE_H_
#define DWIMAGE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

#include "dwipy/core/include/images/Image3D.h"
#include "dwipy/math/include/linalg/Vector3.h"

namespace Image {
    class DWImage : public Image3D {
    protected:
        // Stores the images b-value
        double mBValue;
        // Stores the diffusion direction
        linalg::Vector3<double> mDiffusionDirection;
    public:
        // Default Constructor
        DWImage(int width, int height, int slices, double bValue, linalg::Vector3<double> diffusionDirection) : Image3D(width, height, slices) { mBValue = bValue; mDiffusionDirection =  diffusionDirection;}
        DWImage(int width, int height, int slices, double bValue) : Image3D(width, height, slices) { mBValue = bValue; }
        // Constructor initializes image with an array
        DWImage(const double* data, int width, int height, int slices, double bValue, linalg::Vector3<double> diffusionDirection) : DWImage(width, height, slices, bValue, diffusionDirection) { loadDataFromArray(data); }
        DWImage(const double* data, int width, int height, int slices, double bValue) : DWImage(width, height, slices, bValue) { loadDataFromArray(data); }
        // Constructor initializes image with a PyObject
        DWImage(PyObject* obj, int width, int height, int slices, double bValue, linalg::Vector3<double> diffusionDirection) : DWImage(width, height, slices, bValue, diffusionDirection) { loadDataFromPyObject(obj); }
        DWImage(PyObject* obj, int width, int height, int slices, double bValue) : DWImage(width, height, slices, bValue) { loadDataFromPyObject(obj); }
        // Copy Constructor
        DWImage(const DWImage& other) : DWImage(other.getData(), other.getWidth(), other.getHeight(), other.getSlices(), other.getBValue(), other.getDiffusionDirection()) {} 
        // Move Constructor
        DWImage(DWImage&& image) : mBValue(image.getBValue()), mDiffusionDirection(image.getDiffusionDirection()) {
            mWidth = image.getWidth();
            mHeight = image.getHeight();
            mSlices = image.getSlices();
            mData = image.getData(); 
            image.setData(nullptr);
        }

        // Getters
        double getBValue() const { return mBValue; };
        linalg::Vector3<double> getDiffusionDirection() const {return mDiffusionDirection; }

        // Setters
        void setBValue(double bValue) { mBValue = bValue; };
        void setDiffusionDirection(linalg::Vector3<double> diffusionDirection) { mDiffusionDirection = diffusionDirection; }
    };
}
#endif