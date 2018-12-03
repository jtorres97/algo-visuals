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
	explicit Sorter(sf::Uint32 width, sf::Uint32 height, sf::RenderWindow *outputTarget);

	// Sorting funcions
	void BubbleSort(std::vector<int>& vec);

	// Utility functions
	auto MakeSwap(std::vector<int> &vec, int previous, int next);
	void UpdateSortingVector(std::vector<int> &vec, int previous, int next);
	void Shuffle(std::vector<int> &vec);
	void Sleep(sf::Uint32(time));
private:
	sf::Uint32 m_width;
	sf::Uint32 m_height;

	sf::RenderWindow *m_target;
};

