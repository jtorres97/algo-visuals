#include "Sorter.h"
#include "Log.h"

namespace {
	const sf::Uint32 s_sleepMsTime = 30;
}

auto Sorter::MakeSwap(std::vector<int> &vec, int previous, int next)
{
	return [this, &vec, previous, next]()
	{
		std::swap(vec[previous], vec[next]);
		UpdateElements(vec, previous, next);
		Sleep();
	};
}

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
				auto swap = MakeSwap(vec, i, i + 1);
				swap();

				isSwapped = true;
			}
		}

		// After iteration, last element has been sorted so it will be ignored in the next iteration
		--unsortedElements;
	}
	// Do comparison again if there's swapped element
	while (isSwapped);
}

// Time Complexity : O(n²) as there are two nested loops.
// Auxiliary Space : O(1)
// The good thing about selection sort is it never makes more than O(n) swaps and can be useful when memory write is a costly operation.
// Stability : The default implementation is not stable. However it can be made stable. 
// In Place : Yes, it does not require extra space
void Sorter::SelectionSort(std::vector<int>& vec)
{
	// Var to store the index of min value in each iteration
	int minIndex;

	// Interate until the n-1 elements
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		// Set the first unsorted element as the min value
		minIndex = i;

		// Iterate through the unsorted elements only
		for (int j = i + 1; j < vec.size(); ++j)
		{
			// Set the new min value, if the saved min value is higher than current 
			// index value
			if (vec[j] > vec[minIndex])
			{
				minIndex = j;
			}
			UpdateElements(vec, i, j);
			Sleep();
		}
		// Swap the first unsorted element with the min value
		//Swap(vec, i, minIndex);
		auto swapWithMin = MakeSwap(vec, i, minIndex);
		swapWithMin();
	}
}

void Sorter::UpdateElements(std::vector<int> &vec, int previous, int next)
{
	// Renders the updated array to the screen
	sf::RectangleShape currentRect((sf::Vector2f(static_cast<float>(m_width) / static_cast<float>(vec.size()), m_height)));
	for (int i = 0; i < vec.size(); i++)
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
		currentRect.setPosition(i * currentRect.getSize().x, vec[i]);

		m_target->draw(currentRect);
	}

	// Displays and clears the newly drawn array
	m_target->display();
	m_target->clear();
}

void Sorter::Shuffle(std::vector<int>& vec)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(vec.begin(), vec.end(), randomGenerator);
}

void Sorter::Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(s_sleepMsTime));
}
