#include "Bars.h"

Bars::Bars(sf::RenderWindow &outputTarget, const int numElements)
	: m_sorted(false)
	, m_target(outputTarget)
{
	// Initialize bars
	for (auto i = 0; i < numElements; i++)
	{
		this->push_back(WINDOW_HEIGHT - (WINDOW_HEIGHT / numElements) * i);
	}

	// Shuffle the bars
	Shuffle();
}

Bars::~Bars()
{
}

void Bars::SetSortStatus(bool sorted)
{
	this->m_sorted = sorted;
}

bool Bars::IsSorted()
{
	return this->m_sorted == true;
}

void Bars::Shuffle()
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(this->begin(), this->end(), randomGenerator);
}

void Bars::Render()
{
	sf::RectangleShape currentRect((sf::Vector2f(WINDOW_WIDTH / this->size(), WINDOW_HEIGHT)));
	for (int i = 0; i < this->size(); i++)
	{
		currentRect.setFillColor(sf::Color::White);
		currentRect.setOutlineColor(sf::Color::Black);
		currentRect.setOutlineThickness(1.5);
		currentRect.setPosition(i * currentRect.getSize().x, this->at(i));
		m_target.draw(currentRect);
	}
}
