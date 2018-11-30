#pragma once

#include <SFML\Graphics.hpp>

#include <chrono>
#include <thread>
#include <vector>

class Sorter
{
public:
	explicit Sorter(sf::Uint32 width, sf::Uint32 height, sf::RenderWindow *outputTarget);

	// Sorting funcions
	void BubbleSort(std::vector<int>& vec);

	// Utility functions
	void Swap(std::vector<int> &vec, int previous, int next);
	void Render(std::vector<int> &vec, int previous, int next);
	void Sleep(sf::Uint32(time));
private:
	sf::Uint32 m_width;
	sf::Uint32 m_height;

	sf::RenderWindow *m_target;
};

