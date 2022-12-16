#ifndef IMAGE_H_
#define IMAGE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

#include "dwipy/core/include/generic/Object.h"


namespace Image {
    struct MRIParameters {
        std::string pulseSequence;
        double TE, TR, flipAngle;
        double epiFactor;
        double echoSpacing;
        double PESteps, FESteps;
        //lignalg::Vector PEDirection;
        //linalg::Vector FEDirection;
    };

    class Image : public ObjectManger::Object {
    protected:
        double* mData = nullptr;
        MRIParameters mParams;

        virtual void loadDataFromPyObject(PyObject* obj) = 0;
        /*
            Sets the image data from a C++ double array
        */
        void loadDataFromArray(const double* data) {
            for (int i = 0; i < this->getSize(); ++i) {
                mData[i] = data[i];
            }
        }
    public:
        virtual ~Image() { if (mData != nullptr) { delete[] mData; } }

        double* getData() const { return mData; }
        MRIParameters getMRIParameters() const { return mParams; }
        virtual int getSize() const = 0;

        void setMRIParameters(MRIParameters params) { mParams = params; }
        void setData(double* data) { mData = data; }
        
        virtual PyObject* convertToPyObject() const = 0;
    };
}
#endif