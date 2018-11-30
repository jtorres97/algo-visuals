#pragma once

#include <SFML\Graphics.hpp>

#include <vector>
#include <algorithm>
#include <random>

#include "Sorter.h"

#define NUM_BARS 50

class App
{
public:
	App();
	~App();

	void Run();
	void ProcessEvents();
	void Update();
	void Render();
private:
	sf::RenderWindow m_mainWindow;
	std::vector<int> m_bars;
	bool m_isSorted;
	Sorter m_sorter;
};

