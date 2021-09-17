#include <iostream>
#include <stdio.h> 
#include <mpi.h> 
#include <math.h> 
#include <time.h>
using namespace std;

int main(int argc, char** argv) {
	int myid, P, source, C = 0;
	int numprocs = 0;
	double d = 0;
	int N;
	double inte = 0.0;
	double  SqrtSum = 0.0;
	MPI_Status status;
	clock_t t;
	t = clock();
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	N = atoi(argv[1]);
	double* data = new double[N];
	for (int i = 0; i < N; i++)
	{
		data[i] = double(i * (double((i + 1.0))));
	}
	if (myid != 0)
	{
		for (int i = myid - 1; i < N; i = i + numprocs - 1)
		{
			SqrtSum += sqrt(data[i]);
		}
		cout << "This is process" << " " << myid << ". I will send " << SqrtSum << " back" << endl;
		
	}
	MPI_Reduce(&SqrtSum, &inte, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myid == 0)
	{
		cout << "This is the process 0 , the outcome is " << inte << endl;
		t = clock() - t;
		cout << "Use " << t << "  haomiao" << endl;
		delete[] data;
	}
	MPI_Finalize();
}