from distutils.core import setup, Extension

module = Extension("myModule",sources = ["myModule.cpp"])

setup(name="myModule",
    version = "1.0",
    description = "Fibonacci",
    ext_modules =[module])

