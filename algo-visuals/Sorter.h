#pragma once

#include <SFML\Graphics.hpp>

#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>

class Sorter
{
public:
	explicit Sorter(sf::RenderWindow *outputTarget);

	// Sorting functions
	void BubbleSort(std::vector<int> &arr);
	void SelectionSort(std::vector<int> &arr);
	void QuickSort(std::vector<int> &arr, int startIndex, int endIndex);
	void InsertionSort(std::vector<int> &arr);

	// Utility functions
	auto Swap(std::vector<int> &arr, int previous, int next, bool usingStdSwap);
	void UpdateElements(std::vector<int> &vec, int previous, int next);
	int Partition(std::vector<int> &arr, int startIndex, int endIndex);
	void Shuffle(std::vector<int> &arr);
	void Sleep();
private:
	sf::RenderWindow *m_target;
};

