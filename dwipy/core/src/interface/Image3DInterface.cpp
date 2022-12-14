#include "dwipy/core/include/interface/Image3DInterface.h"

unsigned int Image::create_image3D(int width, int height, int slice) {
    auto [img, id] = ObjectManger::insertObject<Image3D>(width, height, slice);
    return id;
}

unsigned int Image::create_image3D_from_pyobject(PyObject* obj, int width, int height, int slice) {
    auto [img, id] = ObjectManger::insertObject<Image3D>(obj, width, height, slice);
    return id;
}

int Image::get_image3D_width(unsigned int id) {   
    return ObjectManger::getObject<Image3D>(id)->getWidth();
}

int Image::get_image3D_height(unsigned int id) {
    return ObjectManger::getObject<Image3D>(id)->getHeight();
}

int Image::get_image3D_slices(unsigned int id) {
    return ObjectManger::getObject<Image3D>(id)->getSlices();
}

int Image::get_image3D_size(unsigned int id) {
    return ObjectManger::getObject<Image3D>(id)->getSize();
}

unsigned int Image::image3D_add(unsigned int  id1, unsigned int id2) {
    Image3D& img1 = *ObjectManger::getObject<Image3D>(id1);
    Image3D& img2 = *ObjectManger::getObject<Image3D>(id2);

    auto [newImg, id] = ObjectManger::insertObject<Image3D>(img1 + img2);

    return id;
}

unsigned int Image::image3D_iadd(unsigned int  id1, unsigned int id2) {
    Image3D& img1 = *ObjectManger::getObject<Image3D>(id1);
    Image3D& img2 = *ObjectManger::getObject<Image3D>(id2);

    img1 += img2;

    return id1;
}

unsigned int Image::image3D_iadd_constant(unsigned int id, double constant) {
    Image3D& img = *ObjectManger::getObject<Image3D>(id);

    img += constant;

    return id;
}

unsigned int Image::image3D_subtract(unsigned int id1, unsigned int id2) {
    Image3D& img1 = *ObjectManger::getObject<Image3D>(id1);
    Image3D& img2 = *ObjectManger::getObject<Image3D>(id2);

    auto [newImg, id] = ObjectManger::insertObject<Image3D>(img1 - img2);

    return id;
}

unsigned int Image::image3D_mul(unsigned int id1, unsigned int id2) {
    Image3D& img1 = *ObjectManger::getObject<Image3D>(id1);
    Image3D& img2 = *ObjectManger::getObject<Image3D>(id2);

    auto [newImg, id] = ObjectManger::insertObject<Image3D>(img1 * img2);

    return id;
}

unsigned int Image::image3D_scale(unsigned int id, double scale) {
    Image3D& img = *ObjectManger::getObject<Image3D>(id);

    auto [newImg, newID] = ObjectManger::insertObject<Image3D>(img * scale);

    return newID;
}

unsigned int Image::image3D_add_constant(unsigned int id, double constant) {
    Image3D& img = *ObjectManger::getObject<Image3D>(id);

    auto [newImg, newID] = ObjectManger::insertObject<Image3D>(img + constant);

    return newID;
}

double Image::get_image3D_value(unsigned int  id, int i, int j, int k) {
    return (*ObjectManger::getObject<Image3D>(id))(i, j, k);
}

PyObject* Image::get_image3D_data(unsigned int id) {
   return ObjectManger::getObject<Image3D>(id)->convertToPyObject();
}

// Python Interface
PyObject* python_create_image3D(PyObject* self, PyObject* args) {
    int width, height, slices;
    
    if (PyArg_ParseTuple(args, "iii", &width, &height, &slices)) {
         unsigned int id = Image::create_image3D(width, height, slices);
         return PyLong_FromLong(id);
    }

    return NULL;
}

PyObject* python_create_image3D_from_pyobject(PyObject* self, PyObject* args) {
    int width, height, slices;
    PyObject* data;
    
    if (PyArg_ParseTuple(args, "Oiii", &data, &width, &height, &slices)) {
        unsigned int id = Image::create_image3D_from_pyobject(data, width, height, slices);
        return PyLong_FromLong(id);
    }
    return NULL;
}

PyObject* python_get_image3D_data(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    PyObject* data = Image::get_image3D_data(id);
    
    return data;
}

PyObject* python_get_image3D_width(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int width = Image::get_image3D_width(id);
    
    return PyLong_FromLong(width);
}

PyObject* python_get_image3D_height(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int height = Image::get_image3D_height(id);
    
    return PyLong_FromLong(height);
}

PyObject* python_get_image3D_slices(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int slices = Image::get_image3D_slices(id);
    
    return PyLong_FromLong(slices);
}

PyObject* python_get_image3D_size(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int size = Image::get_image3D_size(id);
    
    return PyLong_FromLong(size);
}

PyObject* python_image3D_add(PyObject* self, PyObject* args) {
    unsigned int id1, id2;
    
    //std:: cout << "B\n";

    if (!PyArg_ParseTuple(args, "ii", &id1, &id2)) {
         return NULL;
    }

    unsigned int id = Image::image3D_add(id1, id2);

    return PyLong_FromLong(id);
}

PyObject* python_image3D_iadd(PyObject* self, PyObject* args) {
    unsigned int id1, id2;
    
    //std:: cout << "B\n";

    if (!PyArg_ParseTuple(args, "ii", &id1, &id2)) {
         return NULL;
    }

    unsigned int id = Image::image3D_iadd(id1, id2);

    return PyLong_FromLong(id);
}

PyObject* python_image3D_add_constant(PyObject* self, PyObject* args) {
    unsigned int id1;
    double constant;
    
    if (!PyArg_ParseTuple(args, "id", &id1, &constant)) {
         return NULL;
    }
    
    unsigned int id = Image::image3D_add_constant(id1, constant);
    
    return PyLong_FromLong(id);
}

PyObject* python_image3D_iadd_constant(PyObject* self, PyObject* args) {
    unsigned int id1;
    double constant;
    
    if (!PyArg_ParseTuple(args, "id", &id1, &constant)) {
         return NULL;
    }
    
    unsigned int id = Image::image3D_iadd_constant(id1, constant);
    
    return PyLong_FromLong(id);
}

PyObject* python_image3D_subtract(PyObject* self, PyObject* args) {
    unsigned int id1, id2;
    
    if (!PyArg_ParseTuple(args, "ii", &id1, &id2)) {
         return NULL;
    }

    unsigned int id = Image::image3D_subtract(id1, id2);
    
    return PyLong_FromLong(id);
}

PyObject* python_image3D_mul(PyObject* self, PyObject* args) {
    unsigned int id1, id2;
    
    if (!PyArg_ParseTuple(args, "ii", &id1, &id2)) {
         return NULL;
    }

    unsigned int id = Image::image3D_mul(id1, id2);
    
    return PyLong_FromLong(id);
}

PyObject* python_image3D_scale(PyObject* self, PyObject* args) {
    unsigned int id1;
    double scale;
    
    if (!PyArg_ParseTuple(args, "id", &id1, &scale)) {
         return NULL;
    }

    unsigned int id = Image::image3D_scale(id1, scale);
    
    return PyLong_FromLong(id);
}

PyObject* python_get_image3D_value(PyObject* self, PyObject* args) {
    int i, j, k;
    unsigned int id;
    
    if (PyArg_ParseTuple(args, "iiii", &id, &i, &j, &k)) {
        double voxelValue = Image::get_image3D_value(id, i, j, k) ;
        return PyFloat_FromDouble(voxelValue);
    }

    return NULL;
}