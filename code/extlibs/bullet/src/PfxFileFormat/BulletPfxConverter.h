

#ifndef BULLET_PFX_CONVERTER_H
#define BULLET_PFX_CONVERTER_H

class btDynamicsWorld;
class btTypedConstraint;

class btRigidBody;
class btCollisionShape;
class btConvexHullShape;
class btCompoundShape;
class btTriangleMesh;
class btTransform;
class btVector3;
class PfxCommonImport;

#include "LinearMath/btScalar.h"
#include "LinearMath/btHashMap.h"




class BulletPfxConverter
{
	btDynamicsWorld* m_dynaWorld;

	btHashMap<btHashString,btRigidBody*> m_bodyNameTable;

	btCollisionShape* createSingleBulletCollisionShape(const PfxCommonImport& importer, const struct PfxRigBodyInfo& rbInfo, int shapeIndex);
	
	btCollisionShape* createBulletCollisionShape(const PfxCommonImport& importer, const struct PfxRigBodyInfo& rbInfo);


	public:
		BulletPfxConverter(btDynamicsWorld* dynaWorld)
			:m_dynaWorld(dynaWorld)
	{
	}
	virtual ~BulletPfxConverter()
	{
	}

	virtual bool load(const char* fileName);

	virtual void save(const char* fileName);



	virtual btRigidBody*  createRigidBody(bool isDynamic, 
		float mass, 
		const btTransform& startTransform,
		btCollisionShape* shape);

	virtual btCollisionShape* createBoxShape(const btVector3& halfExtents);
	virtual btCollisionShape* createSphereShape(btScalar radius);
	virtual btCollisionShape* createCapsuleShapeY(btScalar radius,btScalar height);
	virtual class btConvexHullShape* createConvexHullShape();

	virtual class btTriangleMesh*	createTriangleMeshContainer(bool use32bitIndices);
	virtual	btCollisionShape* createBvhTriangleMeshShape(btTriangleMesh* trimesh);

	virtual class btCompoundShape* createCompoundShape();

};

#endif //BULLET_PFX_CONVERTER_H