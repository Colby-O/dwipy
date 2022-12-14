import os
import sys
import numpy as np

currentdir = os.path.dirname(os.path.realpath(__file__))
parentdir = os.path.dirname(os.path.dirname(currentdir))
sys.path.append(parentdir)

import dwipy.core.imageSrc as modelsSrc
from dwipy.core.DWImage4D import DWImage4D
from dwipy.core.image3D import Image3D

class MEMResult:
    def __init__(self, adcMapID, s0MapID, chiSquaredMapID, avgADC, stdADC, avgS0, stdS0, avgChiSquared, stdChiSquared):
        adcMap = Image3D()
        adcMap.id = adcMapID

        s0Map = Image3D()
        s0Map.id = s0MapID

        chiSquaredMap = Image3D()
        chiSquaredMap.id = chiSquaredMapID

        self.adcMap = adcMap
        self.s0Map = s0Map
        self.chiSquaredMap = chiSquaredMap
        self.avgADC = avgADC
        self.avgS0 = avgS0
        self.avgChiSquared = avgChiSquared
        self.stdADC = stdADC
        self.stdS0 = stdS0
        self.stdChiSquared = stdChiSquared


def fit_MEModel(dwiSet):
    res = modelsSrc.fit_MEM(dwiSet.get_id())
    return MEMResult(*res)
