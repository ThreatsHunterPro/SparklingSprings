#pragma once
#include "Component.h"
#include "Resource.h"
#include "Inventory.h"
#include "ProgressBar.h"
#include "Timer.h"

class GatherComponent : public Component
{
	Vector2f barOffset;
	ProgressBar* bar;

	int progress;
	float factor;
	Resource* resource;
	Inventory* inventory;
	Timer* timer;

public:
	void SetProgressBar(ProgressBar* _bar)
	{
		bar = _bar;
		Reset();
	}
private:
	void Reset()
	{
		progress = 0;
		factor = 0.0f;
		resource = nullptr;
		inventory = nullptr;

		if (bar)
		{
			bar->SetValue(0.0f);
			//bar->SetVisible(false);
		}
	}
	bool IsGathering() const
	{
		return resource;
	}

public:
	GatherComponent(Actor* _owner);

public:
	virtual void Update(const float _deltaTime) override;
	void Gather(Resource* _resource);
};