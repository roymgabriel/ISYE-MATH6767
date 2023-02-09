import unittest
from HW4 import *


class MyTestCase(unittest.TestCase):
    def test_problem1_1(self):
        m = n = 3
        ind = [[0, 0], [0, 1], [1, 2], [2, 1]]

        func_output = calc_green_land(m=m, n=n, ind=ind, verbose=True)

        print("Checking Problem 1 with parameter verbose = True...")
        print("Inputs:")
        print(f"m = {m}, n = {n}, ind = {ind}")
        print("\nOutputs:")
        print(func_output[0])
        print(func_output[1])
        a = np.array_equal(func_output[0], np.array([1, 1, 2, 3]))
        b = np.array_equal(func_output[1], np.array([[1, 1, 0], [0, 0, 1], [0, 1, 0]]))
        self.assertTrue(a)
        self.assertTrue(b)
        return (a == True) and (b == True)

    def test_problem1_2(self):
        m = n = 1
        ind = [[0, 0]]

        func_output = calc_green_land(m=m, n=n, ind=ind, verbose=True)

        print("Checking Problem 1 with parameter verbose = True...")
        print("Inputs:")
        print(f"m = {m}, n = {n}, ind = {ind}")
        print("\nOutputs:")
        print(func_output[0])
        print(func_output[1])
        a = np.array_equal(func_output[0], np.array([1]))
        b = np.array_equal(func_output[1], np.array([[1]]))
        self.assertTrue(a)
        self.assertTrue(b)
        return (a == True) and (b == True)

    def test_problem1_3(self):
        m = 6
        n = 5
        ind = [(0, 0), (1, 3), (2, 1), (3, 1), (4, 1), (4, 2), (4, 3)]

        func_output = calc_green_land(m=m, n=n, ind=ind, verbose=True)
        true_output = [[1, 0, 0, 0, 0],
                       [0, 0, 0, 1, 0],
                       [0, 1, 0, 0, 0],
                       [0, 1, 0, 0, 0],
                       [0, 1, 1, 1, 0],
                       [0, 0, 0, 0, 0]]

        print("Checking Problem 1 with parameter verbose = True...")
        print("Inputs:")
        print(f"m = {m}, n = {n}, ind = {ind}")
        print("\nOutputs:")
        print(func_output[0])
        print(func_output[1])
        a = np.array_equal(func_output[0], [1, 2, 3, 3, 3, 3, 3])
        b = np.array_equal(func_output[1].astype(int), np.array(true_output).astype(int))
        self.assertTrue(a)
        self.assertTrue(b)
        return (a == True) and (b == True)

    def test_problem2_1(self):
        p = [1, 0, 1, 2, 1, 1, 7, 5]
        q = [0, 1, 0, 1, 0, 1, 0, 1]
        m = 3

        func_output = angry_cook(p=p, q=q, m=m)

        print("Checking Problem 2...")
        print("Inputs:")
        print(f"p = {p}, q = {q}, m = {m}")
        print(f"\nOutput: {func_output}")

        self.assertEqual(func_output, 16)
        return func_output == 16

    def test_problem2_2(self):
        p = [1]
        q = [0]
        m = 1

        func_output = angry_cook(p=p, q=q, m=m)

        print("Checking Problem 2...")
        print("Inputs:")
        print(f"p = {p}, q = {q}, m = {m}")
        print(f"\nOutput: {func_output}")
        self.assertEqual(func_output, 1)
        return func_output == 1

    def test_problem2_3(self):
        p = [1, 2, 3, 4]
        q = [1, 1, 1, 1]
        m = 1

        func_output = angry_cook(p=p, q=q, m=m)

        print("Checking Problem 2...")
        print("Inputs:")
        print(f"p = {p}, q = {q}, m = {m}")
        print(f"\nOutput: {func_output}")
        self.assertEqual(func_output, 4)
        return func_output == 4


if __name__ == '__main__':
    unittest.main()
