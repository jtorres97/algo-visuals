#include "Sorter.h"
#include "Log.h"

namespace {
	const sf::Uint32 s_sleepMsTime = 50;
}

auto Sorter::Swap(Bars &bars, int previous, int next, bool usingStdSwap)
{
	return [this, &bars, previous, next, usingStdSwap]()
	{
		if (usingStdSwap)
		{
			bars.UseStdSwap(previous, next);
			UpdateElements(bars, previous, next);
			Sleep();
		}
		else
		{
			UpdateElements(bars, previous, next);
			Sleep();
		}
	};
}

Sorter::Sorter(sf::RenderWindow *outputTarget)
	: m_target(outputTarget)
{
}

/*
	Worst and Average Case Time Complexity: O(n�). Worst case occurs when array is reverse sorted.

	Best Case Time Complexity: O(n). Best case occurs when array is already sorted.

	Auxiliary Space: O(1)

	Boundary Cases: Bubble sort takes minimum time(Order of n) when elements are already sorted.

	Sorting In Place: Yes

	Stable: Yes
*/
void Sorter::BubbleSort(Bars &bars)
{
	// Flag for swapping element
	bool isSwapped;

	// The value will be decreased every time one element has been sorted
	int unsortedElements = bars.Size();

	do
	{
		// If there's at least two element are swapped, it will be true
		isSwapped = false;

		// Iterate through the array's element
		for (int i = 0; i < unsortedElements - 1; i++)
		{
			if (bars.At(i) < bars.At(i + 1))
			{
				auto swap = Swap(bars, i, i + 1, true);
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

/*
	Time Complexity: O(n�) as there are two nested loops.

	Auxiliary Space: O(1) The good thing about selection sort is it never makes more than O(n) swaps and can 
	be useful when memory write is a costly operation.

	Stability: The default implementation is not stable. However it can be made stable. 

	In Place: Yes, it does not require extra space.
*/
void Sorter::SelectionSort(Bars &bars)
{
	// Var to store the index of min value in each iteration
	int minIndex;

	// Interate until the n-1 elements
	for (int i = 0; i < bars.Size() - 1; ++i)
	{
		// Set the first unsorted element as the min value
		minIndex = i;

		// Iterate through the unsorted elements only
		for (int j = i + 1; j < bars.Size(); ++j)
		{
			// Set the new min value, if the saved min value is higher than current 
			// index value
			if (bars.At(j) > bars.At(minIndex))
			{
				minIndex = j;
			}
			auto setNewMin = Swap(bars, i, j, false);
			setNewMin();
		}
		// Swap the first unsorted element with the min value
		auto swapWithMin = Swap(bars, i, minIndex, true);
		swapWithMin();
	}
}

/*
	Worst Case Time Complexity: O(n�). QuickSort can be implemented in different ways by changing the 
	choice of pivot, so that the worst case rarely occurs for a given type of data. However, merge sort 
	is generally considered better when data is huge and stored in external storage.

	Best Case Time Complexity: O(n log n). Best case occurs when the partition process always picks the 
	middle element as pivot.

	Average Case Time Complexity: O(n log n). To do average case analysis, we need to consider all possible
	permutation of array and calculate time taken by every permutation.

	Auxiliary Space: O(n)

	Sorting In Place: Yes

	Stable: No, can be made stable by considering indexes as comparison parameter.
*/
void Sorter::QuickSort(Bars &bars, int startIndex, int endIndex)
{
	// Only perform sort process if the end index is higher than start index
	if (startIndex < endIndex)
	{
		// Retrieve pivot position from Partition(), this pivot index is the index
		// of element that is already in correct position
		int pivotIndex = Partition(bars, startIndex, endIndex);

		// Sort left sublist arr[startIndex ... pivotIndex - 1]
		QuickSort(bars, startIndex, pivotIndex - 1);

		// Sort right sublist arr[pivotIndex + 1 ... endIndex]
		QuickSort(bars, pivotIndex + 1, endIndex);
	}
}

/*
	Time Complexity: O(n�)

	Auxiliary Space: O(1)

	Boundary Cases: Insertion sort takes maximum time to sort if elements are sorted in reverse order. 
	And it takes minimum time (Order of n) when elements are already sorted.

	Algorithmic Paradigm: Incremental Approach

	Sorting In Place: Yes

	Stable: Yes
*/
void Sorter::InsertionSort(Bars &bars)
{
	// Iterate through all array's elements
	for (int i = 0; i < bars.Size(); ++i)
	{
		// Set the current element as reference value
		int refValue = bars.At(i);

		// Var to shift the element to the right position
		int j;

		// Iterate through the sorted element to insert the refValue in right position
		for (j = i - 1; j >= 0; --j)
		{
			// If the value of the current index is less than the reference value, then
			// move the current value to right side.. otherwise, put the reference value in the 
			// current index
			if (bars.At(j) < refValue)
			{
				bars.Move(j + 1, j);

				auto moveToRight = Swap(bars, i, j, false);
				moveToRight();
			}
			else
			{
				break;
			}
		}
		// Here's the line to put the reference value in the current index (the right position)
		bars.Set(j + 1, refValue);

		auto moveRefVal = Swap(bars, i, j, false);
		moveRefVal();
	}
}

void Sorter::UpdateElements(Bars &bars, int previous, int next)
{
	// Renders the updated array to the screen
	sf::RectangleShape currentRect((sf::Vector2f(static_cast<float>(m_target->getSize().x) / static_cast<float>(bars.Size()), m_target->getSize().y)));
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

		m_target->draw(currentRect);
	}

	// Displays and clears the newly drawn array
	m_target->display();
	m_target->clear();
}

int Sorter::Partition(Bars &bars, int startIndex, int endIndex)
{
	// Set the first item as pivot
	int pivot = bars.At(startIndex);

	// Left sublist and right sublist are initially empty
	int middleIndex = startIndex;

	// Iterate through arr[1 ... n - 1]
	for (int i = startIndex + 1; i <= endIndex; ++i)
	{
		if (bars.At(i) > pivot)
		{
			// The current item is on the left sublist, prepare a seat by shifting middle index
			++middleIndex;

			// The arr[middleIndex] is the member of right sublist, swap it to the current item 
			// Which is member of left list
			auto swapToCurrent = Swap(bars, i, middleIndex, true);
			swapToCurrent();
		}
	}

	// By now, the arr[middleIndex] item is member of left sublist.
	// We can swap it with the pivot, so the pivot will be in the correct position
	// which is between left sublist and right sublist
	auto swapToPivot = Swap(bars, startIndex, middleIndex, true);
	swapToPivot();

	// Return the index of pivot to be used by next quicksort
	return middleIndex;
}

void Sorter::Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(s_sleepMsTime));
}
