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

def primes(n=-1, MAX_PRIME=10**6):
    isprime = [True] * (MAX_PRIME + 1)
    p = []
    for i in range(2, MAX_PRIME + 1):
        if isprime[i]:
            p.append(i)
            if len(p) == n:
                return p
            for j in range(i * i, len(isprime), i):
                isprime[j] = False
    return p

def factorize(n):
    factors = dict()
    prims = primes(MAX_PRIME=n)
    for p in prims:
        exp = 0
        while n % p == 0:
            n = n // p
            exp += 1
        if exp > 0:
            factors[p] = exp
    return factors

def divisors(n):
    sqn = int(sqrt(n))
    divs = []
    for p in range(1, sqn + 1):
        if n % p == 0:
            divs.append(p)
            q = n // p
            if q != p:
                divs.append(q)
    return sorted(divs)
