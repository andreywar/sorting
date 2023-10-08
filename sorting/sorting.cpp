#include <iostream>
#include <array>
#include <fstream>
#include<algorithm>

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


void rand_array(const int n, int arr[])
{
	srand(time(0));
    for (int i = 0; i < n; i++)
        *(arr + i) = 1 + rand() % 200;
}
void sorting_arr(const int n, int arr[]) {
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void reversing_arr(const int n, int arr[]) {
	for (int i = 0, j = n - 1; i < j; ++i, --j)
	{
		swap(arr[i], arr[j]);
	}
}
void out_array(const int n, int arr[]) {
	cout << "[";
	for (int i = 0; i < n; i++)
		cout << arr[i] << ", ";
	cout << "]" << endl;
}


void selection(const int n, int arr[])
{
	int min = 0;
	int comparation = 0;
	int reposition = 0;
	int a[200]; copy_n(arr, n, a);
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
	cout << "Selection" << endl;
	out_array(n, a);
}


void Bubble_sort(const int n, int arr[]) 
{
	int a[200]; copy_n(arr, n, a);
	int temp;
	int comparation = 0;
	int reposition = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++)
		{
			comparation++;
			if (a[j] > a[j + 1])
			{
				reposition++;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	logging(comparation, reposition);
	cout << "Bubble" << endl;
	out_array(n, a);
}


void Insert_sort(const int n, int arr[])
{
	int comparation = 0;
	int reposition = 0;
	int a[200]; copy_n(arr, n, a);
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
	cout << "insert" << endl;
	out_array(n, a);
}


void binaryInsert(const int n, int arr[]) {
	int left, right, key;
	int a[200]; copy_n(arr, n, a);
	int comparation = 0;
	int reposition = 0;
	for (int i = 1; i < n; i++)
	{
		key = a[i];
		left = 0, right = i - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			comparation++;
			if (a[mid] > key) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		for (int j = i - 1; j >= left; j--) {
			reposition++;
			a[j + 1] = a[j];
		}
		a[left] = key;
	}
	logging(comparation, reposition);
	cout << "binaryInsert" << endl;
	out_array(n, a);
}


void ShakerSort(const int n, int arr[])
{
	int a[200]; copy_n(arr, n, a);
	int left = 1;
	int right = n - 1;
	int comparation = 0;
	int reposition = 0;
	while (left <= right)
	{
		for (int i = right; i >= left; i--) {
			comparation++;
			if (a[i - 1] > a[i])
			{
				reposition++;
				swap(a[i], a[i - 1]);
			}
		}
		left++;


		for (int i = left; i <= right; i++) {
		comparation++;
		if (a[i - 1] > a[i]) 
		{
			reposition++;
			swap(a[i], a[i - 1]);
		}
	}
		right--;
	}
	logging(comparation, reposition);
	cout << "Shaker" << endl;
	out_array(n, a);
}

void ShellSort(const int n, int arr[])
{
	int a[200]; copy_n(arr, n, a);
	int step = 1;
	int comparation = 0;
	int reposition = 0;

	while (step < n / 3) {
		step = step * 3 + 1;
	}

	while (step > 0) 
	{
		for (int i = step; i < n; i++) {
			int temp = a[i];
			int j = i;		
			
			while (j >= step && a[j - step] > temp) {
				comparation+=2;
				reposition++;
				a[j] = a[j - step];
				j -= step;
			}
			a[j] = temp;
		}
		step = (step - 1) / 3;
	}
	logging(comparation, reposition);
	cout << "Shell" << endl;
	out_array(n, a);
}


void heap(int a[], int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	heap_comparation++;
	if (left < n && a[left] > a[largest])
		largest = left;
	heap_comparation++;
	if (right < n && a[right] > a[largest])
		largest = right;

	if (largest != i)
	{
		heap_reposition++;
		swap(a[i], a[largest]);

		heap(a, n, largest);
	}
}


void heapSort(const int n, int arr[])
{
	int a[200]; copy_n(arr, n, a);
	int comparation = 0;
	int reposition = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
		heap(a, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		heap_reposition++;
		swap(a[0], a[i]);
		heap(a, i, 0);
	}
	logging(heap_comparation, heap_reposition);
	heap_comparation = 0;
	heap_reposition = 0;
	cout << "Heap" << endl;
	out_array(n, a);
}


void qsrt(const int n, int a[], int left, int right)
{
	int i, j, x;
	i = left;
	j = right;
	x = a[(left + right) / 2];
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
	qsrt_comparation += 2;
	if (left < j) qsrt(n, a, left, j);
	if (i < right) qsrt(n, a, i, right);

}


void QuickSort(const int n, int arr[]){
	int a[200]; copy_n(arr, n, a);
	qsrt(n, a, 0, n - 1);
	logging(qsrt_comparation, qsrt_reposition);
	qsrt_comparation = 0;
	qsrt_reposition = 0;
	cout << "Quick" << endl;
	out_array(n, a);
}


int main()
{
	const int n = 200;
	ofstream file;
	file.open("sort_methods.csv");
	file << "methods/sorts;" << "selection;" << "bubble;" << "insert;" << "binary;" << "shaker;" << "shell;" << "heap;" << "quick;" << endl;
	file.close();


    int random_arr[200];
	rand_array(n, random_arr);
	cout << "\n\n\n\n\n";
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
	out_array(n, random_arr);


	int sorted_arr[200];
	copy_n(random_arr, 200, sorted_arr);
	sorting_arr(n, sorted_arr);
	cout << "\n\n\n\n\n";
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



	int reverse_arr[200];
	copy_n(sorted_arr, 200, reverse_arr);
	cout << "\n\n\n\n\n";
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