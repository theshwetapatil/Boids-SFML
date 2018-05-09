// VehicleSystem.cpp : Defines header for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "Vehicle.h"

class VehicleSystem
{
	private:
		std::vector<Vehicle> vs;
		PVector separationforce;
		PVector alignmentforce;
		PVector cohesionforce;
		float separationweight;
		float alignmentweight;
		float cohesionweight;
		bool separation;
		bool alignment;
		bool cohesion;
		PVector combinedforce;

		float maxseparation = 50;
		float maxalignment = 2000;
		float maxcohesion = 80;

		float maxseparationforce = 10;
		float maxalignmentforce = 20;
		float maxcohesionforce = 5;

	public:
		VehicleSystem();
		std::vector<Vehicle> addVehicle(Vehicle v);
		std::vector<Vehicle> removeVehicle();
		void toggleseparation();
		void togglealignment();
		void togglecohesion();
		PVector getseparationforce();
		PVector getalignmentforce();
		PVector getcohesionforce();
		void setseparationforce(PVector sf);
		void setalignmentforce(PVector af);
		void setcohesionforce(PVector cf);
		float getseparationweight();
		float getalignmentweight();
		float getcohesionweight();
		void setseparationweight(float sw);
		void setalignmentweight(float aw);
		void setcohesionweight(float cw);
		PVector getcombinedforce();
		void setcombinedforce();
		void zeroacceleration();
		void update(float dt, sf::RenderWindow &window);
		PVector calculateseparation(Vehicle v);
		PVector calculatealignment(Vehicle v);
		PVector calculatecohesion(Vehicle v);
		PVector calculatecombinedforce(Vehicle v);
		void seek(PVector target);
		bool getseparation();
		bool getalignment();
		bool getcohesion();
};

