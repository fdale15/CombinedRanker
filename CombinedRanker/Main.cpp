#include <iostream>
#include <vector>
#include "CombinedRanker.h"

using namespace std;


void main() {
	vector<int> arr {1, 2, 4, 3, 6, 5};
	vector<int> brr { 2, 4, 1, 3, 5, 6 };
	vector<int> crr { 1, 2, 3, 4, 5, 6 };

	auto sources = vector<vector<int>>();

	sources.push_back(arr);
	sources.push_back(brr);
	sources.push_back(crr);

	auto cb = CombinedRanker(sources);

	int i;
	cin >> i;
}