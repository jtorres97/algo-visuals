#include "App.h"
#include "Log.h"

namespace {
	sf::Uint32 s_screenWidth = 800;
	sf::Uint32 s_screenHeight = 540;
}

App::App()
	: m_mainWindow(sf::VideoMode(s_screenWidth, s_screenHeight), "Sorting Visuals", sf::Style::Titlebar | sf::Style::Close)
	, m_sorter(s_screenWidth, s_screenHeight, &m_mainWindow)
	, m_isSorted(false)
	, m_bars(NUM_BARS)
{
	// Enable V-Sync
	m_mainWindow.setVerticalSyncEnabled(true);
	
	// Initialze the bars array
	for (int i = 0; i < m_bars.size(); i++)
	{
		m_bars[i] = s_screenHeight - (s_screenHeight / m_bars.size()) * i;
		LOG_DEBUG("Bar " << i << ": " << m_bars[i]);
	}

	// Shuffle the array
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(m_bars.begin(), m_bars.end(), randomGenerator);
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
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::S && m_isSorted)
			{
				LOG_INFO("Shuffling bars...");
				std::random_device rd;
				std::mt19937 randomGenerator(rd());
				std::shuffle(m_bars.begin(), m_bars.end(), randomGenerator);
				m_isSorted = false;
			}
			else if (event.key.code == sf::Keyboard::B && !m_isSorted)
			{
				LOG_INFO("Performing Bubble Sort on bars...");
				m_sorter.BubbleSort(m_bars);
				m_isSorted = true;
			}
			break;
		case sf::Event::Closed:
			m_mainWindow.close();
			break;
		}
	}
}

void App::Update()
{

}

void App::Render()
{
	m_mainWindow.clear();

	sf::RectangleShape currentRect((sf::Vector2f(s_screenWidth / m_bars.size(), s_screenHeight)));
	for (int i = 0; i < m_bars.size(); i++)
	{
		currentRect.setFillColor(sf::Color::White);
		currentRect.setOutlineColor(sf::Color::Black);
		currentRect.setOutlineThickness(1.5);
		currentRect.setPosition(i * currentRect.getSize().x, m_bars[i]);
		m_mainWindow.draw(currentRect);
	}

	m_mainWindow.display();
}
