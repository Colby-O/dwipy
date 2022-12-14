#include <cmath>
#include <algorithm>
#include "dwipy/core/include/images/DWImage4D.h"

Image::DWImage4D Image::generateTraceWeightedDWImage4D(const DWImage4D& img) {
    DWImage4D traceImage4D(img.getWidth(), img.getHeight(), img.getSlices());
    std::vector<double> bVals = img.getBValues();
    auto last = std::unique(bVals.begin(), bVals.end()); 
    bVals.erase(last, bVals.end());

    for (auto& bVal : bVals) {
        if (bVal == 0) {
            std::vector<DWImage*> b0Images = img.getImages(bVal);

            assert(b0Images.size() == 1);
            
            traceImage4D.appendDWI(std::move(*b0Images[0]));

            continue;
        }
    
        std::vector<DWImage*> xImages = img.getImages(bVal, linalg::Vector3<double>(1, 0, 0));
        std::vector<DWImage*> yImages = img.getImages(bVal, linalg::Vector3<double>(0, 1, 0));
        std::vector<DWImage*> zImages = img.getImages(bVal, linalg::Vector3<double>(0, 0, 1));

        assert(xImages.size() == 1);
        assert(yImages.size() == 1);
        assert(zImages.size() == 1);

        DWImage traceImage = *xImages[0];
        traceImage *= *yImages[0];
        traceImage *= *zImages[0];

        traceImage.cbrt();

        traceImage.setDiffusionDirection(linalg::Vector3<double>(0, 0, 0));

        traceImage4D.appendDWI(std::move(traceImage));
    }

    return traceImage4D;
}

double* Image::DWImage4D::loadDataFromPyObject(PyObject* obj, int numImages) {
    assert(PyList_Check(obj));
    double* data = new double[numImages * mWidth * mHeight * mSlices];
    for (Py_ssize_t i = 0; i < PyList_Size(obj); ++i) {
        PyObject* img = PyList_GetItem(obj, i);
        for (Py_ssize_t j = 0; j < PyList_Size(img); ++j) {
            PyObject* slice = PyList_GetItem(img, j);
            for (Py_ssize_t k = 0; k < PyList_Size(slice); ++k) {
                PyObject* row = PyList_GetItem(slice, k);
                for (Py_ssize_t l = 0; l < PyList_Size(row); ++l) {
                    PyObject* voxel = PyList_GetItem(row, l);
                    double voxelValue = PyFloat_AsDouble(voxel);
                    data[l * mWidth * mHeight * mSlices + k * mWidth * mHeight + j * mWidth + i] = voxelValue;
                }
            }
        }
    }

    return data;
}

PyObject* Image::DWImage4D::convertToPyObject() const {
    assert(mImages.size() != 0);
    PyObject* image4D = PyList_New(mWidth);
    for (Py_ssize_t i = 0; i < mWidth; ++i) {
        PyObject* image = PyList_New(mHeight);
        for (Py_ssize_t j = 0; j < mHeight; ++j) {
            PyObject* slice = PyList_New(mSlices);
            for (Py_ssize_t k = 0; k < mSlices; ++k) {
            PyObject* row = PyList_New(mImages.size());
                for (Py_ssize_t l = 0; l < mImages.size(); ++l) {
                    PyObject* voxelValue = PyFloat_FromDouble((*mImages[l].get())(k, j, i));
                    PyList_SetItem(row, l, voxelValue);
                }
                PyList_SetItem(slice, k, row);
            }
            PyList_SetItem(image, j, slice);
        }
        PyList_SetItem(image4D, i, image);
    }

    return image4D;
};

Image::DWImage4D::DWImage4D(const double* data, std::vector<double> bValues, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages) 
: mWidth(width), mHeight(height), mSlices(slices) {
    assert(bValues.size() == numImages);
    assert(diffusionDirections.size() == numImages);
    for (int i = 0; i < numImages; ++i) {
        mImages.push_back(std::make_unique<DWImage>(&data[i * width * height * slices], width, height, slices, bValues[i], diffusionDirections[i]));
    }
}

