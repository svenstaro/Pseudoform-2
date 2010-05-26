#ifndef _SYSTEM_H_
#define _SYSTEM_H_

class ISystem
{
	public:
		virtual void init()   = 0;
		virtual void update() = 0;
};

#endif
