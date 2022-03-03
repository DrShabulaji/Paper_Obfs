import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import z3
import math
import time

def isPN(a):
    for i in range(2, int(math.sqrt(a))):
        if a % i == 0:
            return False
    return True

def getPN(a):
    i = 1
    while not isPN(a + i):
        i += 1
    return a + i

X = []
Y = []

a1 = z3.BitVec("x", 32)
a2 = z3.BitVec("y", 32)
z3.set_param("timeout", 300 * 1000)
p1 = getPN(10 ** 4 + 3482)
for i in range(0, 10):
    p2 = getPN(10 ** i)
    X.append(int(math.log10(p1 * p2)))
    s = z3.Solver()
    s.add(a1 * a2 == p1 * p2)
    s.add(a1 != 1)
    s.add(a2 != 1)
    s.add(z3.ULT(a1, p1 * p2))
    s.add(z3.ULT(a2, p1 * p2))
    s.add(z3.ZeroExt(32, a1) * z3.ZeroExt(32, a2) == p1 * p2)
    t1 = time.time()
    s.check()

    t2 = time.time()
    print(p1, p2, p1 * p2, t2 - t1)

    Y.append(int(t2 - t1))


fig1 = plt.figure()
ax = fig1.add_subplot(1, 1, 1)
ax.set_xlabel("The order of magnitude of a large number")
ax.set_ylabel("The time for z3-solver to find the factors")
plt.scatter(X, Y, s=6, c="b")
plt.plot(X, Y, c="y")
plt.show()






