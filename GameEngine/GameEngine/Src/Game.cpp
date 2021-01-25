#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "Collision.h"




Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;

SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };


bool Game::isRunning = false;

auto& player(manager.addEntity());


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}


	//mapfile, scale, tilesize
	map = new Map("assets/terrain_ss.png", 3, 32);

	map->LoadMap("assets/map.map", 25, 20);


//create list of things to render in order	
	

	//ECS implimentation

	//add a new player and set their position
	//****THIS IS MY CHARACTERS DIMENSION...?
	//player.addComponent<TransformComponent>(500,500,512,320,.25);
	//player.addComponent<TransformComponent>(4);
	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);

	//getplayer texture
	//MY PLAYER TEXZTURE
	//player.addComponent<SpriteComponent>("assets/player.png");

	//player.addComponent<SpriteComponent>("assets/player_idle.png");...NOT ANIMATED
	//PATH, NUMBER OF FRAMES IN ANIMATION, DELAY SPEED...HIGHER SPEED MEANS SLOWER
	//player.addComponent<SpriteComponent>("assets/player_idle.png",4,100); // ... ANIMATED 4 frames...idle
	player.addComponent<SpriteComponent>("assets/player_anims.png",true); // ... walk and idle animations...path and bool isAnimated


	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);



}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
//auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
//auto& allies(manager.getGroup(groupAllies));

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	//COLLISION!!!!!!
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerpos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();	

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerpos;
		}
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//camera follows player - 400 is half the screen tp keep player in middle
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}



void Game::render()
{
	SDL_RenderClear(renderer);
	// order of render groupings

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	/*for (auto& e : enemies)
	{
		e->draw();
	}*/

	//for (auto& a : allies)
	//{
	//	a->draw();
	//}
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}