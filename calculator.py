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

def derrangement(n):
    if n == 0:
        return 1
    if n == 1:
        return 0
    a = 1
    b = 0
    c = 0
    for i in range(2, n + 1):
        c = (i - 1) * (a + b)
        a = b
        b = c
    return c

def primes_up_to(n):
    n += 1
    primes = []
    sieve = [True for i in range(n)]
    for i in range(2, n):
        if sieve[i]:
            primes.append(i)
            for j in range(i * i, n, i):
                sieve[j] = False
    return primes

def factorize(n):
    primes = primes_up_to(int(sqrt(n) + 5))
    factors = {}
    for p in primes:
        if p > n:
            break
        count = 0
        while n % p == 0:
            count += 1
            n /= p
        if count > 0:
            factors[p] = count
    if n > 1:
        factors[n] = 1
    return factors
