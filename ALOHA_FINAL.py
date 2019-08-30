import random
import pylab as pl
import numpy

import matplotlib.pyplot as plt


N = 1000

numbers = []
for i in range(N):
    a = random.uniform(0,1)
    print(a)
    numbers.append(a)

sorted_numbers = sorted(numbers)
G = pl.frange(0.0, 2.5, 0.015)
print(len(G))

S = []
for j in G:
    tc = 0
    for x in range(0,10): #number of simulation.
        count = 0
        for i in range(1, len(sorted_numbers) - 1):
            thp = sorted_numbers[i-1]
            thn = sorted_numbers[i+1]
            t = sorted_numbers[i]
            if t- thp > j/N and thn - t > j/N:
                count = count + 1
        tc +=count
    avgcount = tc/10
    S.append(avgcount * j/ N)
    
plt.plot(G, S)
plt.xlabel("G (attempts per packet time)")
plt.ylabel("S (Throughput per frame time)")
plt.show()
plt.title("G vs S Throughput for ALOHA")

