# dotprod
loop testing

## turtle

Ryzen 5 3600
GCC 10.1.0

```
$ g++ -O3 dotprod.cpp -o dotprod
$ for i in {0..10}; do ./dotprod ; done &> turtle.log
$ cat turtle.log;
alloc(s) compute(s) dealloc(s) total(s) 0.00840 0.20469 0.00000 0.21309
alloc(s) compute(s) dealloc(s) total(s) 0.00817 0.20175 0.00001 0.20992
alloc(s) compute(s) dealloc(s) total(s) 0.00812 0.20318 0.00000 0.21130
alloc(s) compute(s) dealloc(s) total(s) 0.00811 0.20462 0.00000 0.21273
alloc(s) compute(s) dealloc(s) total(s) 0.00814 0.20240 0.00000 0.21055
alloc(s) compute(s) dealloc(s) total(s) 0.00813 0.20258 0.00000 0.21072
alloc(s) compute(s) dealloc(s) total(s) 0.00815 0.20441 0.00000 0.21256
alloc(s) compute(s) dealloc(s) total(s) 0.00815 0.20138 0.00000 0.20953
alloc(s) compute(s) dealloc(s) total(s) 0.00812 0.20198 0.00000 0.21010
alloc(s) compute(s) dealloc(s) total(s) 0.00811 0.20264 0.00000 0.21076
alloc(s) compute(s) dealloc(s) total(s) 0.00817 0.20388 0.00001 0.21206
$ awk 'BEGIN {a=0;c=0;d=0;t=0}{\
a=($5>a ? $5 : a); \
c=($6>c ? $6 : c); \
d=($7>d ? $7 : d); \
t=($8>t ? $8 : t)} \
END{print "max (sec) alloc compute dealloc total " a " " c " " d " " t}' turtle.log
max (sec) alloc compute dealloc total 0.00840 0.20469 0.00001 0.21309
```

## aimos

Power9
GCC 8.4.0

```
$ salloc -N 1 --gres=gpu:4 -t 10
$ ssh <computeNode>
$ module load gcc
$ g++ -O3 dotprod.cpp -o dotprod
$ for i in {0..10}; do ./dotprod ; done &> p9.log
$ cat p9.log
alloc(s) compute(s) dealloc(s) total(s) 0.00499 0.35648 0.00004 0.36151
alloc(s) compute(s) dealloc(s) total(s) 0.00496 0.35351 0.00004 0.35851
alloc(s) compute(s) dealloc(s) total(s) 0.00497 0.35365 0.00003 0.35865
alloc(s) compute(s) dealloc(s) total(s) 0.00492 0.35645 0.00004 0.36140
alloc(s) compute(s) dealloc(s) total(s) 0.00503 0.35458 0.00003 0.35964
alloc(s) compute(s) dealloc(s) total(s) 0.00503 0.35329 0.00003 0.35836
alloc(s) compute(s) dealloc(s) total(s) 0.00501 0.35579 0.00004 0.36084
alloc(s) compute(s) dealloc(s) total(s) 0.00504 0.35629 0.00004 0.36137
alloc(s) compute(s) dealloc(s) total(s) 0.00501 0.35596 0.00004 0.36101
alloc(s) compute(s) dealloc(s) total(s) 0.00500 0.35655 0.00004 0.36159
alloc(s) compute(s) dealloc(s) total(s) 0.00497 0.35315 0.00003 0.35815
$ awk 'BEGIN {a=0;c=0;d=0;t=0}{\
a=($5>a ? $5 : a); \
c=($6>c ? $6 : c); \
d=($7>d ? $7 : d); \
t=($8>t ? $8 : t)} \
END{print "max (sec) alloc compute dealloc total " a " " c " " d " " t}' p9.log
max (sec) alloc compute dealloc total 0.00504 0.35655 0.00004 0.36159
```
