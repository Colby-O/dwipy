import sys
import os
import numpy as np

currentdir = os.path.dirname(os.path.realpath(__file__))
parentdir = os.path.dirname(os.path.dirname(currentdir))
sys.path.append(parentdir)

from dwipy.misc.sysHelper import sysHelpers

class FuncHelpers:
    # Ensures a input is a python list
    def fileOrArray(imageDim = 3):    
        def decorator(f):
            def wrapper(self, *args, **kw):
                dim = None
                for key in kw:
                    val = kw[key]
                    # Gets data from file
                    if (isinstance(val, str)):
                        val = sysHelpers.getDataFromFile(val)

                    # TODO: Add support for numpy array in C
                    # For the time being converts numpy arrays to python lists
                    if (isinstance(val, np.ndarray)):
                        val = val.tolist()

                    # Gets size of image if data is given
                    if (isinstance(val, list) and len(np.array(val).shape) == imageDim):
                        dim = np.array(val).shape

                    kw[key] = val

                # overrides the changed arguments
                if (type(dim) == type(None)):
                    return f(self, *args, **kw) 
                else:
                    kw.pop('dim', None)
                    return f(self, dim = dim, *args, **kw)
            return wrapper

        return decorator