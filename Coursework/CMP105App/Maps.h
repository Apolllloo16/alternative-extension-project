#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>  // For std::find, std::sort
#include "Framework/BaseLevel.h"

struct Map
{
	char Data[101][101];
	int size = 101;
};


