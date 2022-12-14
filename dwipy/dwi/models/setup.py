from distutils.core import setup, Extension
from pathlib import Path
import os

def findCppFiles(path = './'):
    return [str(path) for path in Path(path).rglob('*.cpp')]


sourceFiles = findCppFiles(path = './') 
sourceFiles.append("../misc/src/object.cpp") 
sourceFiles.append("../math/regression/linearregression.cpp") 

module = Extension("dwiModelsSrc", sources = sourceFiles, language='c++', extra_compile_args=['-std=c++17', '-O3', "-lstdc++"], undef_macros=['NDEBUG'])

setup(name = "dwiModelsSrc", version = "0.01", description = "Test c function", ext_modules = [module])
