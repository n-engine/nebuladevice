/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux Time class
//
// $File: //nextgendev/Framework_080/include/linux/FWLinuxTime.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_LINUXTIME_H__
#define __FW_LINUXTIME_H__

#include <sys/time.h>
#include <unistd.h>

#define _MICROSECS	1000000.0

class FWTimeVal;

class FWTime
{
public:
	static void				init();
	static FWTimeVal		getCurrentTime();
	static void				startTime();
	static void				stopTime();
	static void				update();
	static FWTimeVal		sZero;

private:
	static FWTimeVal		sStoppedTime;
	static FWTimeVal		sCurrentTime;
	static bool				sIsStopped;

	friend class			FWTimeVal;
};

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
	// Parameters:	val - Value to copy from
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(const FWTimeVal &val)
	{
		mVal = val.mVal;
	}


	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	secs - Value in seconds (float)
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(float secs)
	{
		mVal = (long long int)((double)secs * _MICROSECS);
	}

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	secs - Value in seconds (double)
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(double secs)
	{
		mVal = (long long int)(secs * _MICROSECS);
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
	// Parameters:	val - Value to add
	// Returns: Added values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator+(const FWTimeVal &val) const
	{
		FWTimeVal	ret;

		ret.mVal = mVal + val.mVal;
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Subtract operator
	// Parameters:	val - Value to subtract
	// Returns: Subtracted values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator-(const FWTimeVal &val) const
	{
		FWTimeVal	ret;

		ret.mVal = mVal - val.mVal;
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply operator
	// Parameters:	mul - Value to multiply
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(float mul) const
	{
		FWTimeVal	ret;

		ret.mVal = (long long int)((double)mVal * (double)mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply operator
	// Parameters:	mul - Value to multiply
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(double mul) const
	{
		FWTimeVal	ret;

		ret.mVal = (long long int)((double)mVal * mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Value to divide by
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(float div) const
	{
		FWTimeVal	ret;

		ret.mVal = (long long int)((double)mVal / (double)div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Value to divide by
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(double div) const
	{
		FWTimeVal	ret;

		ret.mVal = (long long int)((double)mVal / div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	val - Value to divide by
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline double operator/(const FWTimeVal &val) const
	{
		return (double)mVal / (double)val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Assign operator
	// Parameters:	val - Value to assign
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator=(const FWTimeVal &val)
	{
		mVal = val.mVal;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Add and assign operator
	// Parameters:	val - Value to add
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator+=(const FWTimeVal &val)
	{
		mVal += val.mVal;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Subtract and assign operator
	// Parameters:	val - Value to subtract
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator-=(const FWTimeVal &val)
	{
		mVal -= val.mVal;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply and assign operator
	// Parameters:	mul - Value to multiply by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(float mul)
	{
		mVal = (long long int)((double)mVal * (double)mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply and assign operator
	// Parameters:	mul - Value to multiply by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(double mul)
	{
		mVal = (long long int)((double)mVal * mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Value to divide by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(float div)
	{
		mVal = (long long int)((double)mVal / (double)div);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Value to divide by
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(double div)
	{
		mVal = (long long int)((double)mVal / div);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Equality test operator
	// Parameters:	val - Value to test
	// Returns: True if same, false if different
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator==(const FWTimeVal &val) const
	{
		return mVal == val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Inequality test operator
	// Parameters:	val - Value to test
	// Returns: True if different, false if same
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator!=(const FWTimeVal &val) const
	{
		return mVal != val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Less-than test operator
	// Parameters:	val - Value to test
	// Returns: True if less, false if greater or equal
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator<(const FWTimeVal &val) const
	{
		return mVal < val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Greater-than test operator
	// Parameters:	val - Value to test
	// Returns: True if greater, false if less or equal
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator>(const FWTimeVal &val) const
	{
		return mVal > val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Less-than-or-equal test operator
	// Parameters:	val - Value to test
	// Returns: True if less or equal, false if greater
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator<=(const FWTimeVal &val) const
	{
		return mVal <= val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Greater-than-or-equal test operator
	// Parameters:	val - Value to test
	// Returns: True if greater or equal, false if less
	// Notes: 
	//-----------------------------------------------------------------------------
	inline bool operator>=(const FWTimeVal &val) const
	{
		return mVal >= val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Float cast operator
	// Parameters:
	// Returns: Value in seconds as a float
	// Notes: 
	//-----------------------------------------------------------------------------
	inline operator float() const
	{
		return (float)((double)(mVal / _MICROSECS));
	}

	//-----------------------------------------------------------------------------
	// Description: Double cast operator
	// Parameters:
	// Returns: Value in seconds as a double
	// Notes: 
	//-----------------------------------------------------------------------------
	inline operator double() const
	{
		return ((double)mVal / _MICROSECS);
	}

protected:
	long long int	mVal;

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
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		sCurrentTime.mVal = ((long long int)tv.tv_sec) * ((long long int)_MICROSECS) + ((long long int)tv.tv_usec);
	}
}

#endif//_FWLINUXTIME_H_

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