Image::DWImage4D::DWImage4D(PyObject* obj, std::vector<double> bValues, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages)
: mWidth(width), mHeight(height), mSlices(slices)  {
    assert(bValues.size() == numImages);
    assert(diffusionDirections.size() == numImages);
    double* data = loadDataFromPyObject(obj, numImages);

    for (int i = 0; i < numImages; ++i) {
        mImages.push_back(std::make_unique<DWImage>(&data[i * width * height * slices], width, height, slices, bValues[i], diffusionDirections[i]));
    }

    delete[] data;
}

Image::DWImage4D::DWImage4D(std::vector<DWImage*> images) {
    for (int i = 0; i < images.size(); ++i) {
        mImages.push_back(std::make_unique<DWImage>(*images[i]));
    }
}

std::vector<Image::DWImage*> Image::DWImage4D::getImages(double bValue) const {
    std::vector<DWImage*> newImages;

    for (auto&  dwImage : mImages) {
        if (dwImage->getBValue() == bValue) {
            newImages.push_back(dwImage.get());
        }
    }

    return newImages;
}

std::vector<Image::DWImage*> Image::DWImage4D::getImages(linalg::Vector3<double> diffusionDirection) const {
    std::vector<DWImage*> newImages;

    for (auto&  dwImage : mImages) {
        if (dwImage->getDiffusionDirection() == diffusionDirection) {
            newImages.push_back(dwImage.get());
        }
    }

    return newImages;
}

std::vector<Image::DWImage*> Image::DWImage4D::getImages(double bValue, linalg::Vector3<double> diffusionDirection) const{
    std::vector<DWImage*> newImages;

    for (auto&  dwImage : mImages) {
        if (dwImage->getDiffusionDirection() == diffusionDirection && dwImage->getBValue() == bValue) {
            newImages.push_back(dwImage.get());
        }
    }

    return newImages;
}

std::vector<double> Image::DWImage4D::getBValues() const {
    std::vector<double> bValues;

    for (auto&  dwImage : mImages) {
        bValues.push_back(dwImage->getBValue());
    }

    return bValues;

}

std::vector<double> Image::DWImage4D::getBValues(linalg::Vector3<double> diffusionDirection) const {
    std::vector<double> bValues;

    for (auto&  dwImage : mImages) {
        if (diffusionDirection == dwImage->getDiffusionDirection()) {
            bValues.push_back(dwImage->getBValue());
        }
    }

    return bValues;

}

std::vector<linalg::Vector3<double>>Image::DWImage4D::getDiffusionDirections() const {
     std::vector<linalg::Vector3<double>> diffusionDirections;

    for (auto&  dwImage : mImages) {
        diffusionDirections.push_back(dwImage->getDiffusionDirection());
    }

    return diffusionDirections;
}

std::vector<linalg::Vector3<double>> Image::DWImage4D::getDiffusionDirections(double bValue) const {
    std::vector<linalg::Vector3<double>> diffusionDirections;

    for (auto&  dwImage : mImages) {
        if (bValue == dwImage->getBValue()) {
            diffusionDirections.push_back(dwImage->getDiffusionDirection());
        }
    }

    return diffusionDirections;  
}

void Image::DWImage4D::appendDWI(const DWImage& image) {
    assert(mWidth == image.getWidth());
    assert(mHeight == image.getHeight());
    assert(mSlices == image.getSlices());

    mImages.push_back(std::make_unique<DWImage>(image));
}

void Image::DWImage4D::appendDWI(DWImage&& image) {
    assert(mWidth == image.getWidth());
    assert(mHeight == image.getHeight());
    assert(mSlices == image.getSlices());

    mImages.push_back(std::make_unique<DWImage>(image));
}