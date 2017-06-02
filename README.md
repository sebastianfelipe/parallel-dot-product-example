# parallel-dot-product-example

This program generates 2 matrices:

* A: N rows x M colums
* B: M rows x P colums

The result is a matrix called C and has N rows by P columns

Basically, the programs generate randomly the matrices A and B
in a linear way (that is, not as a matrix itself, but as a long vector, i.e
matrix A  is represented as a vector of NxM spaces only)

Once you compiled the program (using make), it will generate it, using the name "pdp"

The program has some default parameters, they are:

* DEBUG: false
* PARALLEL: false
* N: 10
* M: 10
* P: 10
* THREADS: 1

Each of those parameters can be modified by using the following sintaxis:

pdp -n <N> -m <M> -p <P> -t <THREADS>

Other commands:
* --parallel or --p: Use it to run the program with the parallel version. In case you use the command "pdp -t 1", automatically it will assume that the program will be parallel, by using only 1 thread (there is no significance difference runing in paralell using 1 thread explicitly or just running it sequentially).

* --verbose or --v: That is to activate the DEBUG version, that implies matrix printing.

I hope you enjoy it and have good results :)

Sebastián.
