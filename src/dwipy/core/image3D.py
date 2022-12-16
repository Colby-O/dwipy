import os
import sys
import numpy as np

import dwipySrc as imageSrc
from dwipy.core.image2D import Image2D
from dwipy.misc.funcHelper import FuncHelpers
     
# Wrapper Class for Image
class Image3D(Image2D):
    '''
    
    '''
    @FuncHelpers.fileOrArray(3)
    def __init__(self, data = None, dim = None):
        self.id = None
        if (type(data) == type(None) and type(dim) != type(None)):
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 3)
            self.id = imageSrc.create_image3D(dim[0], dim[1], dim[2])
        elif (type(data) != type(None)):
            assert(type(data) == list)
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 3)
            self.id = imageSrc.create_image3D_from_pyobject(data, dim[0], dim[1], dim[2])

    def create_empty(width, height, slice):
        return Image3D(width = width, height = height, slice = slice)

    def get_width(self):
        return imageSrc.get_image3D_width(self.id)

    def get_height(self):
        return imageSrc.get_image3D_height(self.id)

    def get_slices(self):
        return imageSrc.get_image3D_slices(self.id)

    def get_size(self):
        return imageSrc.get_image3D_size(self.id)

    def get_data(self):
        return np.array(imageSrc.get_image3D_data(self.id))

    def get_id(self):
        return self.id

    def get_at(self, i, j, k):
        return imageSrc.get_image3D_value(self.id, i, j, k)

    def __add__(self, other):
        new_image = Image3D()
        if(isinstance(other, Image3D)):
            new_image.id = imageSrc.image3D_add(self.id, other.get_id())
        else:
            new_image.id = imageSrc.image3D_add_constant(self.id, other)
        
        return new_image
    
    def __iadd__(self, other):
        if(isinstance(other, Image3D)):
            self.id = imageSrc.image3D_iadd(self.id, other.get_id())
        else:
            self.id = imageSrc.image3D_iadd_constant(self.id, other)

        return self

    def __sub__(self, other):
        new_image = Image3D()
        if(isinstance(other, Image3D)):
            new_image.id = imageSrc.image3D_subtract(self.id, other.get_id())
        else:
            new_image.id = imageSrc.image3D_add_constant(self.id, -1 * other)
        
        return new_image
    
    def __mul__(self, other):
        new_image = Image3D()
        if(isinstance(other, Image3D)):
            new_image.id = imageSrc.image3D_mul(self.id, other.get_id())
        else:
            new_image.id = imageSrc.image3D_scale(self.id, other)
        
        return new_image

    def __str__(self):
        return ""

    def __del__(self):
        imageSrc.delete_object(self.id)
