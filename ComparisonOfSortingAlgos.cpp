#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

void InsertionSort(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			swap(arr[j], arr[j - 1]);
	}
}

void Combine(int *arr, int start, int mid, int end)
{
	int size1 = mid - start + 1;
	int size2 = end - mid;
	int *left = new int[size1 + 1];
	int *right = new int[size2 + 1];
	for (int i = 0; i < size1; i++)
		left[i] = arr[start + i];
	left[size1] = INT_MAX;
	for (int j = 0; j < size2; j++)
		right[j] = arr[mid + j + 1];
	right[size2] = INT_MAX;
	for (int i = 0, j = 0, k = start; k <= end;)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	delete[]left;
	delete[]right;
}

void MergeSort(int *arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);
		Combine(arr, start, mid, end);
	}
}

int Partition(int arr[], int start, int end)
{
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (arr[j] <= arr[end])
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[end]);
	return i + 1;
}

void QuickSort(int arr[], int start, int end)
{
	if (start < end)
	{
		int p = Partition(arr, start, end);
		QuickSort(arr, start, p - 1);
		QuickSort(arr, p + 1, end);
	}
}

int medianPartition(int arr[], int start, int end)
{
	int seed, pivot;
	int pivotArr[3];
	mt19937 rng;
	rng.seed(time(NULL));
	uniform_int_distribution<int> randomGenerator(start, end);
	pivotArr[0] = randomGenerator(rng);
	pivotArr[1] = randomGenerator(rng);
	pivotArr[2] = randomGenerator(rng);
	
	if ((pivotArr[0] >= pivotArr[1] && pivotArr[0] <= pivotArr[2]) || (pivotArr[0] >= pivotArr[2] && pivotArr[0] <= pivotArr[1]))
		pivot = pivotArr[0];
	else if ((pivotArr[1] >= pivotArr[0] && pivotArr[1] <= pivotArr[2]) || (pivotArr[1] >= pivotArr[2] && pivotArr[1] <= pivotArr[0])) 
		pivot = pivotArr[1];
	else 
		pivot = pivotArr[2];
	swap(arr[pivot], arr[end]);
	return Partition(arr, start, end);
}

void QuickSort2(int arr[], int start, int end)
{
	if (start < end)
	{
		int p = medianPartition(arr, start, end);
		QuickSort2(arr, start, p - 1);
		QuickSort2(arr, p + 1, end);
	}
}

void maxHeapify(int *arr, int i, int n)
{
	int j, temp= arr[i];
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && arr[j + 1] > arr[j])
			j = j + 1;
		if (temp > arr[j])
			break;
		else if (temp <= arr[j])
		{
			arr[j / 2] = arr[j];
			j = 2 * j;
		}
	}
	arr[j / 2] = temp;
}

void MaxHeap(int *arr, int n)
{
	int i;
	for (i = n / 2; i > 0; i--)
		maxHeapify(arr, i, n);
}

void HeapSort(int *arr, int n)
{
	int i, temp;
	for (i = n; i > 1 ; i--)
	{
		swap(arr[i], arr[1]);
		maxHeapify(arr, 1, i - 1);
	}
}


int main()
{
	double start_s, stop_s, avgRT[5], total = 0;
	system("Color 8F");
	cout << '\t' << '\t' << '\t' << '\t' << "COMPARISON OF SORTING ALGORITHMS  \n";
	cout << " <1> for Insertion Sort  \n <2> for Merge Sort \n <3> for Quick Sort \n <4> for Quick Sort2 \n <5> for Heap Sort \n \n";
	/*for integer data when plots are from 1 */
	cout << "Sorting choice number? ";
	int choice;
	cin >> choice;
	cout << "Data size of array ?(-1 to quit): ";
	int size;
	cin >> size;
	while (size != -1)
	{
		int *input_arr = new int[size];
		int *processing_arr = new int[size];
		int seed;		
		mt19937 rng;
		rng.seed(time(NULL));
		uniform_int_distribution<int> randomGenerator(1, 1000);
		for (int i = 0; i < size; i++)
			input_arr[i] = randomGenerator(rng);
		if (choice == 1)
		{
			cout << "Insertion sort when data size = " << size << '\n';
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				InsertionSort(processing_arr, size);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				cout << "Iteration" << i + 1 << ": " << avgRT[i] << '\n';
				total = total + avgRT[i];
			}
			double avg = total / 5;
			cout << "Average: " << avg << '\n' << '\n';
		}
		else if (choice == 2)
		{
			cout << "Merge sort when data size = " << size << '\n';
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				MergeSort(processing_arr, 0, size - 1);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				total = total + avgRT[i];
				cout << "Iteration" << i + 1 << ": " << avgRT[i]<< "in ms" << '\n';
			}
			double avg = total / 5;
			cout << "Average: " << avg << '\n' << '\n';
		}
		else if (choice == 3)
		{
			cout << "Quick sort when data size =" << size << '\n';
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				QuickSort(processing_arr, 0, size - 1);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				total = total + avgRT[i];
				cout << "Runtime " << i + 1 << ": " << avgRT[i] << "in ms" << '\n';
			}
			double avg = total / 5;
			cout << "Iteration: " << avg << '\n' << '\n';
		}
		else if (choice == 4)
		{
			cout << "Quick sort 2 when data size =" << size << '\n';
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				QuickSort2(processing_arr, 0, size - 1);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				cout << "Iteration" << i + 1 << ": " << avgRT[i] << '\n';
				total = total + avgRT[i];
			}
			double avg = total / 5;
			cout << "Average: " << avg << '\n' << '\n';
		}
		
		else if (choice == 5)
		{
			cout << "Heap sort when data size = " << size << '\n';
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				MaxHeap(processing_arr, size);
				HeapSort(processing_arr, size);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				cout << "Iteration" << i + 1 << ": " << avgRT[i] << '\n';
				total = total + avgRT[i];
			}
			double avg = total / 5;
			cout << "Average: " << avg << '\n' << '\n';
		}
		cout << "Data size of array(-1 to quit): ";
		cin >> size;
		if (size == -1)
		{
			delete[] processing_arr;
			delete[] input_arr;
		}
	}


	/*for integer data when plots are from 2-4 */
	/*
	int *a = new int[1000000];
	int *myArray = new int[100000];;
	int count = 0, count2 = 0, amount = 0;;
	long k = 0;
	ifstream infile("sorted.txt");
	if (infile.is_open())
	{
	while (k<1000000)
	//infile >> a[k++];
	}
	else
	cout << "can not open" << endl;
	for (int i = 0; i < 5; i++)
	{
	start_s = clock();
	InsertionSort(a, k);
	//MergeSort(a, 0, k);
	//QuickSort(a, 0, k);
	//QuickSort2(a, 0, k);
	//MaxHeap(a, k);
	//HeapSort(a, k);
	stop_s = clock();
	avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
	cout << "Iteration" << i + 1 << ": " << avgRT[i] << '\n';
	total = total + avgRT[i];
	}
	double avg = total / 5;
	cout << "Average: " << avg << '\n' << '\n';
	*/
	system("pause");
	return 0;
}
