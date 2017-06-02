// #include <cstdio>
// #include <malloc.h>
// #include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <ctime>
#include <pthread.h>

// DEBUG
bool DEBUG = false;
bool PARALLEL = false;

// THREADS
unsigned THREADS = 1;

// Set random seed
unsigned SEED;
unsigned V_MAX;

// Sizes Definition
// A Matrix -> NxM
// B Matrix -> MxP
// C Matrix -> NxP
unsigned N;
unsigned M;
unsigned P;
unsigned TOTAL_OPERATIONS;

unsigned STEP;

std::vector<int> A;
std::vector<int> B;
std::vector<int> C;

void *product(void *start) {
	unsigned first;
	unsigned next;
	unsigned last;
	unsigned subOperations;
	unsigned row;
	unsigned col;
	unsigned a_pos;
	unsigned b_pos;
	int sum;

	first = *((unsigned *) start);
	next = first + STEP - 1;
	last = next;

	if ( (TOTAL_OPERATIONS > THREADS*STEP - 1)
		 && (THREADS*STEP - 1 == last) )
	{
		last = TOTAL_OPERATIONS - 1;
	}
	subOperations = M;

	for (int n = first; n <= last; n++)
	{
		row = n/P;
		col = n%P;

		sum = 0;

		for (unsigned i = 0; i < subOperations; i++)
		{
			a_pos = row*M + i;
			b_pos = P*i + col;
			sum += A.at(a_pos) * B.at(b_pos);
		}

		C.at(n) = sum;
	}

	// return;
}

int main(int argc, char *argv[])
{
	int error;
	pthread_t *threads_tab;
	unsigned *thread_args;
	clock_t timeElapsed;

	std::time_t initialTime, finishTime;

	// Set random seed
	SEED = 4;
	std::srand(SEED);
	V_MAX = 10;

	// Sizes Definition
	// A Matrix -> NxM
	// B Matrix -> MxP
	// C Matrix -> NxP

	// Set default parameters
	N = 10;
	M = 10;
	P = 10;


	// Configuring Parameters
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == std::string("-n"))
		{
			N = atoi(argv[i+1]);
		}

		else if (argv[i] == std::string("-m"))
		{
			M = atoi(argv[i+1]);
		}

		else if (argv[i] == std::string("-p"))
		{
			P = atoi(argv[i+1]);
		}

		else if (argv[i] == std::string("-t"))
		{
			PARALLEL = true;
			THREADS = atoi(argv[i+1]);
		}

		else if (argv[i] == std::string("--parallel") || argv[i] == std::string("--p"))
		{
			PARALLEL = true;
		}

		else if (argv[i] == std::string("--verbose") || argv[i] == std::string("--v"))
		{
			DEBUG = true;
		}
	}

	TOTAL_OPERATIONS = N*P;

	THREADS = (unsigned) fmin(THREADS, TOTAL_OPERATIONS);
	STEP = TOTAL_OPERATIONS/THREADS;

	std::cout << "PARAMETERS" << std::endl;
	std::cout << "A: " << N << " x " << M << std::endl;
	std::cout << "B: " << M << " x " << P << std::endl;
	std::cout << "C: " << N << " x " << P << std::endl;
	std::cout << "TOTAL_OPERATIONS: " << TOTAL_OPERATIONS << std::endl;
	std::cout << "STEP: " << STEP << std::endl;
	std::cout << "PARALLEL: " << (PARALLEL ? "True" : "False") << std::endl;
	std::cout << "THREADS: " << (PARALLEL ? THREADS : 1) << std::endl;
	std::cout << "DEBUG: " << (DEBUG ? "True" : "False") << std::endl;
	std::cout << std::endl;

	// Generate random vectors values (matrix representation)
	// Initialize vector A

	std::cout << "Initializing Vectors..." << std::endl;

	if (DEBUG) std::cout << "Vector: A" << "(" << N << "x" << M << ")";
	for (int i = 0; i < N*M; i++)
	{
		A.push_back(std::rand()%V_MAX);
		
		if (DEBUG)
		{
			if (i%M == 0)
			{
				std::cout << std::endl;
			}

			std::cout << A.at(i) << "\t";
		}
	}

	if (DEBUG)
	{
		std::cout << std::endl << std::endl;
	}

	// Initialize vector B
	if (DEBUG) std::cout << "Vector: B" << "(" << M << "x" << P << ")";
	
	for (int i = 0; i < M*P; i++)
	{
		B.push_back(std::rand()%V_MAX);

		if (DEBUG)
		{
			if (i%P == 0)
			{
				std::cout << std::endl;
			}

			std::cout << B.at(i) << "\t";
		}
	}
	if (DEBUG)
	{
		std::cout << std::endl << std::endl;
	}

	// Initialize vector C
	for (int i = 0; i < TOTAL_OPERATIONS; i++)
	{
		C.push_back(0);
	}

	std::cout << "Vectors Initialized" << std::endl;

	// Threads init

	// if (DEBUG) std::cout << "Run Program" << std::endl;
	std::cout << "Run Program" << std::endl;

	initialTime = std::time(NULL);

	// Parallel Version
	if (PARALLEL)
	{
		std::cout << "Creating Threads..." << std::endl;
		threads_tab = (pthread_t *)malloc( THREADS*sizeof(pthread_t));
		thread_args = (unsigned *)malloc(sizeof(unsigned)*THREADS);
		// if (DEBUG) std::cout << "Threads Initialized" << std::endl;
		std::cout << "Threads Initialized" << std::endl;
		for (unsigned i = 0; i < THREADS; i++)
		{
			thread_args[i] = i*STEP;
			error = pthread_create( &threads_tab[i], NULL, product, (void *)&thread_args[i]);
	 		if (error) exit(4);
		}

		for(unsigned i=0; i < THREADS; i++) pthread_join(threads_tab[i], NULL);
	}

	// Sequential Version
	else
	{
		unsigned start = 0;

		for (unsigned i = 0; i < THREADS; i++)
		{
			start = i*STEP;
			product(&start);
		}
	}

	finishTime = std::time(NULL);
	timeElapsed = finishTime - initialTime;

	// Result
	if (DEBUG)
	{
		std::cout << "Vector: C" << "(" << N << "x" << P << ")";
		for (int i = 0; i < N*P; i++)
		{		
			if (i%P == 0)
			{
				std::cout << std::endl;
			}

			std::cout << C.at(i) << "\t";
		}

		std::cout << std::endl << std::endl;
	}

	std::cout <<  "Timing: " << timeElapsed << "[s]" << std::endl;

	std::cout << "Finish Program" << std::endl;

	return 0;
}