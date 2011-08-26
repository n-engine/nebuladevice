/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

/*
	Collision Func Table
				FIX			ACTIVE		ACTIVE(S)	KEYFRAME	KEYFRAME(S)	ONEWAY		ONEWAY(S)	TRIGGER
	FIX			No			Yes			No			No			No			Yes			Yes			Yes
	ACTIVE		Yes			Yes			Yes			Yes			Yes			Yes			Yes			Yes
	ACTIVE(S)	No			Yes			No			Yes			No			Yes			No			Yes
	KEYFRAME	No			Yes			Yes			No			No			Yes			Yes			Yes
	KEYFRAME(S)	No			Yes			No			No			No			Yes			No			Yes
	ONEWAY		Yes			Yes			Yes			Yes			Yes			Yes			Yes			Yes
	ONEWAY(S)	No			Yes			No			Yes			No			Yes			No			Yes
	TRIGGER		Yes			Yes			Yes			Yes			Yes			Yes			Yes			No
*/

static bool collidableTable[MoveTypeCount][MoveTypeCount] = {
	{false,	true,	false,	false,	false,	true,	true,	true },
	{true,	true,	true,	true,	true,	true,	true,	true },
	{false,	true,	false,	true,	false,	true,	false,	true },
	{false,	true,	true,	false,	false,	true,	true,	true },
	{false,	true,	false,	false,	false,	true,	false,	true },
	{true,	true,	true,	true,	true,	true,	true,	true },
	{false,	true,	false,	true,	false,	true,	false,	true },
	{true,	true,	true,	true,	true,	true,	true,	false},
};
