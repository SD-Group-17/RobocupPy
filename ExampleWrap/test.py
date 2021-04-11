import unittest
import myModule

class TestFibonacci(unittest.TestCase):

    def testFirst(self):
        wanted_result = 0
        test_result = myModule.fib(0)
        self.assertEqual(wanted_result,test_result)

    def testSmall(self):
        wanted_result = 4181
        test_result = myModule.fib(19)
        self.assertEqual(wanted_result,test_result)

    def testMedium(self):
        wanted_result = 317811
        test_result = myModule.fib(28)
        self.assertEqual(wanted_result,test_result)

    def testLarge(self):
        wanted_result = 102334155
        test_result = myModule.fib(40)
        self.assertEqual(wanted_result,test_result)


if __name__ == '__main__':
    unittest.main()

#x = int(input("Enter a number"))
#y = int(input("Enter a number"))
#print(myModule.fib(x))
#print(myModule.add(x,y))
