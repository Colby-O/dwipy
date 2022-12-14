#include "dwipy/core/include/interface/DWImage4DInterface.h"

std::vector<double> Image::convert_python_object_to_b_value_vector(PyObject* obj) {
    assert(PyList_Check(obj));
    std::vector<double> bVals;

    for (Py_ssize_t i = 0; i < PyList_Size(obj); ++i) {
        bVals.push_back(PyFloat_AsDouble(PyList_GetItem(obj, i)));
    }

    return bVals;
}

std::vector<linalg::Vector3<double>> Image::convert_python_object_to_diffusion_direction_vector(PyObject* obj) {
    assert(PyList_Check(obj));
    std::vector<linalg::Vector3<double>> diffusionDirections;

    for (Py_ssize_t i = 0; i < PyList_Size(obj); ++i) {
        diffusionDirections.push_back(linalg::Vector3<double>(PyList_GetItem(obj, i)));
    }

    return diffusionDirections;
}

PyObject* Image::convert_b_value_vector_to_python_object(std::vector<double> bVals) {
    PyObject* obj = PyList_New(bVals.size());

    for (Py_ssize_t i = 0; i < bVals.size(); ++i) {
        PyObject* bVal = PyFloat_FromDouble(bVals[i]);
        PyList_SetItem(obj, i, bVal);
    }

    return obj;
}

PyObject* Image::convert_diffusion_direction_vector_to_python_object(std::vector<linalg::Vector3<double>> diffusionDirections) {
    PyObject* obj = PyList_New(diffusionDirections.size());

    for (Py_ssize_t i = 0; i < diffusionDirections.size(); ++i) {
        PyList_SetItem(obj, i, diffusionDirections[i].convertToPyObject());
    }

    return obj;
}

unsigned int Image::create_dwimage4D(int width, int height, int slices) {
    auto [img, id] = ObjectManger::insertObject<DWImage4D>(width, height, slices);
    return id;
}

unsigned int Image::create_dwimage4D_from_pyobject(PyObject* obj, std::vector<double> bVal, std::vector<linalg::Vector3<double>> diffusionDirections, int width, int height, int slices, int numImages) {
    auto [img, id] = ObjectManger::insertObject<DWImage4D>(obj, bVal, diffusionDirections, width, height, slices, numImages);
    return id;
}

PyObject* Image::dwimage4D_get_data(unsigned int id) {    
    return ObjectManger::getObject<DWImage4D>(id)->convertToPyObject();
}

unsigned int Image::dwimage4D_get_images_with_b_value(unsigned int id, double bValue) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(bValue);

    auto [img, newID] = ObjectManger::insertObject<DWImage4D>(images);
    
    return newID;
}

unsigned int Image::dwimage4D_get_images_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(diffusionDirection);

    auto [img, newID] = ObjectManger::insertObject<DWImage4D>(images);
    
    return newID;
}

unsigned int Image::dwimage4D_get_images_with_b_values_and_diffusions_directions(unsigned int id, double bValue, linalg::Vector3<double> diffusionDirection) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(bValue, diffusionDirection);
    
    auto [img, newID] = ObjectManger::insertObject<DWImage4D>(images);

    return newID;
}

int Image::dwimage4D_get_number_of_images(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getNumberOfImages();
    
}

int Image::dwimage4D_get_number_of_images_with_b_value(unsigned int id, double bValue) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(bValue);
    return images.size();
}

int Image::dwimage4D_get_number_of_images_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(diffusionDirection);
    return images.size();
}

int Image::dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions(unsigned int id, double bValue, linalg::Vector3<double> diffusionDirection) {
    std::vector<DWImage*> images = ObjectManger::getObject<DWImage4D>(id)->getImages(bValue, diffusionDirection);
    return images.size();
}

int Image::dwimage4D_get_width(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getWidth();
}

int Image::dwimage4D_get_height(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getHeight();
}

int Image::dwimage4D_get_slices(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getSlices();
}

int Image::dwimage4D_get_size(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getSize();
}

