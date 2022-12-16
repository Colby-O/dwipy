#ifndef IMAGE3DINTERFACE_H_
#define IMAGE3DINTERFACE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "dwipy/core/include/images/Image3D.h"
#include "dwipy/core/include/generic/Object.h"

namespace Image {
    // Constructors
    unsigned int create_image3D(int width, int height, int slice);
    unsigned int create_image3D_from_pyobject(PyObject* obj, int width, int height, int slice);

    // Getters
    PyObject* get_image3D_data(unsigned int id);
    int get_image3D_width(unsigned int id);
    int get_image3D_height(unsigned int id);
    int get_image3D_slices(unsigned int id);
    int get_image3D_size(unsigned int id);

    // Member functions

    // Operators Overloads
    unsigned int image3D_add(unsigned int id1, unsigned int id2);
    unsigned int image3D_iadd(unsigned int id1, unsigned int id2);
    unsigned int image3D_add_constant(unsigned int id, double constant);
    unsigned int image3D_iadd_constant(unsigned int id, double constant);
    unsigned int image3D_subtract(unsigned int id1, unsigned int id2);
    unsigned int image3D_mul(unsigned int id1, unsigned int id2);
    unsigned int image3D_scale(unsigned int id, double scale);
    double get_image3D_value(unsigned int id, int i, int j, int k);
}
// Python wrappers
extern "C" {
    PyObject* python_create_image3D(PyObject* self, PyObject* args);
    PyObject* python_create_image3D_from_pyobject(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_data(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_size(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_width(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_height(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_slices(PyObject* self, PyObject* args);
    PyObject* python_image3D_add(PyObject* self, PyObject* args);
    PyObject* python_image3D_iadd(PyObject* self, PyObject* args);
    PyObject* python_image3D_add_constant(PyObject* self, PyObject* args);
    PyObject* python_image3D_iadd_constant(PyObject* self, PyObject* args);
    PyObject* python_image3D_subtract(PyObject* self, PyObject* args);
    PyObject* python_image3D_mul(PyObject* self, PyObject* args);
    PyObject* python_image3D_scale(PyObject* self, PyObject* args);
    PyObject* python_get_image3D_value(PyObject* self, PyObject* args);
}
#endif