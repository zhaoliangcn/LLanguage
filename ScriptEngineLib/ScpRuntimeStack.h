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
	ScpObject * Pop() noexcept
	{
		ScpObject * obj = objstack.top();
		objstack.pop();
		return obj;
	}
	ScpObject * Peek() noexcept
	{
		ScpObject * obj = objstack.top();
		return obj;
	}
	bool IsEmpty() noexcept
	{
		return objstack.empty();
	}
	void Clear() noexcept
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