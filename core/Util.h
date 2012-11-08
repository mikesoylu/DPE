#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

namespace Util
{
	double Random()
	{
		return (double)rand() / RAND_MAX;
	}
};

#endif
