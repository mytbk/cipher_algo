#!/usr/bin/env python3

from random import randint
import sys
sys.setrecursionlimit(5000)

# Miller-Rabin test:
# for a number n, n-1=t*2^k, and a number a<n
# if a^t!=1 and a^(t*2^i)!=-1 for 0<=i<=k-1
# then n is not prime number


def expmod(a, exp, mod):
    if (exp == 0):
        return 1

    if (exp % 2 == 0):
        r = expmod(a, exp // 2, mod)
        return (r * r) % mod
    else:
        r = expmod(a, (exp - 1) // 2, mod)
        return (a * r * r) % mod


def miller_rabin_expmod(a, exp, mod):
    if (exp % 2 == 0):
        pa, r = miller_rabin_expmod(a, exp // 2, mod)
        if (pa == 1):
            return 1, r
        else:
            pass
        # didn't pass the test for small exp, continue testing
        e = (r * r) % mod
        if (e == mod - 1):  # pass the test
            return 1, e
        else:
            return 0, e
    else:  # exp is an odd number, just do the exp
        r = expmod(a, exp, mod)
        if (r == 1 or r == mod - 1):  # pass the test
            return 1, r
        else:
            return 0, r


def miller_rabin_test_base(p, a):
    pa, r = miller_rabin_expmod(a, (p - 1) // 2, p)
    if pa == 1:
        return 1
    else:
        return 0


def miller_rabin_test(p):
    if p == 2:
        return 1
    elif p % 2 == 0:
        return 0

    passes = 100
    while passes > 0:
        passes = passes - 1
        randnum = randint(2, p - 1)
        if (miller_rabin_test_base(p, randnum) == 0):
            return 0
    return 1


def nearest_prime_bigger(x):
    if x % 2 == 0:
        x = x + 1

    while (miller_rabin_test(x) == 0):
        x = x + 2

    return x


def nearest_prime_smaller(x):
    if x % 2 == 0:
        x = x - 1

    while (miller_rabin_test(x) == 0):
        x = x - 2

    return x

# Extend Euclid algorithm
# given the number x and a, calculate b, s.t. ab=1 (mod x)
# if (a,x)!=1 return 0


def extend_euclid(a, x):
    # x = a*q0+r0 => r0 = x-a*q0 = x*1+a*(-q0)
    # a = r0*q1+r1 => r1 = a-r0*q1 = x*(-q1)+a*(1+q0*q1)
    # r0 = r1*q2+r2 => r2 = r0-r1*q2
    x_orig = x
    a = a % x

    if a == 1:
        return 1

    x0, a0 = 1, 0
    x1, a1 = 0, 1
    while True:
        r, q = x % a, x // a
        x2, a2 = x0 * 1 - q * x1, a0 * 1 - q * a1
        x0, a0, x1, a1 = x1, a1, x2, a2 % x_orig
        if r == 1:  # (a,x)=1 and a^(-1)=a1 is found
            return a1
        if r == 0:  # (a,x)=a, a!=1
            return 0
        # continue the calculation
        a, x = r, a


# test
if __name__ == "__main__":
    print('Testing expmod')
    print(expmod(3, 2171950143037921457539 - 1, 2171950143037921457539))
    # should be 1
    print(expmod(19, 333333, 32767))
    print((19 ** 333333) % 32767)
    print(expmod(123423524523452345245423, 4298,
                 572934875293875284795827495728345947502745))
    print((123423524523452345245423 ** 4298) %
          572934875293875284795827495728345947502745)
    print('Testing Miller-Rabin test')
    print(miller_rabin_test(561))  # not prime
    print(miller_rabin_test(85329136972542481))  # prime
    print(miller_rabin_test(2171950143037921457539))  # prime
    print(miller_rabin_test(398572398798745928751524351))  # not prime

    print(nearest_prime_bigger(1234567890))
    print(nearest_prime_smaller(1234567890))
