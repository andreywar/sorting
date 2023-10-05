#include <iostream>
#include <array>
#include <fstream>
using namespace std;




int heap_comparation = 0;
int heap_reposition = 0;

int qsrt_comparation = 0;
int qsrt_reposition = 0;



void logging(int comparation, int reposition) 
{
	ofstream file;
	file.open("sort_methods.csv", ios::app);
	file << "comparation: " << comparation << " " << "reposition: " << reposition <<";";
	file.close();
}


void rand_array(int n, int arr[])
{
	srand(time(0));
    for (int i = 0; i < n; i++)
        *(arr + i) = 1 + rand() % 200;
}
void sorting_arr(int n, int arr[]) {
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > 1; j--)
			if (arr[j - 1] > arr[j])
				swap(arr[j - 1], arr[j]);
}
void reversing_arr(int n, int arr[]) {
	for (int i = 0, j = n - 1; i < j; ++i, --j)
	{
		swap(arr[i], arr[j]);
	}
}
void out_array(int n, int arr[]) {
	cout << "[";
	for (int i = 0; i < n; i++)
		cout << arr[i] << ", ";
	cout << "]" << endl;
}


void selection(int n, int arr[])
{
	int min = 0;
	int buf = 0;
	int comparation = 0;
	int reposition = 0;
	int *a = arr;
	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			comparation++;
			min = (a[j] < a[min]) ? j : min;
		}
		if (i != min)
		{
			swap(a[i], a[min]);
			reposition++;
		}
	}
	logging(comparation, reposition);
	out_array(n, a);
}


void Bubble_sort(int n, int arr[]) {
	int* a = arr;
	int comparation = 0;
	int reposition = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > 1; j--) {
			comparation++;
			if (a[j - 1] > a[j]) {
				reposition++;
				swap(a[j - 1], a[j]);
			}
		}
	logging(comparation, reposition);
	out_array(n, a);
}


void Insert_sort(int n, int arr[])
{
	int comparation = 0;
	int reposition = 0;
	int* a = arr;
	for (int i = 1; i < n; i++) 
	{
		for (int j = i; j > 0; j--)
		{
			comparation++;
			if (a[j - 1] > a[j]) 
			{
				reposition++;
				swap(a[j], a[j - 1]);
			}
		}
	}
	logging(comparation, reposition);
	out_array(n, a);
}


void binaryInsert(int n, int arr[]) {
	int i, j, l, r, m, x;
	int* a = arr;
	int comparation = 0;
	int reposition = 0;
	for (i = 1; i < n; i++) {
		x = a[i];
		l = 1;
		r = i - 1;
		while (l <= r)
		{
			m = (l + r) / 2;
			comparation++;
			(x < a[m]) ? r = m - 1 : l = m + 1;
		}
		for (j = i - 1; j >= l; j--)
			a[j + 1] = a[j];
		reposition++;
		a[l] = x;
	}
	logging(comparation, reposition);
	out_array(n, a);
}


void ShakerSort(int n, int arr[])
{
	int* a = arr;
	int l = 1;
	int r = n - 1;
	int comparation = 0;
	int reposition = 0;
	while (l <= r)
	{
		for (int i = r; i >= l; i--) {
			comparation++;
			if (a[i - 1] > a[i])
			{
				reposition++;
				swap(a[i], a[i - 1]);
			}
		}
		l++;


		for (int i = l; i <= r; i++) {
		comparation++;
		if (a[i - 1] > a[i]) {
			reposition++;
			swap(a[i], a[i - 1]);
		}
	}
		r--;
	}
	logging(comparation, reposition);
	out_array(n, a);
}


void ShellSort(int n, int arr[])
{
	int* a = arr;
	int step = 1;
	int comparation = 0;
	int reposition = 0;

	while (step < n / 3) {
		step = step * 3 + 1;
	}

	while (step > 0) {
		for (int i = step; i < n; i++) {
			int temp = a[i];
			int j = i;
			comparation++;
			while (j >= step && a[j - step] > temp) {
				a[j] = a[j - step];
				j -= step;
			}
			reposition++;
			a[j] = temp;
		}

		step = (step - 1) / 3;
	}
	logging(comparation, reposition);
	out_array(n, a);
}


void heap(int a[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	heap_comparation++;
	if (l < n && a[l] > a[largest])
		largest = l;
	heap_comparation++;
	if (r < n && a[r] > a[largest])
		largest = r;

	if (largest != i)
	{
		heap_reposition++;
		swap(a[i], a[largest]);

		heap(a, n, largest);
	}
}


void heapSort(int n, int arr[])
{
	int* a = arr;
	int comparation = 0;
	int reposition = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
		heap(a, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);
		heap(a, i, 0);
	}
	logging(heap_comparation, heap_reposition);
	out_array(n, a);
}


void qsrt(int n, int a[], int l, int r)
{
	int i, j, x;
	i = l;
	j = r;
	x = a[(l + r) / 2];
	while (i <= j) {
		while (a[i] < x) i++;
		while (x < a[j])j--;{
		qsrt_comparation++;
		if (i <= j) {
			qsrt_reposition++;
			swap(a[i], a[j]);
			i++;
			j--;
			}
		}
	}
	if (l < j) qsrt(n, a, l, j);
	if (i < r) qsrt(n, a, i, r);

}


void QuickSort(int n, int arr[]){
	int* a = arr;
	qsrt(n, a, 0, n - 1);
	logging(qsrt_comparation, qsrt_reposition);
	out_array(n, a);
}


int main()
{
    int n;
    cin >> n;
	ofstream file;
	file.open("sort_methods.csv");
	file << "methods/sorts;" << "selection;" << "bubble;" << "insert;" << "binary;" << "shaker;" << "shell;" << "heap;" << "quick;" << endl;
	file.close();


    int* random_arr = new int[n];
	rand_array(n, random_arr);
	out_array(n, random_arr);
	file.open("sort_methods.csv", ios::app);
	file << "random_array;";
	file.close();


	selection(n, random_arr);
	Bubble_sort(n, random_arr);
	Insert_sort(n, random_arr);
	binaryInsert(n, random_arr);
	ShakerSort(n, random_arr);
	ShellSort(n, random_arr);
	heapSort(n, random_arr);
	QuickSort(n, random_arr);



	int* sorted_arr = random_arr;
	sorting_arr(n, sorted_arr);
	out_array(n, sorted_arr);
	file.open("sort_methods.csv", ios::app);
	file << endl << "sorted array;";
	file.close();


	selection(n, sorted_arr);
	Bubble_sort(n, sorted_arr);
	Insert_sort(n, sorted_arr);
	binaryInsert(n, sorted_arr);
	ShakerSort(n, sorted_arr);
	ShellSort(n, sorted_arr);
	heapSort(n, sorted_arr);
	QuickSort(n, sorted_arr);



	int* reverse_arr = sorted_arr;
	reversing_arr(n, reverse_arr);
	out_array(n, reverse_arr);
	file.open("sort_methods.csv", ios::app);
	file << endl << "reverse array;";
	file.close();


	selection(n, reverse_arr);
	Bubble_sort(n, reverse_arr);
	Insert_sort(n, reverse_arr);
	binaryInsert(n, reverse_arr);
	ShakerSort(n, reverse_arr);
	ShellSort(n, reverse_arr);
	heapSort(n, reverse_arr);
	QuickSort(n, reverse_arr);

}