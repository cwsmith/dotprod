# dotprod
loop testing

## turtle

Ryzen 5 3600
GCC 10.1.0

```
$ g++ -O3 dotprod.cpp -o dotprod
$ for i in {0..10}; do ./dotprod ; done &> turtle.log
$ cat turtle.log;
alloc(s) compute(s) total(s) 0.29898 0.20001 0.49900
alloc(s) compute(s) total(s) 0.29479 0.19874 0.49353
alloc(s) compute(s) total(s) 0.29954 0.20218 0.50172
alloc(s) compute(s) total(s) 0.29265 0.20039 0.49305
alloc(s) compute(s) total(s) 0.29418 0.20131 0.49549
alloc(s) compute(s) total(s) 0.29465 0.20190 0.49654
alloc(s) compute(s) total(s) 0.29392 0.20023 0.49414
alloc(s) compute(s) total(s) 0.29535 0.20173 0.49708
alloc(s) compute(s) total(s) 0.29939 0.20132 0.50071
alloc(s) compute(s) total(s) 0.28834 0.19980 0.48814
alloc(s) compute(s) total(s) 0.28349 0.19988 0.48336
$ awk 'BEGIN {a=0;c=0}{a=($4>a ? $4 : a); c=($5>c ? $5 : c)} END{print "max alloc (sec): " a "  max compute (sec): " c}' turtle.log
max alloc (sec): 0.29954  max compute (sec): 0.20218
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
