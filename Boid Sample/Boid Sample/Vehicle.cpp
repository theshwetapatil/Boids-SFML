// Vehicle.cpp : Defines class for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "Vehicle.h"

Vehicle::Vehicle(float x, float y)
{
	acceleration.setMagnitude(0, 0);
	velocity.setMagnitude(0, 0);
	location.setMagnitude(x, y);

	r = 3.0;

	maxspeed = 100;
	maxforce = 500;
}

void Vehicle::driving(float dt, sf::RenderWindow &window)
{
	sf::Vector2f acc = acceleration.getVector();
	sf::Vector2f vel = velocity.getVector();
	sf::Vector2f pos = location.getVector();
	sf::Vector2f desvel = desiredvelocity.getVector();

	vel.x += acc.x * dt;
	vel.y += acc.y * dt;

	float wx = window.getSize().x;
	float xy = window.getSize().y;

	float speed = 15;

	if (pos.x >= window.getSize().x - 12)
	{
		setacceleration(0, 0);
		if (abs(vel.x) > 10)
		{
			if (vel.x < 0)
				vel.x = -10;
			else
				vel.x = 10;
		}
		else
		if (vel.x > 0)
			vel.x = -(vel.x);
	}

	if (pos.y >= window.getSize().y - 12)
	{
		setacceleration(0, 0);
		if (abs(vel.y) > 10)
		{
			if (vel.y < 0)
				vel.y = -10;
			else
				vel.y = 10;
		}
		else
		if (vel.y > 0)
			vel.y = -(vel.y);
	}

	if (pos.x <= 24)
	{
		setacceleration(0, 0);
		if (abs(vel.x) > 10)
		{
			if (vel.x < 0)
				vel.x = 10;
			else
				vel.x = -10;
		}
		else
		if (vel.x < 0)
			vel.x = -(vel.x);

		vel.x = vel.x * speed;

	}

	if (pos.y <= 12)
	{
		setacceleration(0, 0);
		if (abs(vel.y) > 10)
		{
			if (vel.y < 0)
				vel.y = 10;
			else
				vel.y = -10;
		}
		else
		if (vel.y < 0)
			vel.y = -(vel.y);

		vel.y = vel.y * speed;
	}

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

	velocity.setMagnitude(vel.x, vel.y);
	velocity.limit(maxspeed);
	location.setMagnitude(pos.x, pos.y);

	display(pos.x, pos.y, window);
}

void Vehicle::seek(PVector target)
{
	desiredvelocity = location.sub(target);
	float dist = desiredvelocity.getMagnitude();
	desiredvelocity.normalize();


	desiredvelocity = desiredvelocity.mult(maxspeed);

	steer = velocity.sub(desiredvelocity);
	steer.normalize();
	steer = steer.mult(maxforce);

	if (dist > 150) {
		steer.limit(maxforce);
	}
	else {
		steer.limit(dist / 150 * maxforce);
	}
	applyforce(steer);

}

void Vehicle::arrive(PVector target)
{
	desiredvelocity = location.sub(target);

	float d = desiredvelocity.getMagnitude();
	desiredvelocity.normalize();

	if (d < 100) {
		float m = map(d, 0, 100, 0, maxspeed);
		desiredvelocity = desiredvelocity.mult(m);
	}
	else {
		desiredvelocity = desiredvelocity.mult(maxspeed);
	}

	steer = velocity.sub(desiredvelocity);
	steer.limit(maxforce);
	applyforce(steer);
}

void Vehicle::applyforce(PVector force)
{
	acceleration = acceleration.add(force);
}

void Vehicle::updatev()
{
	velocity = velocity.add(acceleration);
	velocity.limit(maxspeed);
	location = location.add(velocity);
	acceleration = acceleration.mult(0);
}

void Vehicle::display(int x, int y, sf::RenderWindow &window)
{

	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(x, y));
	triangle.setPoint(1, sf::Vector2f(x - 24, y - 6));
	triangle.setPoint(2, sf::Vector2f(x - 24, y + 6));

	sf::Vector2f org = triangle.getOrigin();

	triangle.setFillColor(sf::Color::Blue);

	sf::Vector2f vel = velocity.getVector();
	sf::Vector2f pos = location.getVector();
	PVector dummy = PVector(0, 0);

	triangle.setOrigin(sf::Vector2f(x, y));
	triangle.setPosition(triangle.getOrigin());

	float theta = dummy.getangle(velocity);

	if (vel.x > 0 && vel.y > 0)
		triangle.setRotation(theta);
	else
	if (vel.x < 0 && vel.y < 0)
		triangle.setRotation(180 + theta);
	else
	if (vel.x > 0 && vel.y < 0)
		triangle.setRotation(360 - theta);
	else
		triangle.setRotation(180 - theta);

	window.draw(triangle);
}

float Vehicle::map(float value, float start1, float stop1, float start2, float stop2)
{
	if ((start2 < start1 && start2 < stop1) && (stop2 < start1 && stop2 < stop1))
	{
		return value / (start1 - stop2);
	}
	else
	if ((start2 > start1 && start2 > stop1) && (stop2 > start1 && stop2 > stop1))
	{
		return value / (start2 - stop1);
	}

	return value;
}

int Vehicle::getid()
{
	return this->id;
}

void Vehicle::setid(int id)
{
	this->id = id;
}

PVector Vehicle::getdistance(Vehicle v)
{
	return this->location.sub(v.location);
}

void Vehicle::setdistance(PVector dist)
{
	this->location.add(dist);
}

void Vehicle::addvelocity(Vehicle v)
{
	this->velocity.add(v.location);
}

Vehicle Vehicle::divide(int count)
{
	this->location.div(count);
	return Vehicle(getlocation().getVector().x, getlocation().getVector().y);
}

PVector Vehicle::getlocation()
{
	return this->location;
}

PVector Vehicle::getvelocity()
{
	return this->velocity;
}

void Vehicle::limitforce(float force)
{
	float limitx = this->acceleration.getVector().x;
	if (limitx > force)
		limitx = force;
	float limity = this->acceleration.getVector().y;
	if (limity > force)
		limity = force;
	this->acceleration.setMagnitude(limitx, limity);
}

void Vehicle::setacceleration(float x, float y)
{
	this->acceleration.setMagnitude(x, y);
}

void Vehicle::setvelocity(float x, float y)
{
	this->velocity.setMagnitude(x, y);
}