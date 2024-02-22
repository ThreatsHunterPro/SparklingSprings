#pragma once
#include "IInteractable.h"
#include "Item.h"

struct ResourceData
{
	string path;
	ItemType type;
	RarityType rarity;
	int gatheringAmount;
	float gatheringDuration;
	float gatheringPrecision;

	ResourceData()
	{
		path = "";
		type = ITEM_NONE;
		rarity = RARITY_COMMON;
		gatheringAmount = 1;
		gatheringDuration = 0.5f;
		gatheringPrecision = 0.1f;
	}
	ResourceData(const string& _path, const ItemType& _type, const RarityType& _rarity,
				 const int _gatheringAmount, const float _gatheringDuration,
				 const float _gatheringPrecision)
	{
		path = _path;
		type = _type;
		rarity = _rarity;
		gatheringAmount = _gatheringAmount;
		gatheringDuration = _gatheringDuration;
		gatheringPrecision = _gatheringPrecision;
	}
};

class Resource : public Actor, public IInteractable
{
	ResourceData data;

public:
	ResourceData GetData() const
	{
		return data;
	}

public:
	Resource(const string& _name, const ShapeData& _shapeData, const ResourceData& _data,
			 const function<void()>& _callback);
};