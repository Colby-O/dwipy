#ifndef DWIMAGEINTERFACE_H_
#define DWIMAGEINTERFACE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "dwipy/core/include/images/DWImage.h"
#include "dwipy/core/include/generic/Object.h"

namespace Image {
    unsigned int create_dwimage(int width, int height, int slice, double bVal, linalg::Vector3<double> diffusionDirection);
    unsigned int create_dwimage_from_pyobject(PyObject* obj, int width, int height, int slice, double bVal, linalg::Vector3<double> diffusionDirection);

    void dwimage_set_b_value(unsigned int id, double bVal);
    void dwimage_set_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection);
    double dwimage_get_b_value(unsigned int id);
    linalg::Vector3<double> dwimage_get_diffusion_direction(unsigned int id);
}

extern "C" {
    PyObject* python_create_dwimage(PyObject* self, PyObject* args);
    PyObject* python_create_dwimage_from_pyobject(PyObject* self, PyObject* args);
    PyObject* python_get_dwimage_b_value(PyObject* self, PyObject* args);
    PyObject* python_get_dwimage_diffusion_direction(PyObject* self, PyObject* args);
    PyObject* python_set_dwimage_b_value(PyObject* self, PyObject* args);
    PyObject* python_set_dwimage_diffusion_direction(PyObject* self, PyObject* args);
}

#endif