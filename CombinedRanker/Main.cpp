#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CombinedRanker.h"
#include <algorithm>

using namespace std;

// reads data from 5 sources
vector<vector<int>> read_data() {
	auto sources = vector<vector<int>>();

	for (int i = 0; i < 5; i++) {
		auto source = vector<int>();
		// remove "debug sources/" from filename later
		string filename = "source" + to_string(i + 1) + ".txt";
		ifstream fin(filename);

		if (fin.is_open()) {
			int temp;

			do {
				fin >> temp;

				source.push_back(temp);
			} while (!fin.eof());
		}

		fin.close();

		sources.push_back(source);
	}

	return sources;
}

void main() {
	
	//vector<int> arr {1, 2, 4, 3, 6, 5}; //2
	//vector<int> brr { 2, 4, 1, 3, 5, 6 }; //3
	//vector<int> crr { 4, 2, 5, 3, 1 };//7

	//auto sources = vector<vector<int>>();
	//
	//sources.push_back(arr);
	//sources.push_back(brr);
	//sources.push_back(crr);



	auto sources = read_data();
	auto cb = CombinedRanker(sources);

	int i;
	cin >> i;
}