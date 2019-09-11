#include <stdio.h>
#include <omp.h>

int main() {
	omp_set_num_threads(10);//Tao so luong co dinh
	#pragma omp parallel
	{
		printf("Hello from thread %d, nthread %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
	return 0;
}
