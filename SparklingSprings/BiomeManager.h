#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Biome.h"

class BiomeManager : public Singleton<BiomeManager> , public IManager<string, Biome>
{

};

