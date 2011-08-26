//------------------------------------------------------------------------------
//  /mousegripperproperty.cc
//  (C) 2005 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "properties/mousegripperproperty.h"
#include "game/entity.h"
#include "physics/physicsserver.h"
#include "physics/level.h"
#include "core/factory.h"
#include "input/inputserver.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "managers/focusmanager.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "graphics/graphicsserver.h"
#include "graphics/view.h"
#include "managers/envquerymanager.h"
#include "debugrender/debugshaperenderer.h"
#include "debugrender/debugtextrenderer.h"

namespace PhysicsFeature
{
__ImplementClass(PhysicsFeature::MouseGripperProperty, 'MGRP', GraphicsFeature::InputProperty);

using namespace Input;
using namespace Game;
using namespace Math;
using namespace Debug;
using namespace Util;
using namespace BaseGameFeature;
using namespace GraphicsFeature;


//------------------------------------------------------------------------------
/**
*/
MouseGripperProperty::MouseGripperProperty()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
MouseGripperProperty::~MouseGripperProperty()
{
    //n_assert(!this->physicsGripper.isvalid());
}

//------------------------------------------------------------------------------
/** 
    Called when property is attached to a game entity. This will create and setup
    the required physics entities.
*/
void
MouseGripperProperty::OnActivate()
{
    InputProperty::OnActivate();

    //this->physicsGripper = Physics::MouseGripper::Create();
    //this->physicsGripper->SetMaxDistance(1000.0f);
    //this->physicsGripper->SetMaxForce(10000.0f);
}

//------------------------------------------------------------------------------
/** 
    Called when property is going to be removed from its game entity.
    This will release the physics entity owned by the game entity.
*/
void
MouseGripperProperty::OnDeactivate()
{
    //this->physicsGripper = 0;
    InputProperty::OnDeactivate();
}

//------------------------------------------------------------------------------
/**
*/
void
MouseGripperProperty::SetupCallbacks()
{
    this->entity->RegisterPropertyCallback(this, BeginFrame);
    this->entity->RegisterPropertyCallback(this, MoveBefore);
    this->entity->RegisterPropertyCallback(this, MoveAfter);    
    this->entity->RegisterPropertyCallback(this, RenderDebug); 
}

//------------------------------------------------------------------------------
/**
*/
void
MouseGripperProperty::SetupDefaultAttributes()
{
    InputProperty::SetupDefaultAttributes();    
}

//------------------------------------------------------------------------------
/**
    Handle general input.
*/
void
MouseGripperProperty::OnBeginFrame()
{
    if (InputServer::HasInstance())
    {
        //InputServer* inputServer = InputServer::Instance();        
        //float2 mousePos = inputServer->GetDefaultMouse()->GetScreenPosition();
        //float length = physicsGripper->GetMaxDistance();
        //line worldRay = EnvQueryManager::Instance()->ComputeMouseWorldRay(mousePos, length, GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultView());
        //this->physicsGripper->SetWorldMouseRay(worldRay);

        //this->physicsGripper->OnFrameBefore();

        //// only do something if we have the input focus
        //if (FocusManager::Instance()->GetInputFocusEntity() == this->entity)
        //{
        //    InputServer* inputServer = InputServer::Instance();        
        //    if (inputServer->GetDefaultMouse()->ButtonDown(MouseButton::LeftButton))
        //    {
        //        this->HandleLeftMouseBtnDown();
        //    }
        //    else if (inputServer->GetDefaultMouse()->ButtonUp(MouseButton::LeftButton))
        //    {
        //        this->HandleLeftMouseBtnUp();
        //    }
        //}
    }
}

//------------------------------------------------------------------------------
/** 
*/
void 
MouseGripperProperty::OnRenderDebug()
{
    // only do something if we have the input focus
    if (FocusManager::Instance()->GetInputFocusEntity() == this->entity)
    {
		switch (FocusManager::Instance()->GetInputFocusType())
		{
		case FocusManager::Select:
			DrawSelectGripper();
			break;

		case FocusManager::Move:
			DrawMoveGripper();
			break;

		case FocusManager::Rotate:
		case FocusManager::Scale:
		default:
			break;
		}
    }
}

//------------------------------------------------------------------------------
/** 
*/
void
MouseGripperProperty::OnMoveBefore()
{
    //this->physicsGripper->OnStepBefore();    
}

//------------------------------------------------------------------------------
/** 
*/
void
MouseGripperProperty::OnMoveAfter()
{
    //this->physicsGripper->OnStepAfter();
    //this->physicsGripper->OnFrameAfter();
}

//------------------------------------------------------------------------------
/** 
*/
void
MouseGripperProperty::HandleLeftMouseBtnDown()
{
    //if (this->physicsGripper->IsGripOpen())
    //{
    //    this->physicsGripper->CloseGrip();
    //}
}

//------------------------------------------------------------------------------
/** 
*/
void
MouseGripperProperty::HandleLeftMouseBtnUp()
{
    //if (!this->physicsGripper->IsGripOpen())
    //{
    //    this->physicsGripper->OpenGrip();
    //}
}

//------------------------------------------------------------------------------
/** 
	draw select gripper
*/
void
MouseGripperProperty::DrawSelectGripper()
{
	matrix44 transform = this->GetEntity()->GetMatrix44(Attr::Transform);

	// x axis
	Array<point> lineList;
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(3.0f, 0.0f, 0.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(1.0, 0.0, 0.0, 1.0));

	point pt = matrix44::transform(point(3.2, 0.0, 0.0), transform);
	DebugTextRenderer::Instance()->DrawText3D("X", float4(1.0, 0.0, 0.0, 1.0), pt);

	// y axis
	lineList.Clear();
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(0.0f, 3.0f, 0.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(0.0, 1.0, 0.0, 1.0));

	pt = matrix44::transform(point(0.0, 3.2, 0.0), transform);
	DebugTextRenderer::Instance()->DrawText3D("Y", float4(0.0, 1.0, 0.0, 1.0), pt);

	// z axis
	lineList.Clear();
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(0.0f, 0.0f, 3.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(0.0, 0.0, 1.0, 1.0));

	pt = matrix44::transform(point(0.0, 0.0, 3.2), transform);
	DebugTextRenderer::Instance()->DrawText3D("Z", float4(0.0, 0.0, 1.0, 1.0), pt);
}

//------------------------------------------------------------------------------
/** 
	draw move gripper
*/
void 
MouseGripperProperty::DrawMoveGripper()
{
	matrix44 transform = this->GetEntity()->GetMatrix44(Attr::Transform);

	// x axis
	Array<point> lineList;
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(3.0f, 0.0f, 0.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(1.0, 0.0, 0.0, 1.0));

	matrix44 modelTransform = matrix44::multiply(transform, matrix44::translation(float4(3.0, 0.0, 0.0, 1.0)));
	DebugShapeRenderer::Instance()->DrawCone(modelTransform, float4(1.0, 0.0, 0.0, 1.0));

	// y axis
	lineList.Clear();
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(0.0f, 3.0f, 0.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(0.0, 1.0, 0.0, 1.0));

	modelTransform = matrix44::multiply(matrix44::translation(float4(3.0, 0.0, 0.0, 1.0)),
		matrix44::rotationz(n_deg2rad(90.0f)));
	modelTransform = matrix44::multiply(modelTransform, transform);
	DebugShapeRenderer::Instance()->DrawCone(modelTransform, float4(0.0, 1.0, 0.0, 1.0));

	// z axis
	lineList.Clear();
	lineList.Append(point(0.0f, 0.0f, 0.0f));
	lineList.Append(point(0.0f, 0.0f, 3.0));

	DebugShapeRenderer::Instance()->DrawPrimitives(transform, 
		CoreGraphics::PrimitiveTopology::LineList,
		1, &(lineList.Front()), 4, float4(0.0, 0.0, 1.0, 1.0));

	modelTransform = matrix44::multiply(matrix44::translation(float4(3.0, 0.0, 0.0, 1.0)),
		matrix44::rotationy(n_deg2rad(-90.0f)));
	modelTransform = matrix44::multiply(modelTransform, transform);
	DebugShapeRenderer::Instance()->DrawCone(modelTransform, float4(0.0, 0.0, 1.0, 1.0));
}

}; // namespace Properties
