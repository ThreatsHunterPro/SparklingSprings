#include "GatherComponent.h"
#include "Player.h"

GatherComponent::GatherComponent(Actor* _owner) : Component(_owner)
{
	barOffset = Vector2f(0.0f, -100.0f);
	bar = nullptr;

	Reset();
}


void GatherComponent::Update(const float _deltaTime)
{
	const Vector2f& _position = owner->GetShapePosition() + barOffset;
	bar->SetShapePosition(_position);
}

void GatherComponent::Gather(Resource* _resource)
{
	if (IsGathering()) return;

	resource = _resource;
	if (Player* _player = dynamic_cast<Player*>(owner))
	{
		inventory = _player->GetInventory();
	}

	// 100% = durMax
	const ResourceData& _data = resource->GetData();
	const float _durationMax = _data.gatheringDuration;

	if (bar)
	{
		const float _precision = _data.gatheringPrecision;

		// durMin = durMax * precision
		const float _durationMin = _durationMax * _precision;

		// factor = durMin * 100 / durMax
		factor = _durationMin * 100.0f / _durationMax;

		timer = new Timer([&]() {
			const ResourceData& _data = resource->GetData();
			
			if (bar->GetCurrentValue() >= _data.gatheringAmount * progress)
			{
				progress++;

				inventory->AddItem(1, _data.path, _data.type, _data.rarity);

				if (progress >= _data.gatheringAmount)
				{
					Reset();
					timer->Stop();
					return;
				}
			}
			
			bar->ChangeValue(factor);
			cout << bar->GetCurrentValue() << endl;
		},
		seconds(_durationMin), true, true);
	}
}