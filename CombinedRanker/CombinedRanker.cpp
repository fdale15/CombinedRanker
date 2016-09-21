#pragma once
#include "CombinedRanker.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

//Remove this later.
template <typename T>
void print(vector<T> s)
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
	fill(source_weights.begin(), source_weights.end(), 1.0);
	rank_sums = vector<double>(sources.front().size());

	sum_sources();
	sort_sources();
	derive_weights();
	sum_sources();

	//Remove this later.
	/*for (auto source : sources)
	{
		print(source);
	}*/

	print(rank_sums);
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
	sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

//This function populates the source_weights vector after the sources have been adjusted.
void CombinedRanker::derive_weights()
{
	auto inversions = get_inversions();
	auto reliability = derive_reliability(inversions);

	int count = sources.size();
	double sum = 0;
	for (double i : reliability)
		sum += i;

	int i = 0;
	for (auto& weight : source_weights)
	{
		weight = reliability[i] / sum * count;
		i++;
	}
}

//This function returns a vector with the reliabilty of each source based on a vector of inversions passed into it.
std::vector<double> CombinedRanker::derive_reliability(const std::vector<int> inversions)
{
	auto reliability = vector<double>(sources.size());
	int i = 0;
	for (auto& rel : reliability)
	{
		rel = 1 / ((double)inversions[i] + 1);
		i++;
	}
	return reliability;
}

//This function counts the inversions within a source.
int CombinedRanker::count_inversions(vector<int> source)
{
	int i = 0;
	msort_with_inversions(source, i);
	return i;
}

//This function cycles through the sources and returns a vector with each sources inversion count.
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

//This function uses merge sort to count inversions.
std::vector<int> CombinedRanker::msort_with_inversions(vector<int> source, int& inversions)
{
	if (source.size() == 1)
		return source;

	int half = source.size() / 2;
	auto left = vector<int>(source.begin(), source.begin() + half);
	auto right = vector<int>(source.begin() + half, source.end());

	left = msort_with_inversions(left, inversions);
	right = msort_with_inversions(right, inversions);

	return merge_with_inversions(left, right, inversions);
}

//This function counts the number of inversions with each merge.
std::vector<int> CombinedRanker::merge_with_inversions(vector<int> left, vector<int> right, int& inversions)
{
	auto result = vector<int>();

	while (left.size() || right.size())
	{
		if (right.size() && left.size())
		{
			if (left.front() > right.front())
			{
				inversions++;
				result.push_back(right.front());
				right.erase(right.begin());
			}
			else
			{
				result.push_back(left.front());
				left.erase(left.begin());
			}
		}
		else if (right.size())
		{
			result.push_back(right.front());
			right.erase(right.begin());
		}
		else
		{
			result.push_back(left.front());
			left.erase(left.begin());
		}
	}

	return result;
}

//This function uses quick sort to count inversions.
std::vector<int> CombinedRanker::qsort_with_inversions(vector<int> source)
{
	if (source.size() <= 1)
		return source;

	std::vector<int> equal, less, greater;

	// select a pivot, based on median of three
	int pivot;

	if (source[0] < source[source.size() - 1])
	{
		if (source[0] < source[(source.size() - 1) / 2])
			pivot = source[(source.size() - 1) / 2];
		else
			pivot = source[0];
	}
	else
	{
		if (source[source.size() - 1] < source[(source.size() - 1) / 2])
			pivot = source[(source.size() - 1) / 2];
		else
			pivot = source[source.size() - 1];
	}

	// compare to the pivot and sort appropriately
	for (int i = 0; i < source.size(); i++)
	{
		if (source[i] < pivot)
			less.push_back(source[i]);
		else if (source[i] > pivot)
			greater.push_back(source[i]);
		else
			equal.push_back(source[i]);
	}

	// return w/ concatenation & recursion
	std::vector<int> greater_sorted = qsort_with_inversions(greater);
	std::vector<int> less_sorted = qsort_with_inversions(less);

	equal.insert(equal.end(), greater_sorted.begin(), greater_sorted.end());
	less_sorted.insert(less_sorted.end(), equal.begin(), equal.end());

	return less_sorted;
}

CombinedRanker::~CombinedRanker()
{
}
