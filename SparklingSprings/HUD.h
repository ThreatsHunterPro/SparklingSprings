#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"

class HUD : public Singleton<HUD>, public IManager<string, Canvas>
{

};