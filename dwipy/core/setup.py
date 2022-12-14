from distutils.core import setup, Extension
from pathlib import Path
import os

for path in Path('src').rglob('*.c'):
    print(path.name)

def findCppFiles(path = './'):
    return [str(path) for path in Path(path).rglob('*.cpp')]

#os.environ["CC"] = "gcc"

sourceFiles = findCppFiles(path = './') 
#["./src/image.cpp", "./src/image3D.cpp", "./src/image2D.cpp", './src/dwimage.cpp',  './src/interface.cpp', './src/image3DInterface.cpp']#findCppFiles()
sourceFiles.extend(findCppFiles(path = "../dwi/models/"))
#sourceFiles.append("../misc/src/object.cpp") 
sourceFiles.append("../math/src/regression/linearregression.cpp")
sourceFiles.append("../math/src/regression/curvefit.cpp")

# TODO: Need to find this
projectDir = "/Users/colbyokeefe/Desktop/dwipy/"

module = Extension("imageSrc", sources = sourceFiles, language='c++', libraries = ["m", "gsl", "gslcblas"], library_dirs = ["/usr/local/homebrew/Cellar/gsl/2.7.1/lib"], include_dirs = [projectDir, "/usr/local/homebrew/Cellar/gsl/2.7.1/include/"], extra_compile_args=['-std=c++17', '-O3'], undef_macros=['NDEBUG'])

setup(name = "image", version = "0.01", description = "Test c function", ext_modules = [module])
