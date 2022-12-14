#include "dwipy/dwi/models/include/interface/DWIModelInterface.h"

PyObject* DWIModels::convert_mem_fit_result_to_pyobject(MEMFitResults res) {
    PyObject* resList = PyList_New(9);
    auto [adcMap, adcID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.adcMap));
    auto [s0Map, s0ID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.s0Map));
    auto [chiSquaredMap, chiSquaredID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.chiSquaredMap));

    PyList_SetItem(resList, 0, PyLong_FromLong(adcID));
    PyList_SetItem(resList, 1, PyLong_FromLong(s0ID));
    PyList_SetItem(resList, 2, PyLong_FromLong(chiSquaredID));
    PyList_SetItem(resList, 3, PyFloat_FromDouble(res.avgADC));
    PyList_SetItem(resList, 4, PyFloat_FromDouble(res.stdADC));
    PyList_SetItem(resList, 5, PyFloat_FromDouble(res.avgS0));
    PyList_SetItem(resList, 6, PyFloat_FromDouble(res.stdS0));
    PyList_SetItem(resList, 7, PyFloat_FromDouble(res.avgChiSqaured));
    PyList_SetItem(resList, 8, PyFloat_FromDouble(res.stdChiSquared));
    return resList;
}

PyObject* DWIModels::convert_ivim_fit_result_to_pyobject(IVIMFitResults res) {
    PyObject* resList = PyList_New(5);
    auto [adcMap, adcID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.adcMap));
    auto [s0Map, s0ID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.s0Map));
    auto [dMap, dID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.dMap));
    auto [fMap, fID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.fMap));
    auto [chiSquaredMap, chiSquaredMapID] = ObjectManger::insertObject<Image::Image3D>(std::move(res.chiSquaredMap));

    PyList_SetItem(resList, 0, PyLong_FromLong(adcID));
    PyList_SetItem(resList, 1, PyLong_FromLong(dID));
    PyList_SetItem(resList, 2, PyLong_FromLong(fID));
    PyList_SetItem(resList, 3, PyLong_FromLong(s0ID));
    PyList_SetItem(resList, 4, PyLong_FromLong(chiSquaredMapID));

    return resList;
}

PyObject* DWIModels::fit_mem_to_dwimage4D(unsigned int id) {
    Image::DWImage4D dwiSet = *ObjectManger::getObject<Image::DWImage4D>(id);
    MEMFitResults res = fitMEM(dwiSet, "");

    return convert_mem_fit_result_to_pyobject(res);
}

PyObject* DWIModels::fit_ivim_to_dwimage4D(unsigned int id) {
    Image::DWImage4D dwiSet = *ObjectManger::getObject<Image::DWImage4D>(id);
    IVIMFitResults res = fitIVIM(dwiSet);

    return convert_ivim_fit_result_to_pyobject(res);
}

PyObject* python_fit_mem_to_dwimage4D(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    PyObject* fitRes = DWIModels::fit_mem_to_dwimage4D(id);
    
    return fitRes;
}

PyObject* python_fit_ivim_to_dwimage4D(PyObject* self, PyObject* args) {
    unsigned int id;
    
    if (!PyArg_ParseTuple(args, "i", &id)) {
         return NULL;
    }

    PyObject* fitRes = DWIModels::fit_ivim_to_dwimage4D(id);
    
    return fitRes;
}