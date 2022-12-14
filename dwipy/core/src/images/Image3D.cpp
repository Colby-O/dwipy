#include <cmath>
#include "dwipy/core/include/images/Image3D.h"

using namespace Image;

// C++ Function definitions
Image3D::Image3D(int width, int height, int slices) {
    mWidth  = width;
    mHeight = height;
    mSlices = slices;
    mData = new double[mWidth * mHeight * mSlices];

    for (int i = 0; i < getSize(); ++i) {
        mData[i] = 0;
    }
}

void Image3D::loadDataFromPyObject(PyObject* obj) {
    assert(PyList_Check(obj));
    for (Py_ssize_t i = 0; i < PyList_Size(obj); ++i) {
        PyObject* slice = PyList_GetItem(obj, i);
        for (Py_ssize_t j = 0; j < PyList_Size(slice); ++j) {
            PyObject* row = PyList_GetItem(slice, j);
            for (Py_ssize_t k = 0; k < PyList_Size(row); ++k) {
                PyObject* voxel = PyList_GetItem(row, k);
                double voxelValue = PyFloat_AsDouble(voxel);
                (*this)(k, j, i) = voxelValue;
            }
        }
    }
}

PyObject* Image3D::convertToPyObject() const {
    assert(mData != nullptr);
    PyObject* image = PyList_New(mWidth);
    for (Py_ssize_t i = 0; i < mWidth; ++i) {
        PyObject* slice = PyList_New(mHeight);
        for (Py_ssize_t j = 0; j < mHeight; ++j) {
            PyObject* row = PyList_New(mSlices);
            for (Py_ssize_t k = 0; k < mSlices; ++k) {
                PyObject* voxelValue = PyFloat_FromDouble((*this)(k, j, i));
                PyList_SetItem(row, k, voxelValue);
            }
            PyList_SetItem(slice, j, row);
        }
        PyList_SetItem(image, i, slice);
    }

    return image;
};

Image3D Image3D::operator+ (const Image3D& other) const {
    assert(other.getHeight() == mHeight);
    assert(other.getWidth() == mWidth);
    assert(other.getSlices() == mSlices);

    Image3D res(mWidth, mHeight, mSlices);

    double* otherData = other.getData();
    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] + otherData[i];
    }

    return res;
}

Image3D Image3D::operator+ (double constant) const {
    Image3D res(mWidth, mHeight, mSlices);

    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] + constant;
    }

    return res;
}

Image3D& Image3D::operator+= (const Image3D& other) {
    double* otherData = other.getData();
    for (int i = 0; i < getSize(); ++i) {
        mData[i] += otherData[i];
    }

    return *this;
}

Image3D& Image3D::operator+= (const double other) {
    for (int i = 0; i < getSize(); ++i) {
        mData[i] += other;
    }

    return *this;
}

Image3D Image3D::operator- (const Image3D& other) const {
    assert(other.getHeight() == mHeight);
    assert(other.getWidth() == mWidth);
    assert(other.getSlices() == mSlices);

    Image3D res(mWidth, mHeight, mSlices);

    double* otherData = other.getData();
    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] - otherData[i];
    }

    return res;
}

Image3D Image3D::operator- (double constant) const {
    Image3D res(mWidth, mHeight, mSlices);

    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] - constant;
    }

    return res;
}

Image3D& Image3D::operator-= (const Image3D& other) {
    assert(other.getHeight() == mHeight);
    assert(other.getWidth() == mWidth);
    assert(other.getSlices() == mSlices);

    double* otherData = other.getData();

    for (int i = 0; i < getSize(); ++i) {
        mData[i] -= otherData[i];
    }

    return *this;
}

Image3D& Image3D::operator-= (double constant) {
    for (int i = 0; i < getSize(); ++i) {
        mData[i] -= constant;
    }

    return *this;
}

Image3D Image3D::operator* (const Image3D& other) const {
    assert(other.getHeight() == mHeight);
    assert(other.getWidth() == mWidth);
    assert(other.getSlices() == mSlices);

    Image3D res(mWidth, mHeight, mSlices);

    double* otherData = other.getData();
    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] * otherData[i];
    }

    return res;
}

Image3D& Image3D::operator*= (const Image3D& other) {
    assert(other.getHeight() == mHeight);
    assert(other.getWidth() == mWidth);
    assert(other.getSlices() == mSlices);

    double* otherData = other.getData();

    for (int i = 0; i < getSize(); ++i) {
        mData[i] *= otherData[i];
    }

    return *this;
}

Image3D Image3D::operator* (double scale) const {
    Image3D res(mWidth, mHeight, mSlices);

    double* resData = res.getData();

    for (int i = 0; i < getSize(); ++i) {
        resData[i] = mData[i] * scale;
    }

    return res;
}

Image3D& Image3D::operator*= (double scale) {
    for (int i = 0; i < getSize(); ++i) {
        mData[i] *= scale;
    }

    return *this;
}

Image3D& Image3D::operator= (const Image3D& in) {
    if (mData != nullptr) {
        delete[] mData;
    }
    
    mWidth = in.getWidth();
    mHeight = in.getHeight();
    mSlices = in.getSlices();

    mData = new double[mWidth * mHeight * mSlices];
    
    this->loadDataFromArray(in.getData());

    return *this;
}

Image3D& Image3D::operator= (Image3D&& in) {
    this->setData(in.getData());

    mWidth = in.getWidth();
    mHeight = in.getHeight();
    mSlices = in.getSlices();

    in.setData(nullptr);

    return *this;
}

double& Image3D::operator() (int i, int j, int k) const {
    assert(i < mSlices);
    assert(j < mHeight);
    assert(k < mWidth);

    return mData[i * mWidth * mHeight + j * mWidth + k];
}

void Image3D::cbrt() {
    for (int i = 0; i < getSize(); ++i) {
        mData[i] = std::cbrt(mData[i]);
    }
}