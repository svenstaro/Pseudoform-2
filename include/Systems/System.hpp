#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <iostream>

class ISystem
{
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual std::string toString() = 0;
};

#endif
