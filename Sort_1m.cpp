#include "pch.h"
#include <iostream>
#include <fstream>
#include <time.h>
#define mil 1000000
using namespace std;
void reHeapDown(int arr[], int size, int pos)
{
	int largeChild = pos;
	int leftChild = 2 * pos + 1;
	int rightChild = 2 * pos + 2;
	if (leftChild <  size && arr[leftChild] > arr[largeChild])
		largeChild = leftChild;
	if (rightChild <  size && arr[rightChild] > arr[largeChild])
		largeChild = rightChild;
	if (largeChild != pos)
	{
		swap(arr[pos], arr[largeChild]);
		reHeapDown(arr, size, largeChild);
	}
}
void HeapSort(int *arr, int size,int k,int* res)
{
	int dem = 0;
	for (int i = size / 2 - 1; i >= 0; i--)
		reHeapDown(arr, size, i);
	for (int i = size - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		//Tim k phan tu lon nhat
		if (dem < k) {	
			res[dem] = arr[i];
			dem++;
		}
		reHeapDown(arr, i, 0);
	}

}

int main()
{
	clock_t begin = clock();
	//Read File
	int *arr=new int[mil];
	int *sort = new int[100];
	int *k;
	int size;
	cout << "Tim k phan tu lon nhat: " << endl;
	cin >> size;
	k = new int[size];
	for (int i = 0; i < 100; i++)
	{
		sort[i] = 0;
	}
	ifstream ifs;
	ofstream file;
	ifs.open("random_1m_integer.txt");
	int val;
	int i = 0;
	while (ifs>>val)
	{
		arr[i] = val;
		i++;
		sort[val]++; //Counting Sort
		if (i == mil) break;
	}
	ifs.close();
	//End read file

	clock_t endReadFile = clock();
	HeapSort(arr, mil,size,k);

	//In k phan tu
	for (int i = 0; i < size; i++)
	{
		cout << k[i] << endl;
	}
	clock_t endSort = clock();

	//Write File heap sort
	file.open("output.txt");
	for (int i = 0; i < mil; i++)
	{
		file << arr[i] << "\n";
	}
	file.close();
	//End

	//Write File counting sort
	file.open("output.txt");
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < sort[i]; j++)
			file << i << "\n";
	}
	file.close();
	//End write file

	delete[] arr;
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	double time1 = (double)(endReadFile - begin) / CLOCKS_PER_SEC;
	double time2 = (double)(endSort - endReadFile) / CLOCKS_PER_SEC;
	double time3 = (double)(end - endSort) / CLOCKS_PER_SEC;
	cout << "Program running time: " << time<<" s" << endl;
	cout << "Read file time: " << time1 << " s" << endl;
	cout << "Sort time: " << time2 << " s" << endl;
	cout << "Write file time: " << time3 << " s" << endl;
	return 0;
}