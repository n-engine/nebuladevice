/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 Time class
//
// $File: //nextgendev/Framework_080/include/win32/FWWin32Time.h $
// $Author: asidwell $
// $Date: 2006/02/03 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WIN32TIME_H__
#define __FW_WIN32TIME_H__

#include <windows.h>

class FWTimeVal;

// Time functions.
// Contains static methods for starting, stopping and getting the current time.
class FWTime
{
public:
	static void				init();
	static FWTimeVal		getCurrentTime();
	static void				startTime();
	static void				stopTime();
	static void				update();

	// Zero value time
	static FWTimeVal		sZero;

private:
	// Counter frequency
	static LARGE_INTEGER	sPerfCountFreq;
	// Current time
	static FWTimeVal		sCurrentTime;
	// Counter frequency as double
	static double			sFreq;
	// Is time stopped?
	static bool				sIsStopped;

	// Friend of <c>FWTimeVal</c>
	friend class			FWTimeVal;
};

// Time value class.
// Has methods for converting between the internal representation
// and floating point seconds value, as well as arithmetic functions.
class FWTimeVal
{
public:

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal()
	{
	}

	//-----------------------------------------------------------------------------
	// Description: Copy constructor
	// Parameters:	val - Time value to copy from
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(const FWTimeVal &val)
	{
		mVal.QuadPart = val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	secs - Time value in seconds (float)
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(float secs)
	{
		mVal.QuadPart = (LONGLONG)((double)secs * FWTime::sFreq);
	}

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	secs - Time value in seconds (double)
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(double secs)
	{
		mVal.QuadPart = (LONGLONG)(secs * FWTime::sFreq);
	}

	//-----------------------------------------------------------------------------
	// Description: Destructor
	// Parameters:
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline ~FWTimeVal()
	{
	}

	//-----------------------------------------------------------------------------
	// Description: Add operator
	// Parameters:	val - Time value to add
	// Returns: Added values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator+(const FWTimeVal &val) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = mVal.QuadPart + val.mVal.QuadPart;
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Subtract operator
	// Parameters:	val - Time value to subtract
	// Returns: Subtracted values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator-(const FWTimeVal &val) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = mVal.QuadPart - val.mVal.QuadPart;
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply operator
	// Parameters:	mul - Time value to multiply (float)
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(float mul) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart * (double)mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply operator
	// Parameters:	mul - Time value to multiply (double)
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(double mul) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart * mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Time value to divide by (float)
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(float div) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart / (double)div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Time value to divide by (double)
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(double div) const
	{
		FWTimeVal	ret;

		ret.mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart / div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	val - Time value to divide by
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline double operator/(const FWTimeVal &val) const
	{
		return (double)mVal.QuadPart / (double)val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Assign operator
	// Parameters:	val - Time value to assign
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator=(const FWTimeVal &val)
	{
		mVal.QuadPart = val.mVal.QuadPart;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Add and assign operator
	// Parameters:	val - Time value to add
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator+=(const FWTimeVal &val)
	{
		mVal.QuadPart += val.mVal.QuadPart;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Subtract and assign operator
	// Parameters:	val - Time value to subtract
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator-=(const FWTimeVal &val)
	{
		mVal.QuadPart -= val.mVal.QuadPart;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply and assign operator
	// Parameters:	mul - Time value to multiply by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(float mul)
	{
		mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart * (double)mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply and assign operator
	// Parameters:	mul - Time value to multiply by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(double mul)
	{
		mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart * mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Time value to divide by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(float div)
	{
		mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart / (double)div);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Time value to divide by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(double div)
	{
		mVal.QuadPart = (LONGLONG)((double)mVal.QuadPart / div);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Equality test operator
	// Parameters:	val - Time value to test
	// Returns: True if same, false if different
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator==(const FWTimeVal &val) const
	{
		return mVal.QuadPart == val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Inequality test operator
	// Parameters:	val - Time value to test
	// Returns: True if different, false if same
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator!=(const FWTimeVal &val) const
	{
		return mVal.QuadPart != val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Less-than test operator
	// Parameters:	val - Time value to test
	// Returns: True if less, false if greater or equal
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator<(const FWTimeVal &val) const
	{
		return mVal.QuadPart < val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Greater-than test operator
	// Parameters:	val - Time value to test
	// Returns: True if greater, false if less or equal
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator>(const FWTimeVal &val) const
	{
		return mVal.QuadPart > val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Less-than-or-equal test operator
	// Parameters:	val - Time value to test
	// Returns: True if less or equal, false if greater
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator<=(const FWTimeVal &val) const
	{
		return mVal.QuadPart <= val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Greater-than-or-equal test operator
	// Parameters:	val - Time value to test
	// Returns: True if greater or equal, false if less
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator>=(const FWTimeVal &val) const
	{
		return mVal.QuadPart >= val.mVal.QuadPart;
	}

	//-----------------------------------------------------------------------------
	// Description: Float cast operator
	// Parameters:
	// Returns: Value in seconds as a float
	// Notes: 
	//-----------------------------------------------------------------------------
	inline operator float() const
	{
		return (float)((double)(mVal.QuadPart / FWTime::sFreq));
	}

	//-----------------------------------------------------------------------------
	// Description: Double cast operator
	// Parameters:
	// Returns: Value in seconds as a double
	// Notes: 
	//-----------------------------------------------------------------------------
	inline operator double() const
	{
		return ((double)mVal.QuadPart / FWTime::sFreq);
	}

protected:
	// Actual time value
	LARGE_INTEGER	mVal;

	// Friend of <c>FWTime</c>
	friend class	FWTime;
};

//-----------------------------------------------------------------------------
// Description: Get the current time value
// Parameters:	
// Returns: The current time
// Notes: 
//-----------------------------------------------------------------------------
inline FWTimeVal FWTime::getCurrentTime()
{
	return sCurrentTime;
}
	
//-----------------------------------------------------------------------------
// Description: Starts time running
// Parameters:	
// Returns: 
// Notes: 
//-----------------------------------------------------------------------------
inline void FWTime::startTime()
{
	sIsStopped = false;
}

//-----------------------------------------------------------------------------
// Description: Stops time running
// Parameters:	
// Returns: 
// Notes: 
//-----------------------------------------------------------------------------
inline void FWTime::stopTime()
{
	sIsStopped = true;
}

//-----------------------------------------------------------------------------
// Description: Updates time
// Parameters:	
// Returns: 
// Notes: 
//-----------------------------------------------------------------------------
inline void FWTime::update()
{
	if(!sIsStopped)
		QueryPerformanceCounter(&sCurrentTime.mVal);
}

#endif//__FW_WIN32TIME_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
