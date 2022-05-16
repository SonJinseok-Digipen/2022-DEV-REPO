#include"Camera.h"
CS230::Camera::Camera(math::rect2 movableRange) :movableRange(movableRange) {}
void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
	if (followObjPos.x >= movableRange.TopRight.x)
	{
		position.x = followObjPos.x - movableRange.TopRight.x;
	}
	
	if (followObjPos.x <= movableRange.BottomLeft.x)
	{
		position.x = followObjPos.x - movableRange.BottomLeft.x;
	}

	if (position.x < extent.BottomLeft.x)
	{
		position.x = extent.BottomLeft.x;
	}

	if (position.x > extent.TopRight.x)
	{
		position.x = extent.TopRight.x;
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position);
}