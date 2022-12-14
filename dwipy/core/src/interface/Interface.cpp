#define PY_SSIZE_T_CLEAN
#include <Python.h>
//#include "../headers/image2DInterface.h"
#include "dwipy/core/include/interface/Image3DInterface.h"
#include "dwipy/core/include/interface/DWImageInterface.h"
#include "dwipy/core/include/interface/DWImage4DInterface.h"
// Should be removed from here
#include "dwipy/dwi/models/include/interface/DWIModelInterface.h"

extern "C" {
    PyObject* python_delete_object(PyObject* self, PyObject* args);

    static PyMethodDef pyMethods[] = {
        {"create_image3D", python_create_image3D, METH_VARARGS, "Initializes image gievn the image dimensions i.e. width, height, and slice count."},
        {"create_image3D_from_pyobject", python_create_image3D_from_pyobject, METH_VARARGS, "Initializes image gievn the image dimensions and image data."},
        {"delete_object", python_delete_object, METH_VARARGS, "Deletes an object."},
        {"get_image3D_data", python_get_image3D_data, METH_VARARGS, "Gets the images data array."},
        {"get_image3D_width", python_get_image3D_width, METH_VARARGS, "Gets the images width."},
        {"get_image3D_height", python_get_image3D_width, METH_VARARGS, "Gets the images height."},
        {"get_image3D_slices", python_get_image3D_slices, METH_VARARGS, "Gets the number of slices in the image."},
        {"get_image3D_size", python_get_image3D_size, METH_VARARGS, "Gets the images size."},
        {"image3D_add", python_image3D_add, METH_VARARGS, "Adds two images together."},
        {"image3D_iadd", python_image3D_iadd, METH_VARARGS, "Adds two images together."},
        {"image3D_add_constant", python_image3D_add_constant, METH_VARARGS, "Adds a constant to a image."},
        {"image3D_iadd_constant", python_image3D_iadd_constant, METH_VARARGS, "Adds a constant to a image."},
        {"image3D_subtract", python_image3D_subtract, METH_VARARGS, "Subtracts two images together."},
        {"image3D_mul", python_image3D_mul, METH_VARARGS, "Multiplies two images together."},
        {"image3D_scale", python_image3D_scale, METH_VARARGS, "Scale a image by a constant factor."},
        {"get_image3D_value", python_get_image3D_value, METH_VARARGS, "Gets the i, j, k element of an image."},
        {"create_dwimage", python_create_dwimage, METH_VARARGS, "Creates a DWImage object."},
        {"create_dwimage_from_pyobject", python_create_dwimage_from_pyobject, METH_VARARGS, "Creates a DWImage object."},
        {"dwimage_get_b_value", python_get_dwimage_b_value, METH_VARARGS, "Gets b-value for a DWImage."},
        {"dwimage_get_diffusion_direction", python_get_dwimage_diffusion_direction, METH_VARARGS, "Gets diffusion direction for a DWImage."},
        {"dwimage_set_b_value", python_set_dwimage_b_value, METH_VARARGS, "Sets b-value for a DWImage."},
        {"dwimage_set_diffusion_direction", python_set_dwimage_diffusion_direction, METH_VARARGS, "Sets diffusion direction for a DWImage."},
        {"create_dwimage4D", python_create_dwimage4D, METH_VARARGS, ""},
        {"create_dwimage4D_from_pyobject", python_create_dwimage4D_from_pyobject, METH_VARARGS, ""},
        {"dwimage4D_get_data", python_dwimage4D_get_data, METH_VARARGS, ""},
        {"dwimage4D_get_images_with_b_value", python_dwimage4D_get_images_with_b_value, METH_VARARGS, ""},
        {"dwimage4D_get_images_with_diffusion_direction", python_dwimage4D_get_images_with_diffusion_direction, METH_VARARGS, ""},
        {"dwimage4D_get_images_with_b_values_and_diffusions_directions", python_dwimage4D_get_images_with_b_values_and_diffusions_directions, METH_VARARGS, ""},
        {"dwimage4D_get_number_of_images", python_dwimage4D_get_number_of_images, METH_VARARGS, ""},
        {"dwimage4D_get_number_of_images_with_b_value", python_dwimage4D_get_number_of_images_with_b_value, METH_VARARGS, ""},
        {"dwimage4D_get_number_of_images_with_diffusion_direction", python_dwimage4D_get_number_of_images_with_diffusion_direction, METH_VARARGS, ""},
        {"dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions", python_dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions, METH_VARARGS, ""},
        {"dwimage4D_get_width", python_dwimage4D_get_width, METH_VARARGS, ""},
        {"dwimage4D_get_height", python_dwimage4D_get_height, METH_VARARGS, ""},
        {"dwimage4D_get_slices", python_dwimage4D_get_slices, METH_VARARGS, ""},
        {"dwimage4D_get_b_values", python_dwimage4D_get_b_values, METH_VARARGS, ""},
        {"dwimage4D_get_b_values_with_diffusion_direction", python_dwimage4D_get_b_values_with_diffusion_direction, METH_VARARGS, ""},
        {"dwimage4D_get_diffusion_directions", python_dwimage4D_get_diffusion_directions, METH_VARARGS, ""},
        {"dwimage4D_get_diffusion_directions_with_b_value", python_dwimage4D_get_diffusion_directions_with_b_value, METH_VARARGS, ""},
        {"dwimage4D_append_dwimage", python_dwimage4D_append_dwimage, METH_VARARGS, ""},
        {"generate_trace_weight_dwimage4D", python_generate_trace_weight_dwimage4D, METH_VARARGS, ""},
        {"fit_MEM", python_fit_mem_to_dwimage4D, METH_VARARGS, ""},
        {"fit_IVIM", python_fit_ivim_to_dwimage4D, METH_VARARGS, ""},
        {NULL, NULL,0,NULL}
    };

    static struct PyModuleDef Models = {
        PyModuleDef_HEAD_INIT,
        "image",
        "image",
        -1, //global state
        pyMethods
    };

    // Initializer function
    PyMODINIT_FUNC PyInit_imageSrc(void) {
        return PyModule_Create(&Models);
    }

}

PyObject* python_delete_object(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    ObjectManger::deleteObject(id);

    return Py_None;
}