/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#ifndef __FW_INPUT_H__
#define __FW_INPUT_H__

#if !defined(_WIN32)
#if !defined(__linux__)
#include <cell/pad.h>
#endif // !defined(__linux__)
#endif // !defined(_WIN32)

// Maximum number of devices
#define FWINPUT_MAX_DEVICES	256
// Maximum number of filters per device
#define FWINPUT_MAX_FILTERS	256

class FWInputDevice;

// Input class.
// Contains a number of static methods for enumerating and utilizing input devices
// such as keyboards, mice and game controllers.
// Call <c>enumerateDevices()</c> to obtain a list of attached devices, or use
// <c>getDevice()</c> to try and get a pointer to a specific device type.
class FWInput
{
public:
	//-----------------------------------------------------------------------------
	// Description: Device type enumeration
	//-----------------------------------------------------------------------------
	enum					DeviceType
	{
							DeviceType_Mouse,		// Mouse
							DeviceType_Keyboard,	// Keyboard
							DeviceType_Pad,			// Game pad
	};

	//-----------------------------------------------------------------------------
	// Description: Input channel enumeration
	//-----------------------------------------------------------------------------
	enum					Channel
	{

#include "FWInputChannels.h"

	};

	static void				init(void *pPlatformData);
	static void				shutdown();
	static void				update();
	static int				enumerateDevices(FWInputDevice **ppDevices);
	static FWInputDevice	*getDevice(DeviceType type, int instance);
	static Channel			asciiToChannel(int ascii);

private:
	static bool				platformInit(void *pPlatformData);
	static void				platformShutdown();
	static void				platformUpdate();
	static void				addDevice(FWInputDevice *pDevice);

	// Static array of device pointers
	static FWInputDevice	*sppDevices[FWINPUT_MAX_DEVICES];
	// Ascii lookup table
	static unsigned char	sAsciiLookup[128];

	// Friend of <c>FWInputDevice</c>
	friend class			FWInputDevice;
};

// Input filter class.
// Used to filter a specific input channel from a device
// (for example a key, button or axis).
// Bind a filter to a device using the <c>bindFilter()</c> method in <c>FWInputDevice</c>,
// then set the channel using <c>setChannel()</c>. You can then read the status of the channel
// using the <c>getFloatValue()</c> or <c>getBoolValue()</c> methods.
// Other methods also exist to set the channel's gain, bias and deadzone values.
class FWInputFilter
{
public:
							FWInputFilter();
							~FWInputFilter();

