#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

const int size = 10;
void swap(int a, int b);
int bubbleSort(int arr[size]);
void readFile(int arr[size], int i);

int main()
{
	//declaring variables to store inversions for each sources
	int s1 = 0; 
	int s2 = 0; 
	int s3 = 0; 
	int s4 = 0; 
	int s5 = 0; 
	double time_elapsed = 0;
	
	int source_one[size] = {0};
	int source_two[size] = {0};
	int source_three[size] = {0};
	int source_four[size] = {0};
	int source_five[size] = {0};
	
	readFile(source_one, 1);
	readFile(source_two, 2);
	readFile(source_three,3); 
	readFile(source_four,4); 
	readFile(source_five,5); 
	
	//sorting all arrays
	clock_t start = clock();
	s1 = bubbleSort(source_one);
	s2 = bubbleSort(source_two);
	s3 = bubbleSort(source_three);
	s4 = bubbleSort(source_four);
	s5 = bubbleSort(source_five);
	clock_t end = clock();
	time_elapsed = (end - start);


	cout<<"BUBBLE SORT RESULTS: "<<endl;
	cout << "inversions in source 1: "<<s1<<endl;
	cout << "inversions in source 2: "<<s2<<endl;
	cout << "inversions in source 3: "<<s3<<endl;
	cout << "inversions in source 4: "<<s4<<endl;
	cout << "inversions in source 5: "<<s5<<endl;
	cout << "time elapsed: "<<time_elapsed<< " seconds"<<endl;
	
	return 0;
	
}

//bubble sort algorithm that counts inversions 
int bubbleSort(int arr[size])
{
	int inversion = 0;
	int x = 0;	
	int n = -1;
	while(n != 0)
	{
		x = 0;
		for(int i = 0; i < size-1; i++)
		{
			if(arr[i] > arr[i+1])
			{
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				inversion++;   //counter when every swap happens, hence counting inversions 
				x = i;
			}
		}
		n = x;
	}
	return inversion;
}

//swap two elements
void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

//read the file
void readFile(int arr[size], int x)
{
	ifstream file;
	if (x == 1) {file.open("../../data/source1_count.txt");}
	else if (x == 2) {file.open("../../data/source2_count.txt");}
	else if (x == 3) {file.open("../../data/source3_count.txt");}
	else if (x == 4) {file.open("../../data/source4_count.txt");}
	else {file.open("../../data/source5_count.txt");}
	
	for(int i=0; i < size; i++)
	{
		file >> arr[i];
	}
}
