#ifndef _H_SCPMATHMATICLIB
#define _H_SCPMATHMATICLIB
#include <math.h>
class ScpMathmaticLib
{
public:
	ScpMathmaticLib(void);
	~ScpMathmaticLib(void);

	int _abs(int in)
	{
		return abs(in);
	}
};


#endif //_H_SCPMATHMATICLIB