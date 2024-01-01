#pragma once
#include <intrin.h>

#ifdef DEBUG
	#define ASSERT(expression, assertionMessage) if(!(expression)){std::cout << "\"" <<assertionMessage << "\" assertion failed at line " << __LINE__ << " in function \'" << __func__ << "\' in " << __FILE__ << std::endl; __debugbreak();}
#else
	#define ASSERT(expression, assertionMessage) if(!(expression))std::abort();
#endif