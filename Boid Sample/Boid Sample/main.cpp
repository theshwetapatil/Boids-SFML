// main.cpp : Defines the entry point for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "VehicleSystem.h"
#include "Vehicle.h"
#include "PVector.h"

sf::RenderWindow window(sf::VideoMode(500, 500), "Boid flocking!");
sf::Text txt;
sf::Text separationtxt;
sf::Text alignmenttxt;
sf::Text cohesiontxt;
sf::Font font;

Vehicle v = Vehicle(200, 300);
VehicleSystem vs = VehicleSystem();

bool spressed = false;
bool apressed = false;
bool cpressed = false;
bool spacepressed = false;
bool mousepressed = false;

bool sep = vs.getseparation();
bool alg = vs.getalignment();
bool coh = vs.getcohesion();

void update_state(float dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	//press S to toggle separation
	{
		if (!spressed)
		{
			vs.toggleseparation();
			spressed = true;

			sep = vs.getseparation();
			std::string sept;
			if (sep == true)
				sept = "true";
			else
				sept = "false";
			separationtxt.setString("Separation: " + sept);
		}
	}
	else
	{
		spressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		//press A to toggle alignment
	{
		if (!apressed)
		{
			vs.togglealignment();
			apressed = true;

			alg = vs.getalignment();
			std::string algt;
			if (alg == true)
				algt = "true";
			else
				algt = "false";
			alignmenttxt.setString("Alignment: " + algt);
		}
	}
	else
	{
		apressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))		//press C to toggle separation
	{
		if (!cpressed)
		{
			vs.togglecohesion();
			cpressed = true;

			coh = vs.getcohesion();
			std::string coht;
			if (coh == true)
				coht = "true";
			else
				coht = "false";
			cohesiontxt.setString("Cohesion: " + coht);
		}
	}
	else
	{
		cpressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))	//press SPACE to remove vehicles
	{
		if (!spacepressed)
		{
			vs.removeVehicle();
			spacepressed = true;
		}
	}
	else
	{
		spacepressed = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!mousepressed)
		{
			float mousex = sf::Mouse::getPosition(window).x;
			float mousey = sf::Mouse::getPosition(window).y;
			vs.addVehicle(Vehicle(mousex, mousey));
			mousepressed = true;
		}
	}
	else
	{
		mousepressed = false;
	}

	vs.zeroacceleration();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		float mousex = sf::Mouse::getPosition(window).x;
		float mousey = sf::Mouse::getPosition(window).y;

		PVector target(mousex, mousey);
		vs.seek(target);
	}

	vs.update(dt, window);
	window.draw(txt);
	window.draw(separationtxt);
	window.draw(alignmenttxt);
	window.draw(cohesiontxt);
}

int main()
{

	font.loadFromFile("arial.TTF");
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		window.clear();


		txt.setFont(font);
		txt.setCharacterSize(20);

		txt.setString("S:Separation, A:Alignment, C:Cohesion \nRight click: Seek, Left click: Add , Space: Remove ");
		txt.setPosition(10, 20);

		separationtxt.setFont(font);
		separationtxt.setCharacterSize(30);

		std::string sept;
		if (sep == true)
			sept = "true";
		else
			sept = "false";
		separationtxt.setString("Separation: " + sept);
		separationtxt.setPosition(10, 60);

		alignmenttxt.setFont(font);
		alignmenttxt.setCharacterSize(30);

		std::string algt;
		if (alg == true)
			algt = "true";
		else
			algt = "false";
		alignmenttxt.setString("Alignment: " + algt);
		alignmenttxt.setPosition(10, 90);

		cohesiontxt.setFont(font);
		cohesiontxt.setCharacterSize(30);

		std::string coht;
		if (coh == true)
			coht = "true";
		else
			coht = "false";
		cohesiontxt.setString("Cohesion: " + coht);
		cohesiontxt.setPosition(10, 120);

		update_state(dt);
		window.display();
	}


	return 0;
}


