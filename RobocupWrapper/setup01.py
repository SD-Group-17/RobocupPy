from setuptools  import setup,Extension
# import os
# import sysconfig

# extra_compile_args = sysconfig.get_config_var('CFLAGS').split()
#extra_compile_args += ['-std=c++11', '-v'],
# include_dirs=['-I/usr/include/CppUTest', '-I/usr/include/CppUTestExt', os.path.join(os.getcwd(), 'include')]  
# library_dirs=['-lCppUTest', '-lCppUTestExt']
language = 'c++11'
#module = Extension("RobocupWrapper",sources = ["strategy.cc"],include_dirs=include_dirs,library_dirs=library_dirs,extra_compile_args=extra_compile_args,language=language )

module = Extension("RobocupWrapper",sources = ["strategy.cc"])


setup(name="RobocupWrapper",
    version = "1.0",
    description = "Package description",
    extra_compile_args = ['-std=c++11', '-v'],
    ext_modules =[module]
    )