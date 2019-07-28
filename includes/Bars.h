#pragma once

#include <SFML\Graphics.hpp>

#include <vector>
#include <algorithm>
#include <random>

#include "Config.h"

class Bars : public std::vector<int> 
{
public:
	Bars(sf::RenderWindow &outputTarget, const int numElements);
	~Bars();

	bool IsSorted();
	void SetSortStatus(bool sorted);
	void Shuffle();
	void Render();
private:
	bool m_sorted;
	sf::RenderWindow &m_target;
};

