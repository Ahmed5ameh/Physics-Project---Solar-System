#include "Particle.h"
#include "PhysicsWorld.h"

bool isEmpty = false;

void Particle::SetTexture(sf::Texture myTexture){
	circleBody.setTexture(&myTexture);
}

Particle::Particle(Vector2d position, float mass, float radius, Vector2d velocity , float type){
	this->mass = mass * radius;
	this->position = position;
	this->velocity = Vector2d((velocity.x + radius / 2), (velocity.y + radius / 2));
	particleType = type;

	collider.center = position;
	collider.r = radius;

	circleBody.setRadius(collider.r);
	circleBody.setOrigin(sf::Vector2f(radius, radius));
	circleBody.setPosition(sf::Vector2f(position));
	circleBody.setFillColor(sf::Color::Green);
	if (isEmpty == false && particleType == 1)	this->circleBody.setTexture(&blackhole);
}


void Particle::SetPositionAndMass(Vector2d position, float mass, float radius, int particleType){
	this->particleType = particleType;
	this->mass = mass*radius;
	this->position = position;

	collider.center = position;
	collider.r = radius;

	circleBody.setRadius(radius);
	circleBody.setOrigin(sf::Vector2f(radius,radius));
	circleBody.setPosition(sf::Vector2f(position));
}

void Particle::Update(float dt){
	acceleration = forces * (1.0f / mass);
	velocity += dt * acceleration;
	if (particleType == 0)	position += dt * velocity;
	forces = Vector2d(0, 0);
	collider.center = position;
	circleBody.setPosition(position);
}

void Particle::ForceFromOtherParticles(list <Particle*> listOfWorldParticles, float times){
	list<Particle*>::iterator it;
	list<Particle*>::iterator begin = listOfWorldParticles.begin();
	list<Particle*>::iterator end = listOfWorldParticles.end();
	for (it = begin; it != end &&listOfWorldParticles.size()>1; it++){
		float distanceOfOther = pow(((*it)->position - position).getMagnitude(), 2);
		if (distanceOfOther != 0 && listOfWorldParticles.size() > 1) {
			Vector2d forceDirection = ((*it)->position - position).getNormalized();
			Vector2d gravitationalForce = forceDirection * ((6.6730 * powf(10, -11) * mass * (*it)->mass) / distanceOfOther);
			forces += gravitationalForce * times;
			CheckCollision(listOfWorldParticles);
		}
	}
}

void Particle::CheckCollision(list <Particle*> listOfWorldParticles){
	list<Particle*>::iterator it;
	list<Particle*>::iterator begin = listOfWorldParticles.begin();
	list<Particle*>::iterator end = listOfWorldParticles.end();
	for (it = begin; it != end && listOfWorldParticles.size() > 1; it++){
		float distanceOfOther = pow(((*it)->position - position).getMagnitude(), 2);
		if (distanceOfOther != 0 && ((*it)->collider.center - collider.center).getMagnitude() < ((*it)->collider.r + collider.r)){
			if (collider.r < (*it)->collider.r){
				this->remove = true;
			}
		}
	}
}



