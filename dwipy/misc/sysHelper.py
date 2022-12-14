import os
import numpy as np
import nibabel as nib
import nrrd

class sysHelpers:
    def splitext(path):
        for ext in ['.nii.gz']:
            if path.endswith(ext):
                return path[:-len(ext)], path[-len(ext):]
        return os.path.splitext(path)

    def getDataFromFile(filename):
        if(type(filename) == type(None)):
            raise Exception("No File Directory Defined In Image Class!")
        
        extension = sysHelpers.splitext(filename)[1][1:]
        
        if(extension != 'nrrd' and extension != 'nhdr' and extension !='nii.gz' and extension != '.nii'):
            raise Exception("The file extension '{}' is invaild!".format(extension))

        if (extension == 'nrrd' or extension == 'nhdr'):
            data, header = nrrd.read(filename)
            return data
            
        if (extension =='nii.gz' or extension == '.nii'):
            image = nib.load(filename)
            data = image.get_fdata()
            data = np.flip(data, 1)
            return data