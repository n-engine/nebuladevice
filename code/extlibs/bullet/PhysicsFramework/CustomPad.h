/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CUSTOMPAD_H__
#define __CUSTOMPAD_H__

#include <assert.h>
#include "FWInput.h"

#ifdef WIN32
	#include <windows.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// 入力チャンネルの種類

enum {
	BUTTON_SELECT = 0,
	BUTTON_START,
	BUTTON_L1,
	BUTTON_L2,
	BUTTON_R1,
	BUTTON_R2,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_TRIANGLE,
	BUTTON_CROSS,
	BUTTON_SQUARE,
	BUTTON_CIRCLE,
	ANALOG_XAXIS_0,
	ANALOG_YAXIS_0,
	ANALOG_ZAXIS_0,
	ANALOG_XAXIS_1,
	ANALOG_YAXIS_1,
	ANALOG_ZAXIS_1,
	ANALOG_XAXIS_2,
	ANALOG_YAXIS_2,
	ANALOG_ZAXIS_2,
	ANALOG_GYRO,
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
	CHANNEL_COUNT,
};

///////////////////////////////////////////////////////////////////////////////
// CustomPad class

class CustomPad
{
private:
	struct ChannelData {
		int channel;
		FWInputDevice **device;
	};

	ChannelData mChannelTbl[CHANNEL_COUNT];
	FWInputDevice *mPad,*mMouse,*mKeyborard;

	int mCurrentStatus,mLastStatus;
	bool mPadStatus[2][CHANNEL_COUNT];

public:
	CustomPad();
	~CustomPad();
	
	bool init(int id);
	void update();
	
	bool getCurrentStatus(int cl) {return mPadStatus[mCurrentStatus][cl];}
	bool getLastStatus(int cl) {return mPadStatus[mLastStatus][cl];}
	
	bool getBool(int cl);
	float getFloat(int cl);
};

inline 
bool CustomPad::getBool(int cl)
{
	assert(*mChannelTbl[cl].device);
	return (*mChannelTbl[cl].device)->getRawBool((FWInput::Channel)mChannelTbl[cl].channel);
}

inline
float CustomPad::getFloat(int cl)
{

	assert(*mChannelTbl[cl].device);
	return (*mChannelTbl[cl].device)->getRawFloat((FWInput::Channel)mChannelTbl[cl].channel);
}

#endif
