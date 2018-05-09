// Vehicle.cpp : Defines header for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "PVector.h"

class Vehicle
{
	private:
		sf::ConvexShape triangle;

		PVector location;
		PVector velocity;
		PVector acceleration;

		float r;
		float maxspeed;
		float maxforce;
		int id;

		PVector desiredvelocity;
		PVector steer;

	public:
		Vehicle(float x, float y);
		void driving(float dt, sf::RenderWindow &window);
		void seek(PVector target);
		void arrive(PVector target);
		void applyforce(PVector force);
		void updatev();
		void display(int x, int y, sf::RenderWindow &window);
		float map(float value, float start1, float stop1, float start2, float stop2);
		int getid();
		void setid(int id);
		PVector getdistance(Vehicle v);
		void setdistance(PVector dist);
		void addvelocity(Vehicle v);
		Vehicle divide(int count);
		PVector getlocation();
		PVector getvelocity();
		void limitforce(float force);
		void setacceleration(float x, float y);
		void setvelocity(float x, float y);
};

