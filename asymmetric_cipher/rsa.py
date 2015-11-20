#!/usr/bin/env python3

from prime import *
from random import randint
import sys
sys.setrecursionlimit(5000)


def extend_euclid(a, x):
    # x = a*q0+r0 => r0 = x-a*q0 = x*1+a*(-q0)
    # a = r0*q1+r1 => r1 = a-r0*q1 = x*(-q1)+a*(1+q0*q1)
    # r0 = r1*q2+r2 => r2 = r0-r1*q2
    x_orig = x
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


def gen_coprime_pair(x):
# generate a number coprime with x, and its reverse
    e = randint(2, x - 1)
    d = extend_euclid(e, x)
    while d == 0:
        e = randint(2, x - 1)
        d = extend_euclid(e, x)
    return e, d


def RSA_genkey():
# generate RSA key
    r1 = randint(2 ** 480, 2 ** 512)
    r2 = randint(2 ** 480, 2 ** 512)

    p1 = nearest_prime_bigger(r1)
    p2 = nearest_prime_bigger(r2)
    n = p1 * p2
    euler = (p1 - 1) * (p2 - 1)
    e, d = gen_coprime_pair(euler)
    # public key is n,e
    # private key is d
    return n, e, d


def RSA_encrypt(n, e, data):
    return expmod(data, e, n)


# The following is testing

def test_extend_euclid(a, b):
    a_ = extend_euclid(a, b)
    if a_ == 0:
        print ("Not coprime")
    if (a_ * a) % b == 1:
        print ("Test extend_euclid pass.")

if __name__ == "__main__":
    test_extend_euclid(4, 93)
    test_extend_euclid(12, 18)
    test_extend_euclid(324134, 1234567)
    print ("Generating an RSA key")
    n, e, d = RSA_genkey()
    data = 0x12345678
    data_enc = RSA_encrypt(n, e, data)
    data_enc_dec = RSA_encrypt(n, d, data_enc)
    if (data == data_enc_dec):
        print ("RSA test ok")