	//-----------------------------------------------------------------------------
	// Description: Set the channel to filter
	// Parameters:	channel - Input channel
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setChannel(FWInput::Channel channel)
	{
		mChannel = channel;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the filter's gain
	// Parameters:	gain - Gain value
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setGain(float gain)
	{
		mGain = gain;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the filter's bias
	// Parameters:	bias - Bias value
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setBias(float bias)
	{
		mBias = bias;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the filter's deadzone
	// Parameters:	zone - Deadzone (after gain)
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setDeadzone(float zone)
	{
		mDeadzone = zone;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the filter's value as a float
	// Parameters:
	// Returns: Float value
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getFloatValue() const
	{
		return mFloatValue;
	}

	inline int getRawValue() const
	{
		return mRawValue;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the filter's value as a bool
	// Parameters:
	// Returns: Bool value
	// Notes:
	//-----------------------------------------------------------------------------
	inline bool getBoolValue() const
	{
		return mBoolValue;
	}

	//-----------------------------------------------------------------------------
	// Description: Returns true if the filter has changed state from false to true
	// Parameters:
	// Returns: Bool value
	// Notes:
	//-----------------------------------------------------------------------------
	inline bool getBoolTrue() const
	{
		return mBoolTrue;
	}

	//-----------------------------------------------------------------------------
	// Description: Returns true if the filter has changed state from true to false
	// Parameters:
	// Returns: Bool value
	// Notes:
	//-----------------------------------------------------------------------------
	inline bool getBoolFalse() const
	{
		return mBoolFalse;
	}



private:
	void					update();
	void					calcValues(int iVal);
	void					calcValues(bool bVal);

	// Device this filter is bound to
	FWInputDevice			*mpBoundDevice;
	// Device binding value
	int						mDeviceBinding;
	// Channel this filter is set to
	FWInput::Channel		mChannel;
	// Gain value
	float					mGain;
	// Bias value
	float					mBias;
	// Deadzone value
	float					mDeadzone;
	// Device value as float
	float					mFloatValue;
	// Device value as int
	int						mRawValue;
	// Device value as bool
	bool					mBoolValue;
	// Device value as bool set when bool value changes from false to true
	bool					mBoolTrue;
	// Device value as bool set when bool value changes from true to false
	bool					mBoolFalse;

	// Friend of <c>FWInputDevice</c>
	friend class			FWInputDevice;
};

// Input device.
// Abstract base class for input devices.
// You can read the channel values of a device directly by using the
// <c>getRawFloat()</c> and <c>getRawBool()</c> methods. To obtain filtered
// values, use the <c>bindFilter()</c> method to get a pointer to an
// <c>FWInputFilter</c> object which can then be queried.
class FWInputDevice
{
public:
									FWInputDevice(void *pPlatformData);
	virtual							~FWInputDevice();

	//-----------------------------------------------------------------------------
	// Description: Get device type
	// Parameters:
	// Returns: Type of device
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual FWInput::DeviceType		getType() const = 0;
	
	FWInputFilter					*bindFilter();
	void							unbindFilter(FWInputFilter *pFilter);
	bool							getRawBool(FWInput::Channel eChannel);
	float							getRawFloat(FWInput::Channel eChannel);

#if !defined(_WIN32)
#if !defined(__linux__)
	// to keep track of button pressure
	CellPadData padData;
#endif // !defined(__linux__)
#endif // !defined(_WIN32)

protected:
	virtual void					update();
	void							addFilter(FWInputFilter *pFilter);

	// Array of input filters bound to this device
	FWInputFilter					*mppFilters[FWINPUT_MAX_FILTERS];

	// X-axis values
	int								mXAxis[3];
	// Y-axis values
	int								mYAxis[3];
	// Z-axis values
	int								mZAxis[3];
	// Gyro values
	int								mGyro;
	// Button values
	bool							mButtons[16];
	// Key values
	bool							mKeys[256];
	// Platform specific data
	void							*mpPlatformData;

	// Friend of <c>FWInput</c>
	friend class					FWInput;
	// Friend of <c>FWInputFilter</c>
	friend class					FWInputFilter;
};

// Mouse input device class.
// Derives from <c>FWInputDevice</c>.
// If you require client relative co-ordinates from the mouse instead of a
// motion vector, call <c>setClientRelative()</c>.
class FWInputDeviceMouse : public FWInputDevice
{
public:
									FWInputDeviceMouse(void *pPlatformData);
	virtual 						~FWInputDeviceMouse();

	virtual  FWInput::DeviceType	getType() const;

	//-----------------------------------------------------------------------------
	// Description: Set client relative mode
	// Parameters:	enable - Enable/disable client relative mode
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void						setClientRelative(bool enable)
	{
		mIsClientRelative = enable;
	}

protected:
	virtual void					update();
	// Set if the mouse device is to return client relative coordinates
	// rather than a motion vector
	bool							mIsClientRelative;

};

// Keyboard input device class.
// Derives from <c>FWInputDevice</c>.
class FWInputDeviceKeyboard : public FWInputDevice
{
public:
									FWInputDeviceKeyboard(void *pPlatformData);
	virtual							~FWInputDeviceKeyboard();

	virtual FWInput::DeviceType		getType() const;

protected:
	virtual void					update();
};

// Game pad input device class.
// Derives from <c>FWInputDevice</c>.
class FWInputDevicePad : public FWInputDevice
{
public:
									FWInputDevicePad(void *pPlatformData);
	virtual 						~FWInputDevicePad();

	virtual FWInput::DeviceType		getType() const;
	
	

protected:
	virtual void					update();
};

#endif//__FW_INPUT_H__
