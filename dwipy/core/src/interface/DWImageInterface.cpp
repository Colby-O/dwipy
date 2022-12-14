#include "dwipy/core/include/interface/DWImageInterface.h"

unsigned int Image::create_dwimage(int width, int height, int slices, double bVal, linalg::Vector3<double> diffusionDirection) {
    auto [img, id] = ObjectManger::insertObject<DWImage>(width, height, slices, bVal, diffusionDirection);
    return id;
}

unsigned int Image::create_dwimage_from_pyobject(PyObject* obj, int width, int height, int slices, double bVal, linalg::Vector3<double> diffusionDirection) {
    auto [img, id] = ObjectManger::insertObject<DWImage>(obj, width, height, slices, bVal, diffusionDirection);
    return id;
}

void Image::dwimage_set_b_value(unsigned int id, double bVal) {
    ObjectManger::getObject<DWImage>(id)->setBValue(bVal);
}

void Image::dwimage_set_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection) {
    ObjectManger::getObject<DWImage>(id)->setDiffusionDirection(diffusionDirection);
}

double Image::dwimage_get_b_value(unsigned int id) {
    return ObjectManger::getObject<DWImage>(id)->getBValue();
}

linalg::Vector3<double> Image::dwimage_get_diffusion_direction(unsigned int id) {
    return ObjectManger::getObject<DWImage>(id)->getDiffusionDirection();
}


PyObject* python_create_dwimage(PyObject* self, PyObject* args) {
    int width, height, slices;
    double bVal;
    PyObject* diffusionDirectionObj;
    
    if (PyArg_ParseTuple(args, "iiidO", &width, &height, &slices, &bVal, &diffusionDirectionObj)) {
        linalg::Vector3<double> diffusionDirection = (PyList_Check(diffusionDirectionObj)) ? linalg::Vector3<double>(diffusionDirectionObj) : linalg::Vector3<double>(0.0, 0.0, 0.0);
        unsigned int id = Image::create_dwimage(width, height, slices, bVal, diffusionDirection);
        return PyLong_FromLong(id);
    }

    return NULL;
}

PyObject* python_create_dwimage_from_pyobject(PyObject* self, PyObject* args) {
    int width, height, slices;
    double bVal;
    PyObject* diffusionDirectionObj;
    PyObject* data;
    
    if (PyArg_ParseTuple(args, "OiiidO", &data, &width, &height, &slices, &bVal, &diffusionDirectionObj)) {
        linalg::Vector3<double> diffusionDirection = (PyList_Check(diffusionDirectionObj)) ? linalg::Vector3<double>(diffusionDirectionObj) : linalg::Vector3<double>(0.0, 0.0, 0.0);
        unsigned int id = Image::create_dwimage_from_pyobject(data, width, height, slices, bVal, diffusionDirection);
        return PyLong_FromLong(id);
    }

    return NULL;
}

PyObject* python_get_dwimage_b_value(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int bVal = Image::dwimage_get_b_value(id);
    
    return PyFloat_FromDouble(bVal); 
}

PyObject* python_get_dwimage_diffusion_direction(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection = Image::dwimage_get_diffusion_direction(id);
    
    return diffusionDirection.convertToPyObject();
}

PyObject* python_set_dwimage_b_value(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    
    if (!PyArg_ParseTuple(args, "id", &id, &bVal)) {
         return NULL;
    }

    Image::dwimage_set_b_value(id, bVal);
    
    return Py_None;
}

PyObject* python_set_dwimage_diffusion_direction(PyObject* self, PyObject* args) {
    unsigned int id;
    PyObject* diffusionDirectionObj;
    
    if (!PyArg_ParseTuple(args, "iO", &id, &diffusionDirectionObj)) {
         return NULL;
    }

    Image::dwimage_set_diffusion_direction(id, linalg::Vector3<double>(diffusionDirectionObj));
    
    return Py_None;
}