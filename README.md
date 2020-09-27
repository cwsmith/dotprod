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
$ g++ -O3 dotprod.cpp -o dotprod
$ for i in {0..10}; do ./dotprod ; done &> p9.log
$ cat p9.log
alloc(s) compute(s) total(s) 0.18676 0.36163 0.54839
alloc(s) compute(s) total(s) 0.18408 0.35599 0.54008
alloc(s) compute(s) total(s) 0.18607 0.35712 0.54319
alloc(s) compute(s) total(s) 0.18309 0.35546 0.53855
alloc(s) compute(s) total(s) 0.18058 0.35723 0.53781
alloc(s) compute(s) total(s) 0.18930 0.35939 0.54869
alloc(s) compute(s) total(s) 0.18581 0.35596 0.54177
alloc(s) compute(s) total(s) 0.18070 0.35554 0.53624
alloc(s) compute(s) total(s) 0.18052 0.35398 0.53449
alloc(s) compute(s) total(s) 0.18060 0.35822 0.53882
alloc(s) compute(s) total(s) 0.18157 0.36013 0.54170
$ awk 'BEGIN {a=0;c=0}{a=($4>a ? $4 : a); c=($5>c ? $5 : c)} END{print "max alloc (sec): " a "  max compute (sec): " c}' p9.log
max alloc (sec): 0.18930  max compute (sec): 0.36163
```

