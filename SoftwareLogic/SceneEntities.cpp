#include "stdafx.h"
#include "SceneEntities.h"
#include "Player.h"
#include "Enemy.h"
#include "../UserInterface/MapTile.h"


SceneEntities SceneEntities::instance;


/**
Constructeur de SceneEntities.
*/
SceneEntities::SceneEntities(void)
{
	this->entities = new std::map<CollisionBox*,EnumEntities>;
}

SceneEntities::~SceneEntities(void)
{
	delete this->entities;
}

SceneEntities& SceneEntities::getInstance(void)
{
	return instance;
}


/**
Fonction qui crée une entites
@param[in] _desiredEntitites Une entites dans l'enum Entites
@return Un pointeur vers l'entity, NULL si invalide.
@see Entites
@see Player
@see Enemy
@todo Ajouter les autres entites.
*/
CollisionBox* SceneEntities::CreateEntity(EnumEntities _desiredEntity)
{
	CollisionBox* createdEntity = NULL;
	EnumEntities EntityType;
	switch (_desiredEntity)
	{
	case EnumEntities::ENEMY:
		createdEntity = new Enemy();
		EntityType = EnumEntities::ENEMY;
		break;
	case EnumEntities::PLAYER:
		createdEntity = new Player();
		EntityType = EnumEntities::PLAYER;
		break;
	case EnumEntities::WALL:
		createdEntity = new MapTile();
		EntityType = EnumEntities::WALL;
		break;
	case EnumEntities::COLLECTIBLE:
		createdEntity = new Actor();
		EntityType = EnumEntities::COLLECTIBLE;
		break;
	case EnumEntities::ENDFLAG:
		createdEntity = new Actor();
		EntityType = EnumEntities::ENDFLAG;
		break;
	default:
		break;
	}

	if (createdEntity != NULL)
	{
		entities->insert(std::make_pair(createdEntity,EntityType));
	}

	return createdEntity;
}

/**
Getter du vecteur d'entities.
@return un pointeur de vecteur de pointeur de collisionBox.
*/
std::map<CollisionBox*,EnumEntities>* SceneEntities::getEntitiesMap(void)
{
	return entities;
}

void SceneEntities::CleanMap(void)
{
	delete this->entities;
	this->entities = new std::map<CollisionBox*,EnumEntities>;
}