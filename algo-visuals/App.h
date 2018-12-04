#pragma once

#include <SFML\Graphics.hpp>

#include "Sorter.h"
#include "Bars.h"

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
	Sorter m_sorter;
	Bars m_bars;
	sf::Text m_text;
	sf::Font m_font;
};

