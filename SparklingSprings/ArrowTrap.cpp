#include "ArrowTrap.h"
#include "Macro.h"
#include "Timer.h"
#include "Arrow.h"

#define PATH_ARROW "GPEs/Arrow.png"

ArrowTrap::ArrowTrap(const ShapeData& _data, const Vector2f& _direction)
					: Actor(STRING_ID("ArrowTrap"), _data)
{
	spawnRate = 2.0f;
	offset = Vector2f(100.0f, 0.0f);
	direction = _direction;
	const Vector2f& _finalOffset = direction.x > 0.0f ? offset : -offset;
	arrowData = ShapeData(GetShapePosition() + _finalOffset, Vector2f(100.0f, 50.0f), PATH_ARROW);

	Init();
}

void ArrowTrap::Init()
{
	new Timer(this, &ArrowTrap::SpawnArrow, seconds(spawnRate), true, true);
}

void ArrowTrap::SpawnArrow()
{
	new Arrow(arrowData, direction);
}