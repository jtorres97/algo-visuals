#include "Sorter.h"
#include "Log.h"

Sorter::Sorter(sf::Uint32 width, sf::Uint32 height, sf::RenderWindow *outputTarget)
	: m_width(width)
	, m_height(height)
	, m_target(outputTarget)
{
}

// Worst and Average Case Time Complexity : O(n²). Worst case occurs when array is reverse sorted.
// Best Case Time Complexity : O(n). Best case occurs when array is already sorted.
// Auxiliary Space : O(1)
// Boundary Cases : Bubble sort takes minimum time(Order of n) when elements are already sorted.
// Sorting In Place : Yes
// Stable : Yes
void Sorter::BubbleSort(std::vector<int> &vec)
{
	// Flag for swapping element
	bool isSwapped;

	// The value will be decreased every time one element has been sorted
	int unsortedElements = vec.size();

	do
	{
		// If there's at least two element are swapped, it will be true
		isSwapped = false;

		// Iterate through the array's element
		for (int i = 0; i < unsortedElements - 1; i++)
		{
			if (vec[i] < vec[i + 1])
			{
				Swap(vec, i, i + 1);
				isSwapped = true;
			}
		}

		// After iteration, last element has been sorted so it will be ignored in the next iteration
		--unsortedElements;
	}
	// Do comparison again if there's swapped element
	while (isSwapped);
}

void Sorter::Swap(std::vector<int> &vec, int previous, int next)
{
	int temp = vec[previous];
	vec[previous] = vec[next];
	vec[next] = temp;

	Render(vec, previous, next);
	Sleep(50);
}

void Sorter::Render(std::vector<int> &vec, int previous, int next)
{
	// Renders the updated array to the screen
	sf::RectangleShape currentRect((sf::Vector2f(static_cast<float>(m_width) / static_cast<float>(vec.size()), m_height)));
	for (int i = 0; i < vec.size(); i++)
	{
		currentRect.setFillColor(sf::Color::White);
		currentRect.setOutlineColor(sf::Color::Black);
		currentRect.setOutlineThickness(1.5);

		if (i == previous) currentRect.setFillColor(sf::Color::Green);
		if (i == next) currentRect.setFillColor(sf::Color::Red);

		currentRect.setPosition(i * currentRect.getSize().x, vec[i]);

		m_target->draw(currentRect);
	}

	// Displays and clears the newly drawn array
	m_target->display();
	m_target->clear();
}

void Sorter::Sleep(sf::Uint32(time))
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
