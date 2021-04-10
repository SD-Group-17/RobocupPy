from distutils.core import setup, Extension

module = Extension("matrixModule",sources = ["matrix.cpp"])

setup(name="matrixModule",
    version = "0.1",
    description = "Matrix operations",
    ext_modules =[module])