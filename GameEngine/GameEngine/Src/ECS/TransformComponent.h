#pragma once
#include "Components.h"
#include "../Vector2D.h"

struct TransformComponent : public Component
{
public:
	int xpos, ypos;

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;

	int speed = 3;


	//default pos is 0,0
	//TransformComponent() :position{0.0f,0.0f} {}
	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float sc) :scale(sc)// { 400,320; }
	{
		/*position.x = 400;
		position.y = 320;
		scale = sc;*/
		position.x = 600;
		position.y = 500;
		scale = sc;
	}
	//constructor
	TransformComponent(float x, float y) { position.Zero(); }
	//CONSTRUCTOR FOR ALL PLAYERS/OBJECTS
	TransformComponent(float x, float y, int h, int w, float sc) :position{ x,y }, height(h),width(w),scale(sc) {}

	void init() override
	{
		velocity.Zero();
	}
	
	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};



