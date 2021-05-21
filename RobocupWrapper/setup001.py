from setuptools import setup,Extension


module = Extension("RobocupWrapper",sources = ["strategy.cc"])

setup(name="RobocupWrapper",
    version = "1.0",
    description = "Package description",
    extra_compile_args=['-std=c++11', '-v'],
    ext_modules =[module])
