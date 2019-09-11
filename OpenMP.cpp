#include <omp.h>
#include <stdio.h>
int main(){
	#pragma omp parallel //Khoi tao moi truong da luong
	{	
		//Block nay duoc chay da luong
		//Trong block nay tat ca cac thread thuc hien tat ca cac lenh
	}	
	//omp_get_thread_num(): tra ve id luong
	//omp_get_num_threads(): tra ve so luong vat ly
	printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
	return 0;
}
