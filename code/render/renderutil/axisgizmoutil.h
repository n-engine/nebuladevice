#pragma once
//------------------------------------------------------------------------------
/**
	@class RenderUtil::AxisGizmoUtil

	Helper class to create and raycheck the axis gizmo.

	(C) 2011 xiongyouyi
*/
#include "core/ptr.h"
#include "io/memorystream.h"


//------------------------------------------------------------------------------
namespace RenderUtil
{
class AxisGizmoUtil
{
public:
	AxisGizmoUtil();
	~AxisGizmoUtil();

	/// get pointer to vertex data
	const void* GetVertexData() const;
	/// get index data
	const void* GetIndexData() const;

	/// get number of primitives
	SizeT GetNumPrimitives() const;
	/// get number of vertices
	SizeT GetNumVertices() const;
	/// get number of indices
	SizeT GetNumIndices() const;
private:
	SizeT numPrimitives;
	SizeT numVertices;
	SizeT numIndices;
};

//------------------------------------------------------------------------------
/**
*/
inline
AxisGizmoUtil::AxisGizmoUtil()
: numPrimitives(32)
, numVertices(18)
, numIndices(96)
{
}

//------------------------------------------------------------------------------
/**
*/
inline
AxisGizmoUtil::~AxisGizmoUtil()
{
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
AxisGizmoUtil::GetNumPrimitives() const
{
	return this->numPrimitives;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
AxisGizmoUtil::GetNumVertices() const
{
	return this->numVertices;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
AxisGizmoUtil::GetNumIndices() const
{
	return this->numIndices;
}

} // namespace RenderUtil
//------------------------------------------------------------------------------