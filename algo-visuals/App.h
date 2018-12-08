#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Sorts.h"
#include "Bars.h"
#include "Utils.h"
#include "AssetManager.h"
#include "Config.h"

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
	Sorts m_sorts;
	Bars m_bars;
	Utils m_utils;
	sf::Text m_text;
};

