import os
import sys
import numpy as np

import dwipySrc as modelsSrc
from dwipy.core.DWImage4D import DWImage4D
from dwipy.core.image3D import Image3D

class IVIMResult:
    def __init__(self, adcMapID, dMapID, fMapID, s0MapID, chiSquaredMapID):
        adcMap = Image3D()
        adcMap.id = adcMapID

        s0Map = Image3D()
        s0Map.id = s0MapID

        dMap = Image3D()
        dMap.id = dMapID

        fMap = Image3D()
        fMap.id = fMapID

        chiSquaredMap = Image3D()
        chiSquaredMap.id = chiSquaredMapID

        self.adcMap = adcMap
        self.s0Map = s0Map
        self.dMap = dMap
        self.fMap = fMap
        self.chiSquaredMap = chiSquaredMap

def fit_IVIModel(dwiSet):
    res = modelsSrc.fit_IVIM(dwiSet.get_id())
    return IVIMResult(*res)
