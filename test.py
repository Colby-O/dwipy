import numpy as np
import matplotlib.pyplot as plt
import time
import os, sys
from dwipy.core.image3D import Image3D
from dwipy.core.DWImage import DWImage
from dwipy.core.DWImage4D import DWImage4D, calculate_trace_weight_image
from dwipy.dwi.models.MEM import fit_MEModel
from dwipy.dwi.models.IVIM import fit_IVIModel
#import dwipy.models as models


filename = "./dwidata.nii.gz"
bValues = [0 , 50, 50, 50, 100, 100, 100, 200, 200, 200, 500, 500, 500, 1000, 1000, 1000, 1500, 1500, 1500, 2000, 2000, 2000]
diffusionDirections = [[0, 0, 0], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1]]
i = DWImage4D(data = filename, bValues = bValues, diffusionDirections = np.array(diffusionDirections))

t = calculate_trace_weight_image(i)


start = time.time()
res = fit_IVIModel(t)
print("C++: ", time.time() - start)


plt.imshow(res.adcMap.get_data()[:, :, 10].T * 1e6,vmin = 0, vmax = 2500, cmap='gray')
plt.colorbar()
plt.title("ADC Map")
plt.show()

plt.imshow(res.dMap.get_data()[:, :, 10].T * 1e6, vmin = 0, vmax = 20000, cmap='gray')
plt.colorbar()
plt.title("D* Map")
plt.show()

plt.imshow(res.fMap.get_data()[:, :, 10].T, vmin =0, vmax = 1, cmap='gray')
plt.colorbar()
plt.title("f Map")
plt.show()

plt.imshow(res.s0Map.get_data()[:, :, 10].T, vmin = 0, cmap='gray')
plt.colorbar()
plt.title("s0 Map")
plt.show()

plt.imshow(res.chiSquaredMap.get_data()[:, :, 10].T, vmax = 10, cmap='gray')
plt.colorbar()
plt.title("Chi-Squared Map")
plt.show()


#print(res.adcMap.get_data())

#plt.imshow(res.adcMap.get_data()[:, :, 10].T)
#plt.colorbar()
#plt.show()
