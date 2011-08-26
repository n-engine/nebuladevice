/*

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
Callbacks need to be implemented by a user.
These callbacks are called when OpenPhysics needs to get some information from the user data.

void plGetContactPairInfo(void *userContact,void *userObjectA,void *userObjectB,plContactPairInfo *info);
  This function is called to create a contact pair info structure.A user needs to set plContactPairInfo 
  referring to the user objects which are carried as arguments.

void plCollide(void* userObjectA,void* userObjectB,void* userContact,plContactInfo *info);
  This function is called when two shapes are colliding.
  plContactInfo holds contact information. So a user can convert it into the user contact.

void plGetRigidBodyInfo(void *userObject,plBodyInfo *bodyInfo);
  This function is called to create a internal rigid body.A user needs to set plBodyInfo 
  referring to the user object which is carried as an argument.

void plGetConstraintInfo1(void *userConstraint,plConstraintInfo1 *info)
  User need to inform the system about constraint information.
  The number of generic constraints are specified by a user, then allocated.

void plGetConstraintInfo2(void *userConstraint,void *userObjectA,void *userObjectB,plConstraintInfo2 *info)
  In plGetConstraintInfo2, User need to set the details of constraints into each generic constraints.

void plSetDeltaVelocity(void *userObject,plVector3 deltaLinearVelocity,plVector3 deltaAngularVelocity)
  This function is called after solving constraints.
  User need to update their own rigid body's velocity using delta velocity.

void plSetAccumlatedImpulse(void *userConstraint,plReal *accumlatedImpulse,plInt strideInBytes)
  This function is called after solving constraints.
  An accumlatedImpulse is an array of float values which numbers are specified in plGetConstraintInfo1.
 */

#ifndef OPEN_PL_LOW_LEVEL_PHYSICS_C_API_H
#define OPEN_PL_LOW_LEVEL_PHYSICS_C_API_H

#define PL_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

#ifdef PL_USE_DOUBLE_PRECISION
typedef double	plReal;
#else
typedef float	plReal;
#endif

/** platform specific definitions */
typedef plReal			plVector3[3];
typedef plReal			plQuaternion[4];
typedef long			plInt32;
typedef short			plInt16;
typedef char			plInt8;
typedef unsigned long	plUInt32;
typedef unsigned short	plUInt16;
typedef unsigned char	plUInt8;
typedef int				plInt;
typedef int				plEnum;

/** enums for types of broadphases */
#define	PL_DEFAULT_BROADPHASE				0
#define	PL_SWEEP_AND_PRUNE_BROADPHASE		1
#define	PL_AABB_TREE_BROADPHASE				2
#define	PL_UNIFORM_GRID_BROADPHASE			3

/** enums for types of narrowphase */
#define	PL_DEFAULT_NARROWPHASE				0

/** enums for types of constraint solver */
#define	PL_DEFAULT_CONSTRAINT_SOLVER		0

/** enums for unique Id type */
#define PL_SHORT							1
#define	PL_INT								2

