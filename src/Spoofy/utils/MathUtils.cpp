#include <iostream>

#include "utils/MathUtils.hpp"
#include "math.h"

void MathUtils::CalcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy)
{
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (float)(x1 - x2);
	*dx /= steps;

	*dy = (float)(y1 - y2);
	*dy /= steps;
}

int MathUtils::Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}