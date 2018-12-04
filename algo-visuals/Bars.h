#pragma once

#include <SFML\Graphics.hpp>

#include <vector>
#include <algorithm>
#include <random>

class Bars 
{
public:
	Bars(sf::Uint32 width, sf::Uint32 height, const int numElements);
	std::vector<int> GetVec();
	void SetSortStatus(bool sorted);
	bool IsSorted();
	void Shuffle();
	int Size();
	int At(int index);
	void Move(int index, int newDest);
	void Set(int index, int newVal);
	void UseStdSwap(int a, int b);
private:
	std::vector<int> m_barsVec;
	bool m_sorted;
	sf::Uint32 m_width;
	sf::Uint32 m_height;
};

