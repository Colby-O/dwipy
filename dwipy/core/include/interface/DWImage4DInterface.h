#ifndef DWIMAGE$DINTERFACE_H_
#define DWIMAGE$DINTERFACE_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "dwipy/core/include/images/DWImage4D.h"
#include "dwipy/core/include/generic/Object.h"

namespace Image {
    // Should be moved to a helper file
    std::vector<double> convert_python_object_to_b_value_vector(PyObject* obj);
    std::vector<linalg::Vector3<double>> convert_python_object_to_diffusion_direction_vector(PyObject* obj);
    PyObject* convert_b_value_vector_to_python_object(std::vector<double> bVals);
    PyObject* convert_diffusion_direction_vector_to_python_object(std::vector<linalg::Vector3<double>> diffusionDirections);

    unsigned int create_dwimage4D(int width, int height, int slices);
    unsigned int create_dwimage4D_from_pyobject(PyObject* obj, std::vector<double> bVal, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages);
    PyObject* dwimage4D_get_data(unsigned int id);
    unsigned int dwimage4D_get_images_with_b_value(unsigned int id, double bValue);
    unsigned int dwimage4D_get_images_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection);
    unsigned int dwimage4D_get_images_with_b_values_and_diffusions_directions(unsigned int id, double bValue, linalg::Vector3<double> diffusionDirection);
    int dwimage4D_get_number_of_images(unsigned int id);
    int dwimage4D_get_number_of_images_with_b_value(unsigned int id, double bValue);
    int dwimage4D_get_number_of_images_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection);
    int dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions(unsigned int id, double bValue, linalg::Vector3<double> diffusionDirection);
    int dwimage4D_get_number_of_images(unsigned int id);
    int dwimage4D_get_width(unsigned int id);
    int dwimage4D_get_height(unsigned int id);
    int dwimage4D_get_slices(unsigned int id);
    int dwimage4D_get_size(unsigned int id);
    std::vector<double> dwimage4D_get_b_values(unsigned int id);
    std::vector<double> dwimage4D_get_b_values_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection);
    std::vector<linalg::Vector3<double>> dwimage4D_get_diffusion_directions(unsigned int id);
    std::vector<linalg::Vector3<double>> dwimage4D_get_diffusion_directions_with_b_value(unsigned int id, double bValue);
    void dwimage4D_append_dwimage(unsigned int id1, unsigned int id2);
    unsigned int generate_trace_weight_dwimage4D(unsigned int id);
}

extern "C" {
    PyObject* python_create_dwimage4D(PyObject* self, PyObject* args);
    PyObject* python_create_dwimage4D_from_pyobject(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_data(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_images_with_b_value(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_images_with_diffusion_direction(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_images_with_b_values_and_diffusions_directions(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_number_of_images(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_number_of_images_with_b_value(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_number_of_images_with_diffusion_direction(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_width(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_height(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_slices(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_b_values(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_b_values_with_diffusion_direction(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_diffusion_directions(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_get_diffusion_directions_with_b_value(PyObject* self, PyObject* args);
    PyObject* python_dwimage4D_append_dwimage(PyObject* self, PyObject* args);
    PyObject* python_generate_trace_weight_dwimage4D(PyObject* self, PyObject* args);
}

#endif