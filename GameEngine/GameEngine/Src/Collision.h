#pragma once
#include "SDL.h"
#include "Game.h"
#include "ECS/ECS.h"

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

	static int xAxis(const SDL_Rect& recA, const SDL_Rect& recB);
	static int yAxis(const SDL_Rect& recA, const SDL_Rect& recB);
};