#!/usr/bin/env python3

from prime import *
from random import randint


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
        print("Not coprime")
    if (a_ * a) % b == 1:
        print("Test extend_euclid pass.")

if __name__ == "__main__":
    test_extend_euclid(4, 93)
    test_extend_euclid(12, 18)
    test_extend_euclid(324134, 1234567)
    print("Generating an RSA key")
    n, e, d = RSA_genkey()
    data = 0x12345678
    data_enc = RSA_encrypt(n, e, data)
    data_enc_dec = RSA_encrypt(n, d, data_enc)
    if (data == data_enc_dec):
        print("RSA test ok")
