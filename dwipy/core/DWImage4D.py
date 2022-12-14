import os
import sys
import numpy as np

currentdir = os.path.dirname(os.path.realpath(__file__))
parentdir = os.path.dirname(os.path.dirname(currentdir))
sys.path.append(parentdir)

import dwipy.core.imageSrc as imageSrc
from dwipy.core.DWImage import DWImage
from dwipy.misc.funcHelper import FuncHelpers

class DWImage4D:
    @FuncHelpers.fileOrArray(4)
    def __init__(self, data = None, bValues = None, diffusionDirections = None, dim = None):
        self.id = None
        if (type(data) == type(None) and type(dim) != type(None)):
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 3)
            self.id = imageSrc.create_dwimage4D(dim[0], dim[1], dim[2])
        elif (type(data) != type(None)):
            assert(type(data) == list)
            assert(type(dim) == list or type(dim) == tuple)
            assert(len(dim) == 4)
            self.id = imageSrc.create_dwimage4D_from_pyobject(data, bValues, diffusionDirections, dim[0], dim[1], dim[2], dim[3])

    def get_id(self):
        return self.id

    def get_data(self):
        return np.array(imageSrc.dwimage4D_get_data(self.id))

    def get_width(self):
        return imageSrc.dwimage4D_get_width(self.id)

    def get_height(self):
        return imageSrc.dwimage4D_get_height(self.id)

    def get_slices(self):
        return imageSrc.dwimage4D_get_slices(self.id)

    def get_size(self):
        raise NotImplementedError()

    def get_images(self, bVal = None, diffusionDirection = None):
        newImg = DWImage4D()
        if (type(bVal) != type(None) and type(diffusionDirection) != type(None)):
            if (type(diffusionDirection) == np.ndarray):
                diffusionDirection = diffusionDirection.tolist()
            assert(type(diffusionDirection) == list)
            assert(len(diffusionDirection) == 3)
            newImg.id =  imageSrc.dwimage4D_get_images_with_b_values_and_diffusions_directions(self.id, bVal, diffusionDirection)
        elif (type(bVal) != type(None)):
            newImg.id = imageSrc.dwimage4D_get_images_with_b_value(self.id, bVal)
        elif (type(diffusionDirection) != type(None)):
            if (type(diffusionDirection) == np.ndarray):
                diffusionDirection = diffusionDirection.tolist()
            assert(type(diffusionDirection) == list)
            assert(len(diffusionDirection) == 3)
            newImg.id = imageSrc.dwimage4D_get_images_with_diffusion_direction(self.id, diffusionDirection)

        return newImg

    def get_number_images(self, bVal = None, diffusionDirection = None):
        if (type(bVal) != type(None) and type(diffusionDirection) != type(None)):
            if (type(diffusionDirection) == np.ndarray):
                diffusionDirection = diffusionDirection.tolist()
            assert(type(diffusionDirection) == list)
            assert(len(diffusionDirection) == 3)
            return imageSrc.get_number_of_images_with_b_values_and_diffusions_directions(self.id, bVal, diffusionDirection)
        elif (type(bVal) != type(None)):
            return imageSrc.dwimage4D_get_number_of_images_with_b_value(self.id, bVal)
        elif (type(diffusionDirection) != type(None)):
            if (type(diffusionDirection) == np.ndarray):
                diffusionDirection = diffusionDirection.tolist()
            assert(type(diffusionDirection) == list)
            assert(len(diffusionDirection) == 3)
            return imageSrc.get_number_of_images_with_diffusion_direction(self.id, diffusionDirection)
        else:
            return imageSrc.dwimage4D_get_number_of_images(self.id)

    def append_dwi(self, dwImage):
        imageSrc.dwimage4D_append_dwimage(self.id, dwImage.get_id())

    def get_b_values(self, diffusionDirection = None):
        if (type(diffusionDirection) != type(None)):
            if (type(diffusionDirection) == np.ndarray):
                diffusionDirection = diffusionDirection.tolist()
            assert(type(diffusionDirection) == list)
            assert(len(diffusionDirection) == 3)
            return imageSrc.dwimage4D_get_b_values_with_diffusion_direction(self.id, diffusionDirection)
        else:
            return imageSrc.dwimage4D_get_b_values(self.id)

    def get_diffusion_directions(self, bVal = None):
        if (type(bVal) != type(None)):
            return imageSrc.dwimage4D_get_diffusion_directions_with_b_value(self.id)
        else:
            return imageSrc.dwimage4D_get_diffusion_directions(self.id)

    def get_at(self, i, j, k, imgID):
        return imageSrc.get_image3D_value(self.id, i, j, k, imgID)

    def __del__(self):
        imageSrc.delete_object(self.id)


def calculate_trace_weight_image(dwimage4D):
    newImg = DWImage4D()
    newImg.id = imageSrc.generate_trace_weight_dwimage4D(dwimage4D.get_id())
    return newImg