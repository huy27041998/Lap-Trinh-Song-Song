#include <iostream>
#include <omp.h>
using namespace std;
int * createArray(int num) {
	int *a = new int[num];
	for (int i = 0; i < num; i++){
		cin >> a[i];
	}
	return a;
}
int* sumArray(int *a, int*b, int num, int numthread){
	int *c = new int[num];
	omp_set_num_threads(numthread);
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int end = (id + 1) * num / numthread;
		int start = id * num / numthread;
		// printf("%d %d ", start, end);
		for (int i = start; i < end; i++){
			if (i < num) {
				// printf("%d\n", i);
				c[i] = a[i] + a[i];
			}
		}
	//Moi thread cong tren 1 doan cua array
	}
	cout << endl;
	return c;
}
void print(int* a, int num) {
	for (int i = 0; i < num; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}
int main() {
	int num, numthread;
	cout << "Nhap vao so phan tu cua mang va so luong: ";
	cin >> num >> numthread;
	cout << "Nhap vao mang A: ";
	int* a = createArray(num);
	cout << "Nhap vao mang B: ";
	int* b = createArray(num);
	cout << "Tong cua A va B: ";
	int* c = sumArray(a, b, num, numthread);
	print(c, num);
	delete a;
	delete b;
	delete c;
}
