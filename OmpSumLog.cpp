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
void print(int* a, int num) {
	for (int i = 0; i < num; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}
int sumArray(int *a, int num) {
    int numberThread  = num / 2;
    int *b = new int[num / 2];
    while(numberThread != 1) {
        omp_set_num_threads(numberThread);
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            b[id] = a[2 * id] + a[2 * id + 1];
        }
        for (int i = 0; i < numberThread; i++) {
            a[i] = b[i];
        }
        if (numberThread %2 == 1) b[numberThread - 1] = a[numberThread - 1];
        //print(b, numberThread);
        numberThread = (numberThread % 2 == 0 || numberThread == 1 ? numberThread /= 2 : numberThread / 2 + 1);
    }
    return b[0];

}
int main() {
    int num;
    cout << "Nhap vao so phan tu cua mang: ";
	cin >> num;
	cout << "Nhap vao mang A: ";
	int* a = createArray(num);
    cout << sumArray(a, num);
}
