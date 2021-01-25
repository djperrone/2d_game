#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

#include "../TextureManager.h"
#include "../Map.h"
#include "Components.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "../Collision.h"


class KeyboardController : public Component
{
public:
	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				w = true;
				
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				a = true;			
				
				transform->velocity.x = -1;			
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;

					
				break;
			case SDLK_d:
				d = true;
				
				transform->velocity.x = 1;
				sprite->Play("Walk");

					
				break;
			case SDLK_s:
				s = true;
				
				transform->velocity.y = 1;
				sprite->Play("Walk");

				
				break;
			default:
				break;
			}			

		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				if (s == true)
					transform->velocity.y = 1;
				else
					transform->velocity.y = 0;
					sprite->Play("Idle");

				w = false;
				break;
			case SDLK_a:
				if (d == true)
					transform->velocity.x = 1;
				else
					transform->velocity.x = 0;
					sprite->Play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;


				a = false;
				break;
			case SDLK_d:
				if (a == true)
					transform->velocity.x = -1;
				else
					transform->velocity.x = 0;
					sprite->Play("Idle");

				d = false;
				break;
			case SDLK_s:
				if (w == true)
					transform->velocity.y = -1;
				else
					transform->velocity.y = 0;
					sprite->Play("Idle");

				s = false;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}

};