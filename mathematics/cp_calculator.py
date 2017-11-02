from math import *

def binom(n, k, mod = 0):
    num = factorial(n)
    den = factorial(k) * factorial(n - k)
    res = num / den
    if mod != 0:
        res %= mod
    return res

def fibonacci(n):
    a = 0
    if n == 0:
        return a
    b = 1
    for i in range(2, n + 1):
        ab = a + b
        a = b
        b = ab
    return b

def catalan(n):
    den = (n + 1)
    num = binom(2 * n, n)
    res = num / den
    return res
