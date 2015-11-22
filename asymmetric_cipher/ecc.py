#!/usr/bin/env python3

from prime import *
from rsa import extend_euclid


def newEC(a, b, p):
    if (miller_rabin_test(p) == 1 and (4 * a * a * a + 27 * b * b) % p != 0):
        return a, b, p
    else:
        return 0, 0, 0


def EC_add(ec, p1, p2):
    a, pp = ec[0], ec[2]
    Opoint = (pp, pp)
    x1, y1 = p1[0], p1[1]
    x2, y2 = p2[0], p2[1]

    if (p1 == Opoint):
        return p2

    if (p2 == Opoint):
        return p1

    if (x2 == x1 and (y2 + y1) % pp == 0):
        return Opoint  # the O point

    if (p1 != p2):
        l = (y2 - y1) * extend_euclid(x2 - x1, pp)
        l = l % pp
    else:
        l = (3 * x1 * x1 + a) * extend_euclid(2 * y1, pp)
        l = l % pp

    x3 = l * l - x1 - x2
    y3 = l * (x1 - x3) - y1
    return (x3 % pp), (y3 % pp)


def EC_exp(ec, p, exp):
    if (exp == 0):
        return ec[2], ec[2]

    if (exp % 2 == 0):
        r = EC_exp(ec, p, exp // 2)
        return EC_add(ec, r, r)
    else:
        r = EC_exp(ec, p, exp // 2)
        t = EC_add(ec, r, r)
        return EC_add(ec, p, t)

if __name__ == "__main__":
    print("Testing Elliptic Curve")
    test_curve = newEC(1, 6, 11)
    print(test_curve)
    alpha = (2, 7)
    print(EC_add(test_curve, (2, 7), (3, 5)))
    for i in range(0, 27):
        print(EC_exp(test_curve, alpha, i))
