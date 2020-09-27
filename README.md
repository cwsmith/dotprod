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
