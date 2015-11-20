#!/usr/bin/env python3

from random import randint

# Miller-Rabin test: 
# for a number n, n-1=t*2^k, and a number a<n
# if a^t!=1 and a^(t*2^i)!=-1 for 0<=i<=k-1
# then n is not prime number

def expmod(a, exp, mod):
        if (exp==0):
                return 1
                
        if (exp%2==0):
                r = expmod(a, exp//2, mod)
                return (r*r)%mod
        else:
                r = expmod(a, (exp-1)//2, mod)
                return (a*r*r)%mod

def miller_rabin_expmod(a,exp,mod):
        if (exp%2==0):
                pa, r = miller_rabin_expmod(a, exp//2, mod)
                if (pa==1):
                        return 1, r
                else:
                        pass
                # didn't pass the test for small exp, continue testing
                e = (r*r)%mod
                if (e==mod-1): # pass the test
                        return 1, e
                else:
                        return 0, e
        else: # exp is an odd number, just do the exp
                r = expmod(a, exp, mod)
                if (r==1 or r==mod-1): # pass the test
                        return 1,r
                else:
                        return 0,r

def miller_rabin_test_base(p,a):
        pa, r = miller_rabin_expmod(a, (p-1)//2, p)
        if pa==1:
                return 1
        else:
                return 0

def miller_rabin_test(p):
        passes = 100
        while passes>0:
                passes = passes - 1
                randnum = randint(2,p-1)
                if (miller_rabin_test_base(p,randnum)==0):
                        return 0
        return 1

## test
if __name__ == "__main__":
	print ('Testing expmod')
	print (expmod(3,2171950143037921457539-1,2171950143037921457539)) # should be 1
	print (expmod(19, 333333, 32767))
	print ((19**333333)%32767)
	print (expmod(123423524523452345245423, 4298, 572934875293875284795827495728345947502745))
	print ((123423524523452345245423**4298)%572934875293875284795827495728345947502745)
	print ('Testing Miller-Rabin test')
	print (miller_rabin_test(561)) # not prime
	print (miller_rabin_test(85329136972542481)) # prime
	print (miller_rabin_test(2171950143037921457539)) # prime
	print (miller_rabin_test(398572398798745928751524351)) # not prime
