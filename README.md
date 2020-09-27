# dotprod
loop testing

run the following commands to record max timings over 10 runs

```
sys=someName
for i in {0..10}; do ./dotprod ; done &> ${sys}.log
awk 'BEGIN {a=0;c=0;d=0;t=0}{\
a=($5>a ? $5 : a); \
c=($6>c ? $6 : c); \
d=($7>d ? $7 : d); \
t=($8>t ? $8 : t)} \
END{print "max (sec) alloc compute dealloc total " a " " c " " d " " t}' ${sys}.log
```

## turtle

Ryzen 5 3600
GCC 10.1.0

```
max (sec) alloc compute dealloc total 0.00860 0.20777 0.00001 0.21611
```

## aimos

Power9
GCC 8.4.0

```
```

allocate and build

```
$ salloc -N 1 --gres=gpu:4 -t 10
$ ssh <computeNode>
$ module load gcc
$ g++ -O3 dotprod.cpp -o dotprod
```
