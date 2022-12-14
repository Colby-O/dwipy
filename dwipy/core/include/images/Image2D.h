#ifndef IMAGE2D_H_
#define IMAGE2D_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

#include "dwipy/core/include/images/Image.h"

namespace Image {
    class Image2D : public Image {
    protected:
        // Image data (singal)
        double* mData;
        // Image width and height
        int mWidth, mHeight;

        void loadDataFromPyObject(PyObject* obj) override {}
    public:
        // Default Constructor
        Image2D() {}
        Image2D(int width, int height);
        // Constructor initializes image with an array
        Image2D(const double* data, int width, int height) : Image2D(width, height) { loadDataFromArray(data); }
        // Constructor initializes image with a PyObject
        Image2D(PyObject* obj, int width, int height) : Image2D(width, height) { loadDataFromPyObject(obj); }
        // Copy Constructor
        Image2D(const Image2D& image) : Image2D(image.getData(), image.getWidth(), image.getHeight()) {} 

        // Feteches the image width
        int getWidth() const { return mWidth; }
        // Feteches the images height
        int getHeight() const { return mHeight; }

        int getSize() const override { return mWidth * mHeight; }

        PyObject* convertToPyObject() const  { return nullptr; }

        // Operator overloads
        //Image2D operator+ (const Image& other) const;
        //Image2D operator- (const Image& other) const;
        //Image2D operator* (const Image& other) const;
        //Image2D operator* (double scale) const;
        double& operator() (int i, int j) const;

        friend std::ostream& operator<<(std::ostream& os, const Image2D& img) {
            for (int i = 0; i < img.getHeight(); ++i) {
                for (int j = 0; j < img.getWidth(); ++j) {
                    const double val = img(i, j);
                    os << val << " ";
                }
                os << std::endl;
            }

            return os;
        }
    };
}
#endif