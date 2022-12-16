#ifndef IMAGE3D_H_
#define IMAGE3D_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

#include "dwipy/core/include/images/Image.h"

namespace Image {
    class Image3D : public Image {
    protected:
        // number of slices in the image
        int mWidth, mHeight, mSlices;

        /*
            Converts a PyObject into a double array and then set the image data
        */
        void loadDataFromPyObject(PyObject* obj) override;
    public:
        // Default Constructor
        Image3D() {}
        Image3D(int width, int height, int slices);
        // Constructor initializes image with an array
        Image3D(const double* data, int width, int height, int slices) : Image3D(width, height, slices) { loadDataFromArray(data); }
        // Constructor initializes image with a PyObject
        Image3D(PyObject* obj, int width, int height, int slices) : Image3D(width, height, slices) { loadDataFromPyObject(obj); }
        // Copy Constructor
        Image3D(const Image3D& image) : Image3D(image.getData(), image.getWidth(), image.getHeight(), image.getSlices()) {}
        // Move Constructor
        Image3D(Image3D&& image) : mWidth(image.getWidth()), mHeight(image.getHeight()), mSlices(image.getSlices()) {
             mData = image.getData(); 
             image.setData(nullptr);
        }

        // Feteches the number slices in the image
        int getSlices() const { return mSlices; }
        // Feteches the image width
        int getWidth() const { return mWidth; }
        // Feteches the images height
        int getHeight() const { return mHeight; }
        // Gets the image size
        int getSize() const override { return mWidth * mHeight * mSlices; }

        void cbrt();

        // TODO
        //Image2D getSliceAt(int slice);

        PyObject* convertToPyObject() const override;

        // Operator overloads
        Image3D operator+ (const Image3D& other) const;
        Image3D operator+ (const double constant) const;
        Image3D& operator+= (const Image3D& other);
        Image3D& operator+= (const double constant);
        Image3D operator- (const Image3D& other) const;
        Image3D operator- (const double constant) const;
        Image3D& operator-= (const Image3D& other);
        Image3D& operator-= (const double constant);
        Image3D operator* (const Image3D& other) const;
        Image3D operator* (const double scale) const;
        Image3D& operator*= (const Image3D& other);
        Image3D& operator*= (const double scale);
        Image3D& operator= (const Image3D& in); // l-values
        Image3D& operator= (Image3D&& in); // r-values --must prevent deallocation of data
        double& operator() (int i, int j, int k) const;

        friend std::ostream& operator<<(std::ostream& os, const Image3D& img) {
            for (int i = 0; i < img.getSlices(); ++i) {
                for (int j = 0; j < img.getHeight(); ++j) {
                    for (int k = 0; k < img.getWidth(); ++k) {
                        const double val = img(i, j, k);
                        os << val << " ";
                    }
                    os << std::endl;
                }
                os <<  "\n\n";
            }

            return os;
        }
    };
}
#endif