#include <iostream>
#include <vector>
#include "CombinedRanker.h"

using namespace std;


void main() {
	static const int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	auto numbers = vector<int>(arr, arr + sizeof(arr) / sizeof(arr[0]));

	auto sources = vector<vector<int>>();
	sources.push_back(numbers);

	auto cb = CombinedRanker(sources);

	int i;
	cin >> i;
}