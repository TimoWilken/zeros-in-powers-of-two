# Finding zeros in digits of powers of two

I wrote the Haskell version first, then the C version for speed.

Both programs take an optional command-line argument, the power of two to start
from (e.g. `zeros 10` starts from 1024).

## Try it in C

```{sh}
$ gcc -O2 zeros.c -lgmp -o zeros
$ ./zeros
```

## Try it in Haskell

```{sh}
$ ghc -O2 -dynamic -o zeros.haskell zeros.hs
$ ./zeros.haskell
```
