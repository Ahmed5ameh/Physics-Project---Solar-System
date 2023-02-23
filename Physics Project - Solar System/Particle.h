#pragma once
#include "Vector2d.h"
#include "Collider.h"
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

class Particle
{
public:
	sf::Texture blackhole;
	sf::Texture planetTexture[4];

	sf::CircleShape circleBody;
	Vector2d position;
	Vector2d velocity;
	Vector2d acceleration;
	Vector2d forces;
	Vector2d normal = Vector2d(1, 0);
	Collider collider;
	
	bool remove = false;
	float mass;

	int particleType = 0;

	Particle(Vector2d position = Vector2d(0, 0), float mass = 1, float radius = 10, Vector2d velocity = Vector2d(0, 0), float type = 0);
	void SetPositionAndMass(Vector2d position, float mass = 1, float radius = 20, int particleType = 0);
	void Update(float dt);
	void ForceFromOtherParticles(list <Particle*> listOfWorldParticles, float times = 1);
	void CheckCollision(list <Particle*> listOfWorldParticles);
	void SetTexture(sf::Texture myTexture);
};

