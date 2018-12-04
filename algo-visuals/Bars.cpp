#include "Bars.h"
#include "Log.h"

Bars::Bars(sf::Uint32 width, sf::Uint32 height, const int numElements)
	: m_barsVec(numElements)
	, m_sorted(false)
	, m_width(width)
	, m_height(height)
{
	// Initialize bars
	for (int i = 0; i < m_barsVec.size(); i++)
	{
		m_barsVec[i] = m_height - (m_height / m_barsVec.size()) * i;
	}

	// Shuffle the bars
	Shuffle();
}

std::vector<int> Bars::GetVec()
{
	return m_barsVec;
}

void Bars::SetSortStatus(bool sorted)
{
	this->m_sorted = sorted;
}

bool Bars::IsSorted()
{
	return m_sorted == true;
}

void Bars::Shuffle()
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::shuffle(m_barsVec.begin(), m_barsVec.end(), randomGenerator);
}

int Bars::Size()
{
	return m_barsVec.size();
}

int Bars::At(int index)
{
	return m_barsVec[index];
}

void Bars::Move(int index, int newDest)
{
	m_barsVec[index] = m_barsVec[newDest];
}

void Bars::Set(int index, int newVal)
{
	m_barsVec[index] = newVal;
}

void Bars::UseStdSwap(int a, int b)
{
	std::swap(m_barsVec[a], m_barsVec[b]);
}
