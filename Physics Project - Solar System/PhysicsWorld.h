#pragma once
#include "Particle.h"
#include <list>
#include<vector>
using namespace std;

class PhysicsWorld
{
public:
	list<Particle*> listOfWorldParticles;

	void addParticle(Particle* particle);
	void Update(float deltaTime);
	void ClearList();

	static const Vector2d gravity;
};

