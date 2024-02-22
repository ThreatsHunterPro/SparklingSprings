#include "FlameThrower.h"
#include "Macro.h"
#include "Timer.h"

#define PATH_FLAME "GPEs/Flame.png"

FlameThrower::FlameThrower(const ShapeData& _data, const Vector2f& _direction)
						 : Actor(STRING_ID("FlameThrower"), _data)
{
	cooldown = 3.0f;
	range = 300.0f;
	direction = _direction;
	const float _finalRange = direction.x > 0.0f ? range : -range;
	flame = new Flame(ShapeData(Vector2f(_data.position.x + _finalRange / 2.0f, _data.position.y), Vector2f(range, 50.0f), PATH_FLAME));
}


void FlameThrower::Init()
{
	new Timer(this, &FlameThrower::ToogleFlame, seconds(cooldown));
}

void FlameThrower::ToogleFlame()
{
	flame->ToggleStatus();
}