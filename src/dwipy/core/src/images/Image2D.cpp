#include "dwipy/core/include/images/Image2D.h"

using namespace Image;

Image2D::Image2D(int width, int height) {
    mWidth  = width;
    mHeight = height;
    mData = new double[mWidth];

    std::fill_n(mData, mWidth, 0); 
}

double& Image2D::operator() (int i, int j) const {
    assert(i < mHeight);
    assert(j < mWidth);

    return mData[i * mWidth + j];
}