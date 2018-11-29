#include "App.h"
#include "Log.h"

App::App()
	: m_mainWindow(sf::VideoMode(800, 540), "Sorting Visuals", sf::Style::Titlebar | sf::Style::Close)
{
	m_mainWindow.setVerticalSyncEnabled(true);
}

App::~App()
{
}

void App::Run()
{
	while (m_mainWindow.isOpen())
	{
		ProcessEvents();
		Update();
		Render();
	}
}

void App::ProcessEvents()
{
	sf::Event event;
	while (m_mainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_mainWindow.close();

		if (event.type == sf::Event::MouseMoved)
		{
			LOG_DEBUG("Mouse (x, y): " << event.mouseMove.x << ", " << event.mouseMove.y);
		}
	}
}

void App::Update()
{
}

void App::Render()
{
	m_mainWindow.clear();
	m_mainWindow.display();
}
