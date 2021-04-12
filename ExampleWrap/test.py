import pytest
import myModule
import os 

def testFirst():
    wanted_result = 0
    test_result = myModule.fib(0)
    assert(wanted_result == test_result), "Test Failed"

def testSmall():
    wanted_result = 4181
    test_result = myModule.fib(19)
    assert(wanted_result == test_result), "Test Failed"

def testMedium():
    wanted_result = 317811
    test_result = myModule.fib(28)
    assert(wanted_result == test_result), "Test Failed"

def testLarge():
    wanted_result = 102334155
    test_result = myModule.fib(40)
    assert(wanted_result == test_result), "Test Failed"

