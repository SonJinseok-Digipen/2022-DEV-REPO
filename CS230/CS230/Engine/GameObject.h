#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once

namespace math { class TransformMatrix; }

namespace CS230 {
	class GameObject
	{
	public:
		virtual ~GameObject() {}
		virtual void Update(double dt) = 0;
		virtual void Draw(math::TransformMatrix cameraMatrix) = 0;
	};
}