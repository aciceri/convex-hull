#!/bin/python


from subprocess import call
from random import uniform

m = -10
M = 10
n=10

with open("points.dat", "w") as f:
    for i in range(n):
        f.write("{} {}\n".format(uniform(m, M), uniform(m, M)))


call(["make", "plot"])
