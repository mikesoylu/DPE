#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <limits>

namespace Util
{
	const double INFINITE_MASS = std::numeric_limits<double>::max()/2.0;
	
	double Random()
	{
		return (double)rand() / RAND_MAX;
	}
	
	double Clamp(double src, double low, double hi)
	{
		if (src > hi)
			src = hi;
		if (src < low)
			src = low;
		return src;
	}
	int Clampf(int src, int low, int hi)
	{
		if (src > hi)
			src = hi;
		if (src < low)
			src = low;
		return src;
	}
	float Clampi(float src, float low, float hi)
	{
		if (src > hi)
			src = hi;
		if (src < low)
			src = low;
		return src;
	}
	
	bool IsValid(double x)
	{
		if (x != x)
		{
				// NaN.
				return false;
		}

		double infinity = std::numeric_limits<double>::infinity();
		return -infinity < x && x < infinity;
	}
};

#endif
