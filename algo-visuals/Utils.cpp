#include "Utils.h"
#include "Log.h"

void Utils::UpdateElements(Bars &bars, int previous, int next, sf::RenderWindow &targetWindow)
{
	sf::RectangleShape currentRect((sf::Vector2f(targetWindow.getSize().x / static_cast<float>(bars.size()), targetWindow.getSize().y)));
	for (int i = 0; i < bars.size(); i++)
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
		currentRect.setPosition(i * currentRect.getSize().x, bars[i]);

		targetWindow.draw(currentRect);
	}

	targetWindow.display();
	targetWindow.clear();
}