#ifdef __cplusplus
extern "C" { 
#endif


/** Broadphase Scene/Proxy Handles (C-API)*/
	PL_DECLARE_HANDLE(plBroadphaseHandle);
	PL_DECLARE_HANDLE(plBroadphaseProxyHandle);

/** Narrowphase Handles (C-API)*/
	PL_DECLARE_HANDLE(plNarrowphaseHandle);

/** Constraint for Rigid Bodies (C-API)*/
	PL_DECLARE_HANDLE(plConstraintSolverHandle);
	PL_DECLARE_HANDLE(plConstraintHandle);
	PL_DECLARE_HANDLE(plSolverBodyHandle);

/** Triangle Mesh interface (C-API)*/
	PL_DECLARE_HANDLE(plMeshInterfaceHandle);

/** Collision Shape/Geometry, property of a Rigid Body (C-API)*/
	PL_DECLARE_HANDLE(plShapeHandle);

	struct plPairInfo
	{
		plInt	m_numPairs;
		void*	m_allPairs;
		plInt	m_pairStriding;
		plInt	m_uniqueIdType;
		union {
			plUInt32*	m_uniqueId0;
			plUInt16*	m_uniqueIdShort0;
		};
		union {
			plUInt32*	m_uniqueId1;
			plUInt16*	m_uniqueIdShort1;
		};
		plInt	m_ObjectType;
		void**	m_ObjectPtr0;
		void**	m_ObjectPtr1;
		void**	m_userPointer;
	};

/**
	Low Level Broadphase collision detection API
*/

	typedef void(*plBroadphaseCallback)(void* clientData, void* userObjectA,void* userObjectB,void* userPointer);

	extern plBroadphaseHandle	plCreateBroadphase(plEnum broadphaseType,void* clientData, plBroadphaseCallback beginCallback,plBroadphaseCallback endCallback,void* platformSpecificParam=0);

	extern void	plReleaseBroadphase(plBroadphaseHandle bp);

	extern 	plBroadphaseProxyHandle plCreateProxy(plBroadphaseHandle bp, void* userObject, plInt guid, const plVector3 minAabb, const plVector3 maxAabb);

	extern void plReleaseProxy(plBroadphaseHandle bp, plBroadphaseProxyHandle proxyHandle);

	extern void plSetBoundingBox(plBroadphaseHandle bp, plBroadphaseProxyHandle proxyHandle, const plVector3 minAabb, const plVector3 maxAabb);

	extern void plFindPairs(plBroadphaseHandle broadphaseHandle,plPairInfo* pairInfo);

/**
	Low Level Narrowphase collision detection API
*/

	enum plShapeType {
		PLSHAPE_SPHERE,		
		PLSHAPE_BOX,		
		PLSHAPE_CAPSULE,	
		PLSHAPE_CONE,		// PE not supported
		PLSHAPE_CYLINDER,	// PE not supported
		PLSHAPE_COMPOUND,	
		PLSHAPE_CONVEXMESH,	
		PLSHAPE_TRIANGLES,	
	};

	struct plShapeInfo
	{
		plShapeType m_type;
		plVector3 m_offsetPosition;
		plQuaternion m_offsetOrientation;
		
		// Shape description
		union {
			struct {
				plReal radius;
			} m_sphereParam;

			struct {
				plReal halfExtentX;
				plReal halfExtentY;
				plReal halfExtentZ;
			} m_boxParam;

			struct {
				plInt  direction;	// 0,1,2 = X,Y,Z
				plReal radius;		
				plReal halfLength;	
			} m_capsuleParam;
			
			struct {
				// plConvexMeshHandle m_hConvexMesh;
			} m_convexParam;

			struct {
				// plTrianglesMeshHandle m_hTrianglesMesh;
			} m_trianglesParam;
		};
	};

	struct plContactPairInfo
	{
		plShapeHandle shapeA;
		plShapeHandle shapeB;
		plReal *positionA;
		plReal *positionB;
		plReal *orientationA;
		plReal *orientationB;
	};

	struct plContactInfo
	{
		plInt m_strideInBytes;
		plInt m_numContacts;
		plReal *m_localPointA;	// vector
		plReal *m_localPointB;	// vector
		plReal *m_normal;		// vector
		plReal *m_distance;		// scalar
	};

	extern plNarrowphaseHandle plCreateNarrowphase(plEnum narrowphaseType,void* clientData, void* platformSpecificParam=0);

	extern void	plReleaseNarrowphase(plNarrowphaseHandle np);

	extern void plFindContacts(plNarrowphaseHandle np);

	extern void plCreateContactPair(plNarrowphaseHandle np,void *userObjectA,void *userObjectB,void *userContact);
	
	extern void plReleaseAllContactPairs(plNarrowphaseHandle np);

	//J システムに衝突判定のための情報を与える
	extern void plGetContactPairInfo(void *userContact,void *userObjectA,void *userObjectB,plContactPairInfo *info); // (User callback)

	//J システムから返された衝突点情報をユーザーデータに変換
	extern void plCollide(void* userObjectA,void* userObjectB,void* userContact,plContactInfo *info); // (User callback)

/* Collision Shape definition */
	extern	plShapeHandle plCreateShape(plNarrowphaseHandle np);

	//E PE limitation : It returns false if you add more than 5 shapes.
	extern	bool plAddShape(plNarrowphaseHandle np,plShapeHandle shape,const plShapeInfo *info);

	extern  void plFinishShape(plNarrowphaseHandle np,plShapeHandle shape); // Also release child shapes

	extern  void plReleaseShape(plNarrowphaseHandle np,plShapeHandle shape); // Also release child shapes

	//E PE doesn't support
	extern  void plSetScaling(plNarrowphaseHandle np,plShapeHandle shape, plVector3 scaling);

	/* Convex Meshes */
	//extern  plShapeHandle plCreateConvexHullShape();
	//extern  void plAddVertex(plShapeHandle convexHull, plReal x,plReal y,plReal z);

	/* Concave static triangle meshes */
	//extern  plMeshInterfaceHandle plCreateMeshInterface();
	//extern  void plAddTriangle(plMeshInterfaceHandle meshHandle, plVector3 v0,plVector3 v1,plVector3 v2);
	//extern  plShapeHandle plCreateStaticTriangleMeshShape(plMeshInterfaceHandle);

/**
	Low Level Constraint Solver API
*/
	struct plBodyInfo {
//		plUInt32 *uniqueId;			// scalar
		plReal *position;			// vector
		plReal *orientation;		// quaternion
		plReal *linearVelocity;		// vector
		plReal *angularVelocity;	// vector
		plReal *restitution;		// scalar
		plReal *friction;			// scalar
		plReal *invMass;			// scalar
		plReal *invInertiaCol0;		// vector
		plReal *invInertiaCol1;		// vector
		plReal *invInertiaCol2;		// vector
	};
	
	struct plConstraintInfo1 {
		plInt numConstraintRows;
		plSolverBodyHandle bodyA;
		plSolverBodyHandle bodyB;
		void *userObjectA;
		void *userObjectB;
		plUInt32 uniqueIdA;
		plUInt32 uniqueIdB;
		bool isStaticA;
		bool isStaticB;
	};
	
	struct plConstraintInfo2 {
		plInt  strideInBytes;
		plEnum *type; // linear or angular
		plReal fps;
		plReal erp;
		plReal *cfm;					// scalar
		plReal *constraintError;		// scalar
		plReal *lowerLimit;				// scalar
		plReal *upperLimit;				// scalar
		plReal *accumlatedImpulse;		// scalar
		plReal *jacobianLinearAxisA;	// vector
		plReal *jacobianAngularAxisA;	// vector
		plReal *jacobianLinearAxisB;	// vector
		plReal *jacobianAngularAxisB;	// vector
	};

	/* Constraint Solver */
	extern plConstraintSolverHandle	plCreateConstraintSolver(plEnum constraintSolverType,plInt iteration,plReal timeStep,void* platformSpecificParam=0);
	extern void	plReleaseConstraintSolver(plConstraintSolverHandle cs);

	/* Solver Body */
	extern plSolverBodyHandle plCreateSolverBody(plConstraintSolverHandle cs,void* userObject);
	extern void plReleaseSolverBody(plConstraintSolverHandle cs,plSolverBodyHandle body);
	extern void plGetRigidBodyInfo(void *userObject,plBodyInfo *bodyInfo); // (User callback)
	extern void plSetDeltaVelocity(void *userObject,plVector3 deltaLinearVelocity,plVector3 deltaAngularVelocity); // Called after solver (User callback)
	
	/* Solver Constraint */
	extern plConstraintHandle plCreateConstraint(plConstraintSolverHandle cs,void *userConstraint);
	//extern void plReleaseConstraint(plConstraintSolverHandle cs,plConstraintHandle constraint); // Todo
	extern void plReleaseAllConstraints(plConstraintSolverHandle cs);
	extern void plGetConstraintInfo1(void *userConstraint,plConstraintInfo1 *info); // (User callback)
	extern void plGetConstraintInfo2(void *userConstraint,void *userObjectA,void *userObjectB,plConstraintInfo2 *info); // (User callback)
	extern void plSetAccumlatedImpulse(void *userConstraint,plReal *accumlatedImpulse,plInt strideInBytes); // Called after solver (User callback)
	
	/* Solver Main */
	extern void plSolveConstraints(plConstraintSolverHandle cs);

/**
	Set/Get parameter
*/
	enum plConfig {
		// Global
		PLCONFIG_ENABLE_SPU,
		PLCONFIG_NUM_SPU,
		PLCONFIG_MAX_UNIQUEID,	// Use for parallelization

		// BROADPHASE

		// NARROWPHASE
		PLCONFIG_USER_CONTACT_BYTES,

		// CONSTRAINT SOLVER
		PLCONFIG_USER_OBJECT_BYTES,
		PLCONFIG_USER_CONSTRAINT_BYTES,
		PLCONFIG_SOLVER_ITERATION,
	};

	extern void	plSetBroadphaseConfigPtr(plBroadphaseHandle bp,plConfig type,void *param);
	extern void	plSetBroadphaseConfigInt(plBroadphaseHandle bp,plConfig type,plInt param);
	extern void	plSetBroadphaseConfigFloat(plBroadphaseHandle bp,plConfig type,plReal param);

	extern void	plSetNarrowphaseConfigPtr(plNarrowphaseHandle np,plConfig type,void *param);
	extern void	plSetNarrowphaseConfigInt(plNarrowphaseHandle np,plConfig type,plInt param);
	extern void	plSetNarrowphaseConfigFloat(plNarrowphaseHandle np,plConfig type,plReal param);

	extern void	plSetConstraintSolverConfigPtr(plConstraintSolverHandle cs,plConfig type,void* param);
	extern void	plSetConstraintSolverConfigInt(plConstraintSolverHandle cs,plConfig type,plInt param);
	extern void	plSetConstraintSolverConfigFloat(plConstraintSolverHandle cs,plConfig type,plReal param);
#ifdef __cplusplus
}
#endif

#endif //OPEN_PL_LOW_LEVEL_PHYSICS_C_API_H

