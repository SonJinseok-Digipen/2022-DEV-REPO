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

#include "Vec2.h"
#include "Sprite.h"
#include "TransformMatrix.h"


namespace CS230 {
	class GameObject {
	public:
		GameObject(math::vec2 position);
		GameObject(math::vec2 position, double rotation, math::vec2 scale);
		virtual ~GameObject() {}

		virtual void Update(double dt);
		virtual void Draw(math::TransformMatrix cameraMatrix);

		const math::TransformMatrix& GetMatrix();
		const math::vec2& GetPosition() const;
		const math::vec2& GetVelocity() const;
		const math::vec2& GetScale() const;
		double GetRotation() const;

	protected:
		void SetPosition(math::vec2 newPosition);
		void UpdatePosition(math::vec2 adjustPosition);
		void SetVelocity(math::vec2 newPosition);
		void UpdateVelocity(math::vec2 adjustPosition);
		void SetScale(math::vec2 newScale);
		void SetRotation(double newRotationAmount);
		void UpdateRotation(double newRotationAmount);

		Sprite sprite;

	private:
		math::TransformMatrix objectMatrix;
		bool updateMatrix;

		double rotation;
		math::vec2 scale;
		math::vec2 position;
		math::vec2 velocity;
	};
}
