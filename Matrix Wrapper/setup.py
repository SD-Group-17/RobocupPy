from distutils.core import setup, Extension

module = Extension("matrixModule",sources = ["matrixModule.cpp"])

setup(name="matrixModule",
    version = "1.0",
    description = "Package description",
    ext_modules =[module])