#include "PhysicsWorld.h"
#include <iostream>

using namespace std;

void PhysicsWorld::addParticle(Particle* particle){
	if (particle->remove == false)
		listOfWorldParticles.push_back(particle);
}

void PhysicsWorld::Update(float deltaTime){
	list<Particle*>::iterator it;
	for (it = listOfWorldParticles.begin(); it != listOfWorldParticles.end(); it++){
		(**it).Update(deltaTime);
	}
}

void PhysicsWorld::ClearList(){
	listOfWorldParticles.clear();
}

const Vector2d PhysicsWorld::gravity = Vector2d(0, 9.8f);
