#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <algorithm>
#include <random>

#include "Bars.h"
#include "Utils.h"
#include "AssetManager.h"

class Sorts
{
public:
	Sorts(sf::RenderWindow &outputTarget);

	void BubbleSort(Bars &bars);
	void SelectionSort(Bars &bars);
	void QuickSort(Bars &bars, int startIndex, int endIndex);
	void InsertionSort(Bars &bars);

private:
	auto Swap(Bars &bars, int previous, int next, bool usingStdSwap);
	int Partition(Bars &bars, int startIndex, int endIndex);
private:
	Utils m_utils;
	sf::RenderWindow &m_target;
};

