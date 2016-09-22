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
}\

//prints data from a vector
template<typename T>
void print(vector<T> source)
{
	for (auto s : source)
	{
		cout << s << endl;
	}
}

void main() {
	
	auto sources = read_data();
	auto cb = CombinedRanker(sources);

	print(cb.getCombinedRank());

	int i;
	cin >> i;
}