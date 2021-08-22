#ifndef _H_SCPRUNTIMESTACK
#define _H_SCPRUNTIMESTACK

#include "ScpObject.h"
#include <stack>

typedef std::stack<ScpObject *>   ScpObjectStack;
class ScpRuntimeStack 	
{
public:
	ScpRuntimeStack();
	~ScpRuntimeStack();
	void Push(ScpObject * obj)
	{
		objstack.push(obj);
	}
	ScpObject * Pop()
	{
		ScpObject * obj = objstack.top();
		objstack.pop();
		return obj;
	}
	ScpObject * Peek()
	{
		ScpObject * obj = objstack.top();
		return obj;
	}
	void IsEmpty()
	{
		objstack.empty();
	}
	void Clear()
	{
		ScpObject * obj = objstack.top();
		while (obj)
		{
			objstack.pop();
			obj = objstack.top();
		}
	}
	ScpObjectStack objstack;
};

#endif