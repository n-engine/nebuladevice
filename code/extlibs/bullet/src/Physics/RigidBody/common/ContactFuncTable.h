/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CONTACT_FUNC_TABLE_H__
#define __CONTACT_FUNC_TABLE_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/RigidBody/common/CollObject.h"
#include "Physics/RigidBody/common/Contact.h"

typedef int (*PrimContacts)(
				ContactPoint *cp,
				const CollPrim & primA,const Transform3 &primTransformA,const Transform3 &relTransformA,int primIndexA,
				const CollPrim & primB,const Transform3 &primTransformB,const Transform3 &relTransformB,int primIndexB,
				float objsInContactDist);

extern PrimContacts funcTbl_primContacts[PRIM_COUNT][PRIM_COUNT];

#endif /* __CONTACT_FUNC_TABLE_H__ */
