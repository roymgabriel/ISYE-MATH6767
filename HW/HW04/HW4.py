from typing import Union

import numpy as np


##############################################
############ Helper Functions ################
##############################################

def search_matrix(A: np.ndarray, x: int, y: int) -> None:
    """
    A Depth First Search (DFS) algo to traverse matrix A.

    :param A: a 2D numpy array of shape m-by-n that stands for the map of 0's, 1's
    :param x: row cursor to navigate matrix A
    :param y: column cursor to navigate matrix A
    :return: None -> The function is recursive and changes entries in A
    """
    # get dimensions of matrix A
    m, n = A.shape

    # check edge cases or error inputs
    if (x < 0) or (y < 0) or (x >= m) or (y >= n) or (A[x, y] != 1):
        return

    # change visited entries in A
    A[x, y] = 69

    # recurse
    search_matrix(A, x - 1, y)
    search_matrix(A, x + 1, y)
    search_matrix(A, x, y - 1)
    search_matrix(A, x, y + 1)


def get_num_islands(A: np.ndarray) -> int:
    """
    A function that counts how many green islands in matrix A. A green land is
    encircled by desert (0's) and is aggregated by connecting all its neighboring
    green lands horizontally or vertically.

    :param A: a 2D numpy array of shape m-by-n that stands for the map of 0's, 1's
    :return: An int representing the count of green islands
    """
    # Initialize count variable
    c = 0

    # get dimensions of matrix A
    m, n = A.shape

    # check edge case
    if (m == 0) or (n == 0):
        return c

    for x in range(m):
        for y in range(n):
            # if green land
            if A[x, y] == 1:
                c += 1
                search_matrix(A=A, x=x, y=y)
    return c


##############################################
############## Problem 1 #####################
##############################################

def calc_green_land(m: int, n: int, ind: Union[list, np.ndarray], verbose: bool = False) -> tuple[
    np.ndarray, np.ndarray]:
    """
    Problem 1 Function to solve Desert and Green Land problem.

    :param m: number of rows of an underlying matrix
    :param n: number of columns of an underlying matrix
    :param ind: an array of indices (x_i, y_i), where element (x_i, y_i) is transformed
                into a green land in the ith transformation
    :param verbose: a boolean to trigger whether to return transformed matrix or not
    :return: a list of integers p where p_i is the number of green lands after transforming
             element (x_i, y_i) into a green land
    """
    # Initialize Matrix A and output array list
    A = np.zeros([m, n])
    p = np.array([])

    # check if empty array or empty indices array
    if (m == 0) or (n == 0) or not ind:
        return np.array([0]), A if verbose else np.array([0])

    # transform element (x_i, y_i) and count number of green lands
    for x, y in ind:
        # change element (x_i, y_i)
        A[x, y] = 1

        # get num of green lands
        c = get_num_islands(A)
        p = np.append(p, c)

        # Trigger visited lands
        A = np.where(A == 69, 1, A)

    return (p, A) if verbose else p


##############################################
############## Problem 2 #####################
##############################################

def angry_cook(p: Union[list, np.ndarray], q: Union[list, np.ndarray], m: int) -> int:
    """
    A function that returns the maximum number of customers who received good service
    given an integer array that describes the number of customers that entered the restaurant
    at each hour (p) and a binary array at each hour of whether the cook was angry or not
    :param p: An integer array denoting the number of customers who entered at the ith hour
    :param q: A binary array denoting whether the cook is angry (1) or not (0)
    :param m: An integer denoting the number of hours of how long the cook can keep himself calm
              for m consecutive hours
    :return: An integer denoting the maximum number of customers who received good service.
             If the return value is -1, it means an error occured in the input.
    """

    # check incorrect inputs
    if (not p) or (not q) or (len(p) != len(q)):
        print("Either array p or q or both is/are invalid!")
        return -1

    # change to numpy arrays for easy math calculatinos
    p, q = np.array(p).astype(int), np.array(q).astype(int)

    # since 1 is angry, 0 is not, we multiply the arrays to get
    # total lost customers
    lost_customers = p * q

    # find maximum m-consecutive customers who could have received good service
    max_summed_loss = np.max(np.convolve(lost_customers, np.ones(m), 'valid'))

    # calculate original num customers who received good service
    won_customers = np.sum(p * np.where(q == 0, 1, 0))

    return int(max_summed_loss + won_customers)






