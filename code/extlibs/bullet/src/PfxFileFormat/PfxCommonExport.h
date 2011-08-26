/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_COMMON_EXPORT_H__
#define __PFX_COMMON_EXPORT_H__

#include "PfxCommonFileIO.h"
#include "PfxCommonFormat.h"

///////////////////////////////////////////////////////////////////////////////
// PfxCommonExport

class PfxCommonExport : public PfxCommonFileWriter , public PfxCommonFormat
{
private:
	
	void writePreHeader();
	void writePostHeader();
	
	void writeRigWorld();
	void writeRigBodies();
	void writeRigStates();
	void writeRigJoints();
	void writeRigConvexMeshes();
	void writeRigLargeMeshes();
	void writeRigNonContactPairs();
	
	void writeRigBody(const PfxRigBodyInfo &info);
	void writeRigState(const PfxRigStateInfo &info);
	void writeRigJoint(const PfxRigJointInfo &info);
	void writeRigConvexMesh(const PfxRigConvexMeshInfo &info);
	void writeRigLargeMesh(const PfxRigLargeMeshInfo &info);
	
public:

	PfxBool doExport(const char *filename);
};

#endif /* __PFX_COMMON_EXPORT_H__ */
