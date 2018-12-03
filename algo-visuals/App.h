#pragma once

#include <SFML\Graphics.hpp>

#include <vector>

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
	std::vector<int> m_array;
	bool m_isSorted;
	Sorter m_sorter;
	sf::Text m_text;
	sf::Font m_font;
};