std::vector<double> Image::dwimage4D_get_b_values(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getBValues();
}

std::vector<double> Image::dwimage4D_get_b_values_with_diffusion_direction(unsigned int id, linalg::Vector3<double> diffusionDirection) {
    return ObjectManger::getObject<DWImage4D>(id)->getBValues(diffusionDirection);
}

std::vector<linalg::Vector3<double>> Image::dwimage4D_get_diffusion_directions(unsigned int id) {
    return ObjectManger::getObject<DWImage4D>(id)->getDiffusionDirections();
}

std::vector<linalg::Vector3<double>> Image::dwimage4D_get_diffusion_directions_with_b_value(unsigned int id, double bValue) {
    return ObjectManger::getObject<DWImage4D>(id)->getDiffusionDirections(bValue);
}

void Image::dwimage4D_append_dwimage(unsigned int id1, unsigned int id2) {
    return ObjectManger::getObject<DWImage4D>(id1)->appendDWI(*ObjectManger::getObject<DWImage>(id2));
}

unsigned int Image::generate_trace_weight_dwimage4D(unsigned int id) {
    DWImage4D traceSet = ::Image::generateTraceWeightedDWImage4D(*ObjectManger::getObject<DWImage4D>(id));
    auto [img, newID] = ObjectManger::insertObject<DWImage4D>(std::move(traceSet));
    return newID;
}

PyObject* python_create_dwimage4D(PyObject* self, PyObject* args) {
    int width, height, slices;
    
    if (PyArg_ParseTuple(args, "iii", &width, &height, &slices)) {
        unsigned int id = Image::create_dwimage4D(width, height, slices);
        return PyLong_FromLong(id);
    }

    return NULL;
}

PyObject* python_create_dwimage4D_from_pyobject(PyObject* self, PyObject* args) {
    int width, height, slices, numImages;
    PyObject* diffusionDirectionsObj;
    PyObject* bValObj;
    PyObject* data;
    
    if (PyArg_ParseTuple(args, "OOOiiii", &data, &bValObj, &diffusionDirectionsObj, &width, &height, &slices, &numImages)) {
        std::vector<double> bVals = Image::convert_python_object_to_b_value_vector(bValObj);
        std::vector<linalg::Vector3<double>> diffusionDirections = Image::convert_python_object_to_diffusion_direction_vector(diffusionDirectionsObj);
        unsigned int id = Image::create_dwimage4D_from_pyobject(data, bVals, diffusionDirections, width, height, slices, numImages);
        return PyLong_FromLong(id);
    }

    return NULL;
}

PyObject* python_dwimage4D_get_data(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    PyObject* data = Image::dwimage4D_get_data(id);
    
    return data;
}

PyObject* python_dwimage4D_get_images_with_b_value(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    
    if (!PyArg_ParseTuple(args, "id", &id, &bVal)) {
         return NULL;
    }

    unsigned int newID = Image::dwimage4D_get_images_with_b_value(id, bVal);
    
    return PyLong_FromLong(newID);
}

