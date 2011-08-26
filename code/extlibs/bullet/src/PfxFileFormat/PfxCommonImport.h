/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_COMMON_IMPORT_H__
#define __PFX_COMMON_IMPORT_H__

#include "PfxCommonFileIO.h"
#include "PfxCommonFormat.h"

///////////////////////////////////////////////////////////////////////////////
// PfxCommonImport

class PfxCommonImport : public PfxCommonFileReader , public PfxCommonFormat
{
private:
	void readRigidBodies();
	
	void readRigBodies();
	void readRigStates();
	void readRigJoints();
	void readRigConvexMeshes();
	void readRigLargeMeshes();
	void readRigNonContactPairs();
	
	PfxBool readRigWorld(PfxRigWorldInfo &world);
	PfxBool readRigBody(PfxRigBodyInfo &body);
	PfxBool readRigShape(PfxRigShapeInfo &shape);
	PfxBool readRigState(PfxRigStateInfo &state);
	PfxBool readRigJoint(PfxRigJointInfo &joint);
	PfxBool readRigConvexMesh(PfxRigConvexMeshInfo &convexmesh);
	PfxBool readRigLargeMesh(PfxRigLargeMeshInfo &largemesh);
	PfxBool readPair(PfxRigNonContactPairInfo &pair);
	
	void readVerts(vector<PfxFloat> &verts);
	void readIndices(vector<PfxUInt16> &indices);
	
public:
	
	PfxBool doImport(const char *filename);
};

#endif /* __PFX_COMMON_IMPORT_H__ */
