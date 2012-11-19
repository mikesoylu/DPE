#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

namespace Util
{
	const double INFINITE_MASS = 1024.0*1024.0;
	
	double Random()
	{
		return (double)rand() / RAND_MAX;
	}
};

#endif
