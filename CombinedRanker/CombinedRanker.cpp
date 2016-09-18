#pragma once
#include "CombinedRanker.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

//Remove this later.
void print(vector<int> s)
{
	for(auto i : s)
	{
		cout << i << endl;
	}
	cout << "\n\n\n";
}

CombinedRanker::CombinedRanker(std::vector<std::vector<int>> _sources)
{
	sources = _sources;
	source_weights = vector<double>(sources.size());
	fill(source_weights.begin(), source_weights.end(), 1);
	rank_sums = vector<int>(sources.front().size());

	sum_sources();
	sort_sources();
	derive_weights();
	sum_sources();

	//Remove this later.
	for (auto source : sources)
	{
		print(source);
	}
}

//This function sums all sources and populates the rank_sums vector.
void CombinedRanker::sum_sources()
{
	fill(rank_sums.begin(), rank_sums.end(), 0);

	int s = 0;
	for(auto source: sources)
	{
		int i = 0;
		for (auto rank: source)
		{
			rank_sums[i] += rank * source_weights[s];
			i++;
		}
		s++;
	}
}

//This function sorts all of the ranks in the sources based on the sums of the ranks.
void CombinedRanker::sort_sources()
{
	auto idx_changes = sort_indexes(rank_sums);

	for (auto& source : sources)
	{
		auto sorted_source = vector<int>(source.size());

		int i = 0;
		for (auto idx : idx_changes)
		{
			sorted_source[i] = source[idx];
			i++;
		}
		source = sorted_source;
	}
}

//Helper function that uses lambda expressions to keep track of indices that move.
template <typename T>
std::vector<size_t> CombinedRanker::sort_indexes(const std::vector<T>& v)
{
	// initialize original index locations
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

//This function populates the source_weights vector after the sources have been adjusted.
void CombinedRanker::derive_weights()
{
	auto inversions = get_inversions();
	auto reliability = derive_reliability(inversions);

	int count = sources.size();
	int sum = 0;
	for (auto i : reliability)
		sum += i;

	int i = 0;
	for (auto& weight : source_weights)
	{
		weight = reliability[i] / sum * count;
	}
}

std::vector<double> CombinedRanker::derive_reliability(std::vector<int> inversions)
{
	auto reliability = vector<double>(sources.size());
	int i = 0;
	for (auto& rel : reliability)
	{
		rel = 1 / (inversions[i] + 1);
		i++;
	}
	return reliability;
}

//This function counts the inversions within a source.
int CombinedRanker::count_inversions(vector<int> source)
{
	return 0;
}

std::vector<int> CombinedRanker::get_inversions()
{
	auto source_inversions = vector<int>(sources.size());
	int i = 0;
	for (auto source : sources)
	{
		source_inversions[i] = count_inversions(source);
		i++;
	}
	return source_inversions;
}


CombinedRanker::~CombinedRanker()
{
}
