from setuptools import setup,Extension


module = Extension("RobocupWrapper",sources = ["behaviors/strategy.cc","particlefilter/PFLocalization.cc"])

setup(name="RobocupWrapper",
    version = "1.0",
    description = "Package description",
    ext_modules =[module])