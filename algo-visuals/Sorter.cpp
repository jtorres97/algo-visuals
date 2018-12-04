#include "Sorter.h"
#include "Log.h"

namespace {
	const sf::Uint32 s_sleepMsTime = 50;
}

auto Sorter::Swap(std::vector<int> &arr, int previous, int next, bool usingStdSwap)
{
	return [this, &arr, previous, next, usingStdSwap]()
	{
		if (usingStdSwap)
		{
			std::swap(arr[previous], arr[next]);
			UpdateElements(arr, previous, next);
			Sleep();
		}
		else
		{
			UpdateElements(arr, previous, next);
			Sleep();
		}
	};
}

Sorter::Sorter(sf::Uint32 width, sf::Uint32 height, sf::RenderWindow *outputTarget)
	: m_width(width)
	, m_height(height)
	, m_target(outputTarget)
{
}

/*
	Worst and Average Case Time Complexity: O(n²). Worst case occurs when array is reverse sorted.

	Best Case Time Complexity: O(n). Best case occurs when array is already sorted.

	Auxiliary Space: O(1)

	Boundary Cases: Bubble sort takes minimum time(Order of n) when elements are already sorted.

	Sorting In Place: Yes

	Stable: Yes
*/
void Sorter::BubbleSort(std::vector<int> &arr)
{
	// Flag for swapping element
	bool isSwapped;

	// The value will be decreased every time one element has been sorted
	int unsortedElements = arr.size();

	do
	{
		// If there's at least two element are swapped, it will be true
		isSwapped = false;

		// Iterate through the array's element
		for (int i = 0; i < unsortedElements - 1; i++)
		{
			if (arr[i] < arr[i + 1])
			{
				auto swap = Swap(arr, i, i + 1, true);
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
	Time Complexity: O(n²) as there are two nested loops.

	Auxiliary Space: O(1) The good thing about selection sort is it never makes more than O(n) swaps and can 
	be useful when memory write is a costly operation.

	Stability: The default implementation is not stable. However it can be made stable. 

	In Place: Yes, it does not require extra space.
*/
void Sorter::SelectionSort(std::vector<int>& arr)
{
	// Var to store the index of min value in each iteration
	int minIndex;

	// Interate until the n-1 elements
	for (int i = 0; i < arr.size() - 1; ++i)
	{
		// Set the first unsorted element as the min value
		minIndex = i;

		// Iterate through the unsorted elements only
		for (int j = i + 1; j < arr.size(); ++j)
		{
			// Set the new min value, if the saved min value is higher than current 
			// index value
			if (arr[j] > arr[minIndex])
			{
				minIndex = j;
			}
			auto setNewMin = Swap(arr, i, j, false);
			setNewMin();
		}
		// Swap the first unsorted element with the min value
		auto swapWithMin = Swap(arr, i, minIndex, true);
		swapWithMin();
	}
}

/*
	Worst Case Time Complexity: O(n²). QuickSort can be implemented in different ways by changing the 
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
void Sorter::QuickSort(std::vector<int>& arr, int startIndex, int endIndex)
{
	// Only perform sort process if the end index is higher than start index
	if (startIndex < endIndex)
	{
		// Retrieve pivot position from Partition(), this pivot index is the index
		// of element that is already in correct position
		int pivotIndex = Partition(arr, startIndex, endIndex);

		// Sort left sublist arr[startIndex ... pivotIndex - 1]
		QuickSort(arr, startIndex, pivotIndex - 1);

		// Sort right sublist arr[pivotIndex + 1 ... endIndex]
		QuickSort(arr, pivotIndex + 1, endIndex);
	}
}

/*
	Time Complexity: O(n²)

	Auxiliary Space: O(1)

	Boundary Cases: Insertion sort takes maximum time to sort if elements are sorted in reverse order. 
	And it takes minimum time (Order of n) when elements are already sorted.

	Algorithmic Paradigm: Incremental Approach

	Sorting In Place: Yes

	Stable: Yes
*/
void Sorter::InsertionSort(std::vector<int> &arr)
{
	// Iterate through all array's elements
	for (int i = 0; i < arr.size(); ++i)
	{
		// Set the current element as reference value
		int refValue = arr[i];

		// Var to shift the element to the right position
		int j;

		// Iterate through the sorted element to insert the refValue in right position
		for (j = i - 1; j >= 0; --j)
		{
			// If the value of the current index is less than the reference value, then
			// move the current value to right side.. otherwise, put the reference value in the 
			// current index
			if (arr[j] < refValue)
			{
				arr[j + 1] = arr[j];
				auto moveToRight = Swap(arr, i, j, false);
				moveToRight();
			}
			else
			{
				break;
			}
		}
		// Here's the line to put the reference value in the current index (the right position)
		arr[j + 1] = refValue;
		
		auto moveRefVal = Swap(arr, i, j, false);
		moveRefVal();
	}
}

void Sorter::UpdateElements(std::vector<int> &arr, int previous, int next)
{
	// Renders the updated array to the screen
	sf::RectangleShape currentRect((sf::Vector2f(static_cast<float>(m_width) / static_cast<float>(arr.size()), m_height)));
	for (int i = 0; i < arr.size(); i++)
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
		currentRect.setPosition(i * currentRect.getSize().x, arr[i]);

		m_target->draw(currentRect);
	}

	// Displays and clears the newly drawn array
	m_target->display();
	m_target->clear();
}

int Sorter::Partition(std::vector<int>& arr, int startIndex, int endIndex)
{
	// Set the first item as pivot
	int pivot = arr[startIndex];

	// Left sublist and right sublist are initially empty
	int middleIndex = startIndex;

	// Iterate through arr[1 ... n - 1]
	for (int i = startIndex + 1; i <= endIndex; ++i)
	{
		if (arr[i] > pivot)
		{
			// The current item is on the left sublist, prepare a seat by shifting middle index
			++middleIndex;

			// The arr[middleIndex] is the member of right sublist, swap it to the current item 
			// Which is member of left list
			auto swapToCurrent = Swap(arr, i, middleIndex, true);
			swapToCurrent();
		}
	}

	// By now, the arr[middleIndex] item is member of left sublist.
	// We can swap it with the pivot, so the pivot will be in the correct position
	// which is between left sublist and right sublist
	auto swapToPivot = Swap(arr, startIndex, middleIndex, true);
	swapToPivot();

	// Return the index of pivot to be used by next quicksort
	return middleIndex;
}

void Sorter::Shuffle(std::vector<int>& arr)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(arr.begin(), arr.end(), randomGenerator);
}

void Sorter::Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(s_sleepMsTime));
}
