#include "App.h"
#include "Log.h"

namespace {
	sf::Uint32 s_screenWidth = 800;
	sf::Uint32 s_screenHeight = 540;
	const int s_numElements = 25;
}

template<typename Resource>
void CenterOrigin(Resource & resource)
{
	sf::FloatRect bounds = resource.getLocalBounds();
	resource.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

App::App()
	: m_mainWindow(sf::VideoMode(s_screenWidth, s_screenHeight), "Algorithms Visualized", sf::Style::Titlebar | sf::Style::Close)
	, m_sorter(&m_mainWindow)
	, m_text()
	, m_font()
	, m_bars(s_screenWidth, s_screenHeight, s_numElements)
{
	// Enable V-Sync
	m_mainWindow.setVerticalSyncEnabled(true);

	// Load font
	if (!m_font.loadFromFile("res/fonts/Open 24 Display St.ttf"))
		LOG_WARNING("Failed to load font!");

	// Set font properties
	m_text.setFont(m_font);
	m_text.setStyle(sf::Text::Bold);
	m_text.setCharacterSize(20);
	m_text.setOutlineThickness(2.f);
	m_text.setFillColor(sf::Color::Green);
	m_text.setPosition(s_screenWidth * 0.4f, 50.f);
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
				m_sorter.BubbleSort(m_bars);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::S && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Selection sort...");
				m_sorter.SelectionSort(m_bars);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::Q && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Quick sort...");
				m_sorter.QuickSort(m_bars, 0, m_bars.Size() - 1);
				m_bars.SetSortStatus(true);
			}
			else if (event.key.code == sf::Keyboard::I && !m_bars.IsSorted())
			{
				m_mainWindow.setTitle("Performing Insertion sort...");
				m_sorter.InsertionSort(m_bars);
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
		m_text.setPosition(s_screenWidth * 0.4f, 50.f);
	}
	if (m_bars.IsSorted())
	{
		std::string str = "Bars are sorted!";
		m_mainWindow.setTitle(str);
		m_text.setString("\nPress R to shuffle the bars");
		m_text.setPosition(s_screenWidth * 0.35f, 50.f);
	}
}

void App::Render()
{
	m_mainWindow.clear();

	sf::RectangleShape currentRect((sf::Vector2f(s_screenWidth / m_bars.Size(), s_screenHeight)));
	for (int i = 0; i < m_bars.Size(); i++)
	{
		currentRect.setFillColor(sf::Color::White);
		currentRect.setOutlineColor(sf::Color::Black);
		currentRect.setOutlineThickness(1.5);
		currentRect.setPosition(i * currentRect.getSize().x, m_bars.At(i));
		m_mainWindow.draw(currentRect);
	}

	m_mainWindow.draw(m_text);

	m_mainWindow.display();
}
