#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "dwipy/dwi/models/include/interface/DWIModelInterface.h"

extern "C" {
    static PyMethodDef pyMethods[] = {
        {"fit_MEM", python_fit_mem_to_dwimage4D, METH_VARARGS, ""},
        {NULL, NULL,0,NULL}
    };

    static struct PyModuleDef Models = {
        PyModuleDef_HEAD_INIT,
        "dwiModels",
        "dwiModels",
        -1, //global state
        pyMethods
    };

    // Initializer function
    PyMODINIT_FUNC PyInit_dwiModelsSrc(void) {
        return PyModule_Create(&Models);
    }

}