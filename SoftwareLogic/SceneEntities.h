#ifndef _SCENE_ENTITIES_H
#define _SCENE_ENTITIES_H
#include "CollisionBox.h"
#include "EnumEntities.h"
#include <map>

class SceneEntities
{
public:
	SceneEntities(void);
	~SceneEntities(void);
	static SceneEntities& getInstance(void);
	CollisionBox* CreateEntity(EnumEntities);
	void CleanMap(void);
	std::map<CollisionBox*,EnumEntities>* getEntitiesMap(void);

private:
	static SceneEntities instance;
	std::map<CollisionBox*,EnumEntities>* entities;

};

#endif