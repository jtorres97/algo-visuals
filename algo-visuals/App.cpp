#include "App.h"
#include "Log.h"

AssetManager assetManager;

namespace {
	const int s_numElements = 100;
}

template<typename Resource>
void CenterOrigin(Resource & resource)
{
	sf::FloatRect bounds = resource.getLocalBounds();
	resource.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

App::App()
	: m_mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Algorithms Visualized", sf::Style::Titlebar | sf::Style::Close)
	, m_sorts(m_mainWindow)
	, m_bars(m_mainWindow, s_numElements)
	, m_text()
{
	std::cout << R"(
   _   _                  _ _   _                           _                 _ _             _ 
  /_\ | | __ _  ___  _ __(_) |_| |__  _ __ ___  ___  /\   /(_)___ _   _  __ _| (_)_______  __| |
 //_\\| |/ _` |/ _ \| '__| | __| '_ \| '_ ` _ \/ __| \ \ / / / __| | | |/ _` | | |_  / _ \/ _` |
/  _  \ | (_| | (_) | |  | | |_| | | | | | | | \__ \  \ V /| \__ \ |_| | (_| | | |/ /  __/ (_| |
\_/ \_/_|\__, |\___/|_|  |_|\__|_| |_|_| |_| |_|___/   \_/ |_|___/\__,_|\__,_|_|_/___\___|\__,_|
         |___/                                                                                  

--------------------------------------By: Joshua Torres-----------------------------------------
	)" << std::endl;

	// Limit FPS
	m_mainWindow.setFramerateLimit(23);

	// Set font properties
	m_text.setFont(AssetManager::GetFont("res/fonts/Open 24 Display St.ttf"));
	m_text.setStyle(sf::Text::Bold);
	m_text.setCharacterSize(20);
	m_text.setOutlineThickness(2.f);
	m_text.setFillColor(sf::Color::Green);
	m_text.setPosition(WINDOW_WIDTH * 0.4f, 50.f);
	CenterOrigin(m_text);
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
			if (event.key.code == sf::Keyboard::R)
			{
				LOG_INFO("Shuffling...");
				m_bars.Shuffle();
				m_bars.SetSortStatus(false);
			}
			else if (event.key.code == sf::Keyboard::B && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Bubble Sort...");
				m_sorts.BubbleSort(m_bars);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::S && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Selection sort...");
				m_sorts.SelectionSort(m_bars);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::Q && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Quick sort...");
				m_sorts.QuickSort(m_bars, 0, m_bars.size() - 1);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::I && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Insertion sort...");
				m_sorts.InsertionSort(m_bars);
				m_bars.SetSortStatus(true);
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
	if (!m_bars.IsSorted())
	{
		std::string str = "Choose your sort!";
		m_mainWindow.setTitle(str);
		m_text.setString( 
			 "\nB - Bubble Sort"
			 "\nS - Selection Sort"
			 "\nQ - Quick Sort"
			 "\nI - Insertion Sort"
		);
		m_text.setPosition(WINDOW_WIDTH * 0.4f, 50.f);
	}
	if (m_bars.IsSorted())
	{
		std::string str = "Bars are sorted!";
		m_mainWindow.setTitle(str);
		m_text.setString("\nPress R to shuffle the bars");
		m_text.setPosition(WINDOW_WIDTH * 0.35f, 50.f);
	}
}

void App::Render()
{
	m_mainWindow.clear();

	m_bars.Render();
	m_mainWindow.draw(m_text);

	m_mainWindow.display();
}
