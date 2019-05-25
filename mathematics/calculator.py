# Common mathematical functions

from math import *


def combinations(n, k):
    num = factorial(n)
    den = factorial(k) * factorial(n - k)
    return num // den

# n-th fibonacci, 1 indexed
def fibonacci(n, a0=0, a1=1):
    if n == 1:
        return a0
    if n == 2:
        return a1
    for i in range(3, n + 1):
        a = a0 + a1
        a0 = a1
        a1 = a
    return a

def fibonacci_up_to(n, a0=0, a1=1):
    if n == 1:
        return [a0]
    if n == 2:
        return [a1]
    res = [0] * n
    res[0] = a0
    res[1] = a1
    for i in range(2, n):
        a = a0 + a1
        res[i] = a

        a0 = a1
        a1 = a
    return res

def primes(n, MAX_PRIME=10**5):
    isprime = [True] * (MAX_PRIME + 1)
    p = []
    for i in range(2, MAX_PRIME + 1):
        if isprime[i]:
            p.append(i)
            if len(p) == n:
                return p
            for j in range(i * i, len(isprime), i):
                isprime[j] = False
