#pragma once
#include <map>
#include <vector>

using namespace std;

template <typename Key, typename Value>
class IManager
{
	Value* current;

protected:
	bool needToDelete;
	map<Key, Value*> allValues;
	vector<Value*> unregisteredValues;

public:
	IManager(const bool _needToDelete = true)
	{
		needToDelete = _needToDelete;
		current = nullptr;
		allValues = map<Key, Value*>();
		unregisteredValues = vector<Value*>();
	}
	~IManager()
	{
		if (!needToDelete) return;

		for (auto _pair : allValues)
		{
			delete _pair.second;
		}

		for (Value* _value : unregisteredValues)
		{
			delete _value;
		}
	}

public:
	void Add(const Key& _key, Value* _value)
	{
		if (Exist(_value))
		{
			unregisteredValues.push_back(_value);
			return;
		}
		allValues[_key] = _value;
		_value->SetID(_key);
		current = _value;
	}

	void Remove(Value* _value)
	{
		if (!Exist(_value)) return;
		_value->SetToRemove(true);
	}
	void Remove(const Key& _key)
	{
		if (!Exist(_key)) return;
		allValues[_key]->SetToRemove(true);
	}
	void GarbageValues()
	{
		vector<Key> _keysToRemove;
		for (const auto& _pair : allValues)
		{
			if (_pair.second->IsToRemove())
			{
				_keysToRemove.push_back(_pair.first);
			}
		}

		for (const Key& _key : _keysToRemove)
		{
			Value* _value = allValues[_key];
			allValues.erase(_key);
			delete _value;
		}
	}

	Value* GetCurrent() const
	{
		return current;
	}
	Value* Get(const Key& _key)
	{
		if (!Exist(_key)) return nullptr;
		return allValues[_key];
	}
	map<Key, Value*> GetAll() const 
	{
		return allValues;
	}
	vector<Value*> GetAllValues() const
	{
		vector<Value*> _values;

		for (const auto& _pair : allValues)
		{
			_values.push_back(_pair.second);
		}

		return _values;
	}

	bool Exist(const Key& _key) const
	{
		//if (allValues.empty()) return false;
		return allValues.find(_key) != allValues.end();
	}
	bool Exist(Value* _value) const
	{
		return Exist(_value->GetID());
	}
};