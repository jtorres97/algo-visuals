#pragma once

#include <SFML\Graphics.hpp>

#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>

#include "Bars.h"

class Sorter
{
public:
	explicit Sorter(sf::RenderWindow *outputTarget);

	// Sorting functions
	void BubbleSort(Bars &bars);
	void SelectionSort(Bars &bars);
	void QuickSort(Bars &bars, int startIndex, int endIndex);
	void InsertionSort(Bars &bars);

	// Utility functions
	auto Swap(Bars &bars, int previous, int next, bool usingStdSwap);
	void UpdateElements(Bars &bars, int previous, int next);
	int Partition(Bars &bars, int startIndex, int endIndex);
	void Sleep();
private:
	sf::RenderWindow *m_target;
};

