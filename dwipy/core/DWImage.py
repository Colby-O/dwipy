import os
import sys
import numpy as np

currentdir = os.path.dirname(os.path.realpath(__file__))
parentdir = os.path.dirname(os.path.dirname(currentdir))
sys.path.append(parentdir)

import dwipy.core.imageSrc as imageSrc
from dwipy.core.image3D import Image3D
from dwipy.misc.funcHelper import FuncHelpers

class DWImage(Image3D):
    @FuncHelpers.fileOrArray(3)
    def __init__(self, data = None, bValue = None, diffusionDirection = None, dim = None):
        self.id = None
        if (type(data) == type(None) and type(dim) != type(None)):
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 3)
            self.id = imageSrc.create_dwimage(dim[0], dim[1], dim[2], bValue, diffusionDirection)
        elif (type(data) != type(None)):
            assert(type(data) == list)
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 3)
            self.id = imageSrc.create_dwimage_from_pyobject(data, dim[0], dim[1], dim[2], bValue, diffusionDirection)

    def create_empty(width, height, slice, bValue = None, diffusionDirection = None):
        return DWImage(width = width, height = height, slice = slice, bValue = bValue, diffusionDirection = diffusionDirection)

    def get_b_value(self):
        return imageSrc.dwimage_get_b_value(self.id)

    def get_diffusion_direction(self):
        return imageSrc.dwimage_get_diffusion_direction(self.id)

    def set_b_value(self, bVal):
        return imageSrc.dwimage_set_b_value(self.id, bVal)

    def set_diffusion_direction(self, diffusionDirection):
        return imageSrc.dwimage_set_diffusion_direction(self.id, diffusionDirection)