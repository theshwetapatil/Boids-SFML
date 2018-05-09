// PVector.cpp : Defines class for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "PVector.h"

PVector::PVector()
{
	this->x = 0.0;
	this->y = 0.0;
}

PVector::PVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

PVector PVector::add(PVector v)
{
	return PVector(this->x + v.x, this->y + v.y);
}

PVector PVector::sub(PVector v)
{
	return PVector(this->x - v.x, this->y - v.y);
}

PVector PVector::mult(float m)
{
	return PVector((this->x * m), (this->y * m));
}

PVector PVector::div(float m)
{
	if (m != 0)
	{
		return PVector((this->x / m), (this->y / m));
	}
	return PVector(-1, -1);
}

float PVector::getMagnitude()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

void PVector::setMagnitude(float x, float y)
{
	this->x = x;
	this->y = y;
}

void PVector::normalize()
{
	if (getMagnitude() != 0) {
		PVector temp;
		temp = div(getMagnitude());
		this->x = temp.x;
		this->y = temp.y;
	}
	else
	{
		this->x = -1;
		this->y = -1;
	}
}

float PVector::getDotProduct(PVector v)
{
	float h = sqrt((v.x - this->x)*(v.x - this->x) + (v.y - this->y)*(v.y - this->y)); //hypotenus
	float b = sqrt((v.x - this->x)*(v.x - this->x) + (this->y - this->y)*(this->y - this->y)); //adjucent side
	float ctheta;	//cos(theta)
	if (h != 0)
		ctheta = b / h;
	else
		ctheta = 0;
	return (getMagnitude()*v.getMagnitude()*ctheta);
}

float PVector::getCrossProduct(PVector v)
{
	float h = sqrt((v.x - this->x)*(v.x - this->x) + (v.y - this->y)*(v.y - this->y)); //hypotenus
	float a = sqrt((v.x - v.x)*(v.x - v.x) + (v.y - this->y)*(v.y - this->y)); //opposite side
	float stheta;	//sin(theta)
	if (h != 0)
		stheta = a / h;
	else
		stheta = 0;
	return (getMagnitude()*v.getMagnitude()*stheta);
}

void PVector::limit(float max)
{

	float mag = getMagnitude();

	if (mag < max) return;

	float theta = 0.0;

	if (mag != 0) 
	{
		theta = asin(this->y / mag);
	}

	float newx = max * cos(theta);
	float newy = max * sin(theta);

	if (this->x < 0)
	{
		newx = -newx;
	}

	this->x = newx;
	this->y = newy;

}
sf::Vector2f PVector::getVector()
{
	return sf::Vector2f(this->x, this->y);
}

float PVector::getangle(PVector v)
{

	float h = sqrt((v.x - this->x)*(v.x - this->x) + (v.y - this->y)*(v.y - this->y)); //hypotenus
	float b = sqrt((v.x - this->x)*(v.x - this->x) + (this->y - this->y)*(this->y - this->y)); //adjucent side
	float ctheta;	//cos(theta)
	if (h != 0)
		ctheta = b / h;
	else
		ctheta = 0;

	float theta = acos(ctheta)*(180 / 3.14159);
	return theta;
}