PyObject* python_dwimage4D_get_images_with_diffusion_direction(PyObject* self, PyObject* args) {
    unsigned int id;
    PyObject* diffusionDirectionObj;
    
    if (!PyArg_ParseTuple(args, "iO", &id, &diffusionDirectionObj)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection(diffusionDirectionObj);
    unsigned int newID = Image::dwimage4D_get_images_with_diffusion_direction(id, diffusionDirection);
    
    return PyLong_FromLong(newID);
}

PyObject* python_dwimage4D_get_images_with_b_values_and_diffusions_directions(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    PyObject* diffusionDirectionObj;
    
    if (!PyArg_ParseTuple(args, "idO", &id, &bVal, &diffusionDirectionObj)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection(diffusionDirectionObj);
    unsigned int newID = Image::dwimage4D_get_images_with_b_values_and_diffusions_directions(id, bVal, diffusionDirection);
    
    return PyLong_FromLong(newID);
}

PyObject* python_dwimage4D_get_number_of_images(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int numImages = Image::dwimage4D_get_number_of_images((id));
    
    return PyLong_FromLong(numImages);
}

PyObject* python_dwimage4D_get_number_of_images_with_b_value(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    
    if (!PyArg_ParseTuple(args, "id", &id, &bVal)) {
         return NULL;
    }

    int numImages = Image::dwimage4D_get_number_of_images_with_b_value(id, bVal);
    
    return PyLong_FromLong(numImages);
}

PyObject* python_dwimage4D_get_number_of_images_with_diffusion_direction(PyObject* self, PyObject* args) {
    unsigned int id;
    PyObject* diffusionDirectionObj;
    
    if (!PyArg_ParseTuple(args, "iO", &id, &diffusionDirectionObj)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection(diffusionDirectionObj);
    int numImages = Image::dwimage4D_get_number_of_images_with_diffusion_direction(id, diffusionDirection);
    
    return PyLong_FromLong(numImages);
}

PyObject* python_dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    PyObject* diffusionDirectionObj;

    if (!PyArg_ParseTuple(args, "idO", &id, &bVal, &diffusionDirectionObj)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection(diffusionDirectionObj);
    unsigned int newID = Image::dwimage4D_get_number_of_images_with_b_values_and_diffusions_directions(id, bVal, diffusionDirection);
    
    return PyLong_FromLong(newID);
}

PyObject* python_dwimage4D_get_width(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int width = Image::dwimage4D_get_width(id);
    
    return PyLong_FromLong(width);
}

PyObject* python_dwimage4D_get_height(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int height = Image::dwimage4D_get_height(id);
    
    return PyLong_FromLong(height);
}

PyObject* python_dwimage4D_get_slices(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    int slices = Image::dwimage4D_get_slices(id);
    
    return PyLong_FromLong(slices);
}

PyObject* python_dwimage4D_get_b_values(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    std::vector<double> bVals = Image::dwimage4D_get_b_values(id);
    
    return Image::convert_b_value_vector_to_python_object(bVals);
}

PyObject* python_dwimage4D_get_b_values_with_diffusion_direction(PyObject* self, PyObject* args) {
    unsigned int id;
    PyObject* diffusionDirectionObj;
    
    if (!PyArg_ParseTuple(args, "iO", &id, &diffusionDirectionObj)) {
         return NULL;
    }

    linalg::Vector3<double> diffusionDirection(diffusionDirectionObj);
    std::vector<double> bVals = Image::dwimage4D_get_b_values_with_diffusion_direction(id, diffusionDirection);
    
    return Image::convert_b_value_vector_to_python_object(bVals);
}

PyObject* python_dwimage4D_get_diffusion_directions(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    std::vector<linalg::Vector3<double>> diffusionDirections = Image::dwimage4D_get_diffusion_directions(id);
    
    return Image::convert_diffusion_direction_vector_to_python_object(diffusionDirections);
}

PyObject* python_dwimage4D_get_diffusion_directions_with_b_value(PyObject* self, PyObject* args) {
    unsigned int id;
    double bVal;
    
    if (!PyArg_ParseTuple(args, "i", &id, &bVal)) {
         return NULL;
    }

    std::vector<linalg::Vector3<double>> diffusionDirections = Image::dwimage4D_get_diffusion_directions_with_b_value(id, bVal);
    
    return Image::convert_diffusion_direction_vector_to_python_object(diffusionDirections);   
}

PyObject* python_dwimage4D_append_dwimage(PyObject* self, PyObject* args) {
    unsigned int id1, id2;
    
    if (!PyArg_ParseTuple(args, "ii", &id1, &id2)) {
         return NULL;
    }

    Image::dwimage4D_append_dwimage(id1, id2);
    
    return Py_None;
}

PyObject* python_generate_trace_weight_dwimage4D(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    unsigned int newID = Image::generate_trace_weight_dwimage4D(id);
    
    return PyLong_FromLong(newID);
}