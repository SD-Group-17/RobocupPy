from distutils.core import setup, Extension

module = Extension("Robocup",sources = ["wrapper.cpp"])

setup(name="Robocup",
    version = "1.0",
    description = "Robocup Python Libary",
    ext_modules =[module])

