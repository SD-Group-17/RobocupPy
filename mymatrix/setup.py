from distutils.core import setup, Extension

module = Extension("myMatrix",sources = ["mymatrix.cpp"])

setup(name="myMatrix",
    version = "0.1",
    description = "Matrix operations",
    ext_modules =[module])