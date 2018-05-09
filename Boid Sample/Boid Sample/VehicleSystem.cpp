// VehicleSystem.cpp : Defines class for the windows application.
// Generative System: Boids Flocking Algorithm
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include "VehicleSystem.h"

VehicleSystem::VehicleSystem()
{

	setseparationweight(50);
	setalignmentweight(20);
	setcohesionweight(30);

	separation = true;
	alignment = true;
	cohesion = true;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		float x = rand() % 400 + 50;
		float y = rand() % 400 + 50;
		vs.push_back(Vehicle(x, y));
	}
	for (int i = 0; i < vs.size(); i++)
		vs.at(i).setid(i);
	int abc = 0;

}

std::vector<Vehicle> VehicleSystem::addVehicle(Vehicle v)
{
	vs.push_back(v);
	return this->vs;
}

std::vector<Vehicle> VehicleSystem::removeVehicle()
{
	if (vs.size()>0)
		vs.pop_back();
	return this->vs;
}

void VehicleSystem::toggleseparation()
{
	if (this->separation == true)
		this->separation = false;
	else
		this->separation = true;
}

void VehicleSystem::togglealignment()
{
	if (this->alignment == true)
		this->alignment = false;
	else
		this->alignment = true;
}

void VehicleSystem::togglecohesion()
{
	if (this->cohesion == true)
		this->cohesion = false;
	else
		this->cohesion = true;
}

PVector VehicleSystem::getseparationforce()
{
	return this->separationforce;
}

PVector VehicleSystem::getalignmentforce()
{
	return this->alignmentforce;
}

PVector VehicleSystem::getcohesionforce()
{
	return this->cohesionforce;
}

void VehicleSystem::setseparationforce(PVector sf)
{
	this->separationforce = sf;
}

void VehicleSystem::setalignmentforce(PVector af)
{
	this->alignmentforce = af;
}

void VehicleSystem::setcohesionforce(PVector cf)
{
	this->cohesionforce = cf;
}

float VehicleSystem::getseparationweight()
{
	return this->separationweight;
}

float VehicleSystem::getalignmentweight()
{
	return this->alignmentweight;
}

float VehicleSystem::getcohesionweight()
{
	return this->cohesionweight;
}

void VehicleSystem::setseparationweight(float sw)
{
	this->separationweight = sw;
}

void VehicleSystem::setalignmentweight(float aw)
{
	this->alignmentweight = aw;
}

void VehicleSystem::setcohesionweight(float cw)
{
	this->cohesionweight = cw;
}

PVector VehicleSystem::getcombinedforce()
{
	return this->combinedforce;
}

void VehicleSystem::setcombinedforce()
{
	int s, a, c;
	if (this->separation == true)
		s = 1;
	else
		s = 0;
	if (this->alignment == true)
		a = 1;
	else
		a = 0;
	if (this->cohesion == true)
		c = 1;
	else
		c = 0;

	float combinedx = s * this->separationweight * this->separationforce.getVector().x + a * this->alignmentweight * this->alignmentforce.getVector().x + c * this->cohesionweight * this->alignmentforce.getVector().x;
	float combinedy = s * this->separationweight * this->separationforce.getVector().y + a * this->alignmentweight * this->alignmentforce.getVector().y + c * this->cohesionweight * this->alignmentforce.getVector().y;
	this->combinedforce.setMagnitude(combinedx, combinedy);
}

void VehicleSystem::zeroacceleration()
{
	for (int i = 0; i < vs.size(); i++) {
		vs.at(i).setacceleration(0, 0);
	}
}

void  VehicleSystem::update(float dt, sf::RenderWindow &window)
{

	for (int i = 0; i < vs.size(); i++)
	{
		PVector combf = calculatecombinedforce(vs.at(i));
		vs.at(i).applyforce(combf);

		vs.at(i).driving(dt, window);
	}

}

PVector VehicleSystem::calculateseparation(Vehicle v)
{
	PVector sf;
	int count = 0;
	for (int i = 0; i < vs.size(); i++)
	{
		if (vs.at(i).getid() != v.getid())
		{

			float d = v.getdistance(vs.at(i)).getMagnitude();
			if (d < maxseparation)
			{
				PVector diff = v.getdistance(vs.at(i));
				diff.normalize();
				sf = sf.add(diff);
				count++;
			}
		}
	}

	sf = sf.div(count);

	return sf;
}

PVector VehicleSystem::calculatealignment(Vehicle v)
{
	PVector af;
	int count = 0;
	for (int i = 0; i < vs.size(); i++)
	{

		if (vs.at(i).getid() != v.getid())
		{
			float d = v.getdistance(vs.at(i)).getMagnitude();
			if (d < maxalignment)
			{
				af = af.add(vs.at(i).getvelocity());
				count++;
			}
		}
		else
			i++;
	}
	af = af.div(count);

	return af;
}

PVector VehicleSystem::calculatecohesion(Vehicle v)
{
	PVector cf;
	int ct = 0;
	float cohx = 0;
	float cohy = 0;
	for (int i = 0; i < vs.size(); i++)
	{
		cohx += vs.at(i).getlocation().getVector().x;
		cohy += vs.at(i).getlocation().getVector().y;
		ct++;
	}
	cohx = cohx / ct;
	cohy = cohy / ct;

	int count = 0;
	for (int i = 0; i < vs.size(); i++)
	{
		if (vs.at(i).getid() != v.getid())
		{
			float d = v.getdistance(Vehicle(cohx, cohy)).getMagnitude();
			if (d < maxcohesion)
			{
				PVector diff = v.getdistance(Vehicle(cohx, cohy));
				diff.normalize();
				cf = cf.add(diff);
				count++;
			}
		}
		else
			i++;
	}

	cf = cf.div(count);

	return cf;
}

PVector VehicleSystem::calculatecombinedforce(Vehicle v)
{
	int s, a, c;
	if (this->separation == true)
		s = 1;
	else
		s = 0;
	if (this->alignment == true)
		a = 1;
	else
		a = 0;
	if (this->cohesion == true)
		c = 1;
	else
		c = 0;

	float combinedx = s * this->separationweight * calculateseparation(v).getVector().x + a * this->alignmentweight * calculatealignment(v).getVector().x + c * this->cohesionweight * calculatecohesion(v).getVector().x;
	float combinedy = s * this->separationweight * calculateseparation(v).getVector().y + a * this->alignmentweight * calculatealignment(v).getVector().y + c * this->cohesionweight * calculatecohesion(v).getVector().y;

	this->combinedforce.setMagnitude(combinedx, combinedy);
	return combinedforce;
}

void VehicleSystem::seek(PVector target)
{
	for (int i = 0; i < vs.size(); i++)
		vs.at(i).seek(target);
}

bool VehicleSystem::getseparation()
{
	return this->separation;
}

bool VehicleSystem::getalignment()
{
	return this->alignment;
}

bool VehicleSystem::getcohesion()
{
	return this->cohesion;
}