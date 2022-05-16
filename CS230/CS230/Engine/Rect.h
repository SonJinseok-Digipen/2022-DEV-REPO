#pragma once
#include"Vec2.h"
namespace math
{
	struct rect2
	{
		math::vec2 BottomLeft;
		math::vec2 TopRight;
	};

	struct irect2
	{
		math::ivec2 BottomLeft;
		math::ivec2 TopRight;
	};
}
