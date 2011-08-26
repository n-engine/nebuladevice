/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CUSTOMTIME_H__
#define __CUSTOMTIME_H__

#include "FWTime.h"

class CustomTime : public FWTime
{
private:
	FWTimeVal t1,t2;

public:
	void	beginTime()
	{
		update();
		t1 = getCurrentTime();
	}

	void	endTime()
	{
		update();
		t2 = getCurrentTime()-t1;
	}

	float	getElapsedTime()
	{
		return (float)t2*1000.0f;
	}
};

#endif
