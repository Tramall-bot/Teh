from unittest import TestCase
from main import  fun

class TestFun(TestCase):
    def test_fun(self):
        print("test")
        self.assertEqual(fun(1), 1)
        self.assertEqual(fun(0), 0)
        self.assertEqual(fun(2), 1)
        self.assertEqual(fun(3), 2)
        self.assertEqual(fun(4), 3)
        self.assertEqual(fun(5), 5)
