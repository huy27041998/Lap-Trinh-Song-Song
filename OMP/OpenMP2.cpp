#include <stdio.h>
#include <omp.h>

int main() {
	int id, x;
	omp_set_num_threads(10);
	#pragma omp parallel
	{
		id = omp_get_thread_num();
		x = 10 * id;
		printf("\n");
		printf("Hello from thread %d, x = %d", id, x);
		printf("\n");
	}
	//Loi cac luong song song tranh chap tai nguyen int id, int x
	return 0;
}
