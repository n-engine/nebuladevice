/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SIMPLE_STACK_H__
#define __SIMPLE_STACK_H__

#define SIMPLE_STACK_COUNT 20

template <class StackData>
class SimpleStack
{
private:
	uint32_t cur;
	StackData stacks[SIMPLE_STACK_COUNT];

public:
	SimpleStack()
	{
		cur = 0;
	}
	
	void push(const StackData &stack)
	{
		stacks[cur++] = stack;
		PFX_ASSERT(cur<SIMPLE_STACK_COUNT);
	}
	
	StackData pop()
	{
		return stacks[--cur];
	}

	bool isEmpty()
	{
		return cur == 0;
	}

	int getStackCount()
	{
		return cur;
	}
};

#endif // __SIMPLE_STACK_H__
