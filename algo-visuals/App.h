#pragma once

#include <SFML\Graphics.hpp>

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
};

