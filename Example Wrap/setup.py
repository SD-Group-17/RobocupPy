from distutils.core import setup, Extension

module = Extension("myModule",sources = ["myModule.cpp"])

setup(name="PackageName",
    version = "1.0",
    description = "Package description",
    ext_modules =[module])

