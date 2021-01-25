#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	//delay btwn frames in miliseconds
	int speed = 100;

public:
	//initialize sprite animation to 0
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	//make character animation flip
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	//path is filename of pic
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;
		//parameters : index of frame in pic, number of frames, speed
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTex(path);
	}

	~SpriteComponent()
	{		
		SDL_DestroyTexture(texture);
	}


	//use this to change texture/pic
	void setTex(const char* path)
	{
		//texture = Game::assets->GetTexture(id);
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
	
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;
	}
	
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
	}

	void Play(const char* animName) 
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};