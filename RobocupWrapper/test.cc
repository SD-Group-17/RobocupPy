#include <vector>
#include <cmath>
#include <stdio.h>
#include <Python.h>
#include "pyhelper.hpp"
#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <iostream>
#define PY_SSIZE_T_CLEAN

using namespace std;

//Calls python function selectSkill() in strategy.py and prints the output
int selectSkill(){
    CPyInstance hInstance;

	CPyObject pName = PyUnicode_FromString("strategy"); //name of python file
	CPyObject pModule = PyImport_Import(pName);

	if(pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "selectSkill"); //name of python function
		if(pFunc && PyCallable_Check(pFunc))
		{
			CPyObject pValue = PyObject_CallObject(pFunc, NULL); //output of python function as c++ object

			return (int) PyLong_AsLong(pValue);
		}
		else
		{
			cout << "ERROR: function selectSkill()\n";
            return -1;
		}

	}
	else
	{
		cout << "ERROR: Module not imported\n";
        return -1;
	}
}


TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   FAIL("Fail me!");
}

TEST(FirstTestGroup, SecondTest)
{
    STRCMP_EQUAL("hello", "hello");
}

int main(int ac, char** av){
    int val = selectSkill();
    cout << "Selected skill: "<<val<<endl;

    return CommandLineTestRunner::RunAllTests(ac, av);
}