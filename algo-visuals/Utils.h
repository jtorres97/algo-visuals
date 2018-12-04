#pragma once

#include <SFML\Graphics.hpp>

#include <chrono>
#include <thread>

#include "Bars.h"

class Utils
{
public:
	Utils() = default;
	~Utils();

	void UpdateElements(Bars &bars, int previous, int next, sf::RenderWindow &targetWindow);
	void Sleep();
};

