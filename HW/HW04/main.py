from HW4 import *

def main():
    print("Testing Problem 1...")
    m = n = 3
    ind = [[0, 0], [0, 1], [1, 2], [2, 1]]

    print("Inputs:")
    print(f"m = {m}, n = {n}, ind = {ind}")

    func_output = calc_green_land(m=m, n=n, ind=ind, verbose=True)
    print("\nOutputs:")
    print("p-array:")
    print(func_output[0])
    print("\nMatrix after changing entry (x_i, y_i)")
    print(func_output[1])

    print("\nTesting Problem 1 (different input)...")
    m = n = 1
    ind = [[0, 0]]

    print("Inputs:")
    print(f"m = {m}, n = {n}, ind = {ind}")

    func_output = calc_green_land(m=m, n=n, ind=ind, verbose=True)
    print("\nOutput:")
    print("p-array:")
    print(func_output[0])
    print("\nMatrix after changing entry (x_i, y_i)")
    print(func_output[1])

    print("\nTesting Problem 2...")
    p = [1, 0, 1, 2, 1, 1, 7, 5]
    q = [0, 1, 0, 1, 0, 1, 0, 1]
    m = 3

    print("Inputs:")
    print(f"p = {p}, q = {q}, m = {m}")

    func_output = angry_cook(p=p, q=q, m=m)

    print("\nOutput:")
    print(f"Number of Satisfied Customers: {func_output}")

    print("\nTesting Problem 2 (different inputs)...")
    p = [1]
    q = [0]
    m = 1

    print("Inputs:")
    print(f"p = {p}, q = {q}, m = {m}")

    func_output = angry_cook(p=p, q=q, m=m)

    print("\nOutput:")
    print(f"Number of Satisfied Customers: {func_output}")

    print("\nRunning Unit Tests...\n")

if __name__ == '__main__':
    main()
    import unit_test

    tester = unit_test.MyTestCase()

    print(tester.test_problem1_1())
    print(tester.test_problem1_2())
    print(tester.test_problem1_3())
    print(tester.test_problem2_1())
    print(tester.test_problem2_2())
    print(tester.test_problem2_3())

