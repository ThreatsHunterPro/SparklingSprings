#pragma once
#include "Actor.h"

class Arrow : public Actor
{
	float moveSpeed;
	Vector2f direction;
	float damages;
	float lifeSpan;

public:
	Arrow(const ShapeData& _data, const Vector2f& _direction);

private:
	void Init();
	virtual void Update(const float _deltaTime) override;
	void Move(const float _deltaTime);
	void CheckCollision();
};