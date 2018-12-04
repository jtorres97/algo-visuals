#include "Utils.h"
#include "Log.h"

namespace {
	const sf::Uint32 s_sleepMsTime = 50;
}

Utils::~Utils()
{
}

void Utils::UpdateElements(Bars &bars, int previous, int next, sf::RenderWindow &targetWindow)
{
	// Renders the updated array to the screen
	sf::RectangleShape currentRect((sf::Vector2f(800 / static_cast<float>(bars.Size()), 540)));
	for (int i = 0; i < bars.Size(); i++)
	{
		currentRect.setFillColor(sf::Color::White);
		currentRect.setOutlineColor(sf::Color::Black);
		currentRect.setOutlineThickness(1.5);

		if (i == previous)
		{
			currentRect.setFillColor(sf::Color::Green);
		}

		if (i == next)
		{
			currentRect.setFillColor(sf::Color::Red);
		}
		currentRect.setPosition(i * currentRect.getSize().x, bars.At(i));

		targetWindow.draw(currentRect);
	}

	// Displays and clears the newly drawn array
	targetWindow.display();
	targetWindow.clear();
}

void Utils::Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(s_sleepMsTime));
}
