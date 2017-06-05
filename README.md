# Parallel Dot Product Example

This program generates 2 matrices:

* A: N rows x M colums
* B: M rows x P colums

The result is a matrix called C and has N rows by P columns

Basically, the program generates randomly the matrices A and B
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

Some extra and fixed parameters are:
* RANDOM VALUES: between 0 and 10
* RANDOM SEED: 4

In terms of operations, a single operation is the calculation of one cell in the matrix C. A sequential version will calculate each cell, one by one. Instead, the parallel version will divide that cost among the all threads. That is the general idea (well, there is some logic behind the scenes, but in abstract, that is the main idea).


Each of those parameters can be modified by using the following sintaxis:

./pdp -n N -m M -p P -t THREADS

Other commands:
* --parallel or --p: Use it to run the program with the parallel version. In case you use the command "pdp -t 1", automatically it will assume that the program will be parallel, by using only 1 thread (there is no significance difference runing in paralell using 1 thread explicitly or just running it sequentially).

* --verbose or --v: That is to activate the DEBUG version, that implies matrix printing.

An example:

./pdp -n 1000 -m 300 -p 200 -t 3

This command line will generate the matrix A with 1000 rows and 300 colums, the matrix B with 300 rows and 200 colums, that implies a outcome matrix C with 1000 rows and 200 columns. Also, it uses 3 threads to calculate the result.

I hope you enjoy it and have good results :)

Sebastián.
