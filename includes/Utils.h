#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>
#include <thread>

#include "Bars.h"

struct Utils
{
	Utils() = default;

	void UpdateElements(Bars &bars, int previous, int next, sf::RenderWindow &targetWindow);
};

