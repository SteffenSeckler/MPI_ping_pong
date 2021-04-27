#include <chrono>
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (size != 2) {
		std::cout << "Bad size, has to be run with 2 processes!" << std::endl;
		MPI_Finalize();
		return 1;
	}
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int error_flag = 0;
	std::cout << "Starting ping pong" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	if (rank == 0) {
		int i = 0;

		MPI_Send(&i, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&i, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (i != 1) {
			error_flag = 1;
		}
	} else {
		int i = 1;
		MPI_Send(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Recv(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (i != 0) {
			error_flag = 1;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	MPI_Finalize();
	std::cout << "rank=" << rank << ": flag=" << error_flag << ", duration=" << duration << " ns" << std::endl;
	return error_flag;
}
