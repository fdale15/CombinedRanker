#pragma once
#include <vector>

class CombinedRanker
{
	std::vector<std::vector<int>> sources;
	std::vector<double> source_weights;
	std::vector<double> rank_sums;

	//This function sums all sources and populates the rank_sums vector.
	void sum_sources();
	//This function sorts all of the ranks in the sources based on the sums of the ranks.
	void sort_sources();
	//This function populates the source_weights vector from the derived reliability of each source.
	void derive_weights();
	//This function returns a vector with the reliabilty of each source based on a vector of inversions passed into it.
	std::vector<double> derive_reliability(std::vector<int> inversions);
	//This function counts the inversions within a source.
    int count_inversions(std::vector<int> source);
	//This function uses merge sort to count inversions.
	std::vector<int> msort_with_inversions(std::vector<int> source, int& inversions);
	//This function counts the number of inversions with each merge.
	std::vector<int> merge_with_inversions(std::vector<int> left, std::vector<int> right, int& inversions);
	//This functions returns a vector of inversions from the sources.
	std::vector<int> get_inversions();

	//Helper function that uses lambda expressions to keep track of indices that move.
	template <typename T>
	std::vector<size_t> sort_indexes(const std::vector<T> &v);

public:
	CombinedRanker(std::vector<std::vector<int>> _sources);
	~CombinedRanker();
};

