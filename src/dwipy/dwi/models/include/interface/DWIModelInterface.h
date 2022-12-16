#ifndef MODELINTERFACE_H_
#define MODELINTERFACE_H_

#include "dwipy/dwi/models/include/MEM.h"
#include "dwipy/dwi/models/include/IVIM.h"
#include "dwipy/core/include/generic/Object.h"

namespace DWIModels {
    PyObject* convert_mem_fit_result_to_pyobject(MEMFitResults res);
    PyObject* convert_ivim_fit_result_to_pyobject(IVIMFitResults res);
    PyObject* fit_mem_to_dwimage4D(unsigned int id);
    PyObject* fit_ivim_to_dwimage4D(unsigned int id);
}

extern "C" {
    PyObject* python_fit_mem_to_dwimage4D(PyObject* self, PyObject* args);
    PyObject* python_fit_ivim_to_dwimage4D(PyObject* self, PyObject* args);
}

#endif