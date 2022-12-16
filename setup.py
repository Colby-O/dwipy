from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from pathlib import Path
import subprocess
import os, sys
import platform

options = {}
cmake_cmd_args = []

def get_cmake_version(cmake_path):
    dirs = os.listdir(cmake_path)
    return dirs[0]

class CMakeExtension(Extension):
    def __init__(self, name, cmake_lists_dir = '.', **kwag):
        Extension.__init__(self, name, sources = list(), **kwag)
        self.cmake_lists_dir = os.path.abspath(cmake_lists_dir)

class CustomBuildExtension(build_ext):
    def build_extensions(self):
        if (self.compiler.compiler_type == 'msvc'):
            raise Exception("Visual Studio is not supported")

        for e in self.extensions:
            e.extra_compile_args = ['--pedantic']
            e.extra_link_args = ['-lgomp']

        build_ext.build_extensions(self)

class CMakeBuildExtension(CustomBuildExtension):
    def build_extensions(self):
        # Check if CMake is working a persent on System
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError('Cannot find CMake executable')

        for ext in self.extensions:

            extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
            cfg = 'Debug' if options['--debug'] == 'ON' else 'Release'

            cmake_args = [
                '-DCMAKE_BUILD_TYPE=%s' % cfg,
                '-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir),
                '-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), self.build_temp),
                '-DPYTHON_EXECUTABLE={}'.format(sys.executable),
            ]

            if (platform.system() == 'Windows'):
                plat = ('x64' if platform.architecture()[0] == '64bit' else 'Win32')
                cmake_args += [
                    '-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE',
                    '-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir),
                ]
                if (self.compiler.compiler_type == 'msvc'):
                    cmake_args += [
                        '-DCMAKE_GENERATOR_PLATFORM=%s' % plat,
                    ]
                else:
                    cmake_args += [
                        '-G', 'MinGW Makefiles',
                    ]

            cmake_args += cmake_cmd_args

            if (not os.path.exists(self.build_temp)):
                os.makedirs(self.build_temp)
            
            # M1/M2 macbook will need to install x86_64 cmake via arch
            # TODO: Fix this
            if (platform.system() == "Darwin"):
                cmake_root_path = "/usr/local/homebrew/Cellar/cmake/"
                cmake_version = get_cmake_version("/usr/local/homebrew/Cellar/cmake/")
                cmake_command = "{0}{1}/bin/cmake".format(cmake_root_path, cmake_version)
            else:
                cmake_command = "cmake"

            # Config
            subprocess.check_call([cmake_command, ext.cmake_lists_dir] + cmake_args,
                                  cwd=self.build_temp)

            # Build
            subprocess.check_call([cmake_command, '--build', '.', '--config', cfg],
                                  cwd=self.build_temp)

if (__name__ == "__main__"):
    options['--debug'] = 'OFF'
    for f in sys.argv:
        if f.startswith('-D'):
            cmake_cmd_args.append(f)

    for f in cmake_cmd_args:
        sys.argv.remove(f)

    setup(name = "dwipy",
        version = "0.1",
        package_dir={"": "src"}, 
        ext_modules = [CMakeExtension("dwipySrc", "./")],
        cmdclass = {'build_ext': CMakeBuildExtension},
        )