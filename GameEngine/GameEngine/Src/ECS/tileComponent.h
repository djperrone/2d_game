#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"


class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize,int tscale, const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		/*position.x = xpos;
		position.y = ypos;*/
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);

		/*destRect.x = xpos;
		destRect.y = ypos;*/

		destRect.w = destRect.h = tsize * tscale;
	}

	//camera follow player
	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};