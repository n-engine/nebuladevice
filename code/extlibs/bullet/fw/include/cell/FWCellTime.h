/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Cell Time class
//
// $File: //nextgendev/Framework_080/include/cell/FWCellTime.h $
// $Author: asidwell $
// $Date: 2006/02/20 $
// $Revision: #3 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_CELLTIME_H__
#define __FW_CELLTIME_H__

#include <stdint.h>
#include <sys/time_util.h>

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
	static double			sFreq;

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
		mVal = (unsigned long)((double)secs * FWTime::sFreq);
	}

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:	secs - Value in seconds (double)
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal(double secs)
	{
		mVal = (unsigned long)(secs * FWTime::sFreq);
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
	// Parameters:	mul - Value to multiply (float)
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(float mul) const
	{
		FWTimeVal	ret;

		ret.mVal = (unsigned long)((double)mVal * (double)mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply operator
	// Parameters:	mul - Value to multiply (double)
	// Returns: Multiplied values
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator*(double mul) const
	{
		FWTimeVal	ret;

		ret.mVal = (unsigned long)((double)mVal * mul);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Value to divide by (float)
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(float div) const
	{
		FWTimeVal	ret;

		ret.mVal = (unsigned long)((double)mVal / (double)div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	div - Value to divide by (double)
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal operator/(double div) const
	{
		FWTimeVal	ret;

		ret.mVal = (unsigned long)((double)mVal / div);
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide operator
	// Parameters:	val - Value to divide by (FWTimeVal)
	// Returns: Divided value
	// Notes: 
	//-----------------------------------------------------------------------------
	inline double operator/(const FWTimeVal &val) const
	{
		return (double)mVal / (double)val.mVal;
	}

	//-----------------------------------------------------------------------------
	// Description: Assign operator
	// Parameters:	val - Value to assign (FWTimeVal)
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
	// Parameters:	mul - Value to multiply by (float)
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(float mul)
	{
		mVal = (unsigned long)((double)mVal * (double)mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Multiply and assign operator
	// Parameters:	mul - Value to multiply by (double)
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator*=(double mul)
	{
		mVal = (unsigned long)((double)mVal * mul);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Value to divide by (float)
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(float div)
	{
		mVal = (unsigned long)((double)mVal / (double)div);
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Description: Divide and assign operator
	// Parameters:	div - Value to divide by (double)
	// Returns: Reference to this object
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWTimeVal &operator/=(double div)
	{
		mVal = (unsigned long)((double)mVal / div);
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
	// Description: less-than test operator
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
		return (float)((double)mVal / FWTime::sFreq);
	}

	//-----------------------------------------------------------------------------
	// Description: Double cast operator
	// Parameters:
	// Returns: Value in seconds as a double
	// Notes: 
	//-----------------------------------------------------------------------------
	inline operator double() const
	{
		return ((double)mVal / FWTime::sFreq);
	}

protected:
	uint64_t	mVal;

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
		SYS_TIMEBASE_GET(sCurrentTime.mVal);
}

#endif//__FW_CELLTIME_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
