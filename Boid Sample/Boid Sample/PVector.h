// PVector.cpp : Defines header for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <math.h>
#include <map>
#include <vector>
#include <time.h>

class PVector
{
	private:
		float x;	//x-component of the vector
		float y;	//y-component of the vector

	public:
		PVector();
		PVector(float x, float y);
		PVector add(PVector v);
		PVector sub(PVector v);
		PVector mult(float m);
		PVector div(float m);
		float getMagnitude();
		void setMagnitude(float x, float y);
		void normalize();
		float getDotProduct(PVector v);
		float getCrossProduct(PVector v);
		void limit(float max);
		sf::Vector2f getVector();
		float getangle(PVector v);
};

