#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "vec2.h"

class Particle
{
public:
	vec2 position;
	vec2 velocity;
	double mass;

public:
	Particle() { this->position = vec2(0, 0); this->mass = 1; this->velocity = vec2(0, 0); };
	Particle(vec2 p, vec2 v = vec2(0, 0), double m = 1) { this->position = p; this->velocity = v; this->mass = m;  }
	
	void ApplyForce(Force f, double delta_t)
	{
		this->velocity += f * (delta_t / this->mass);
	}

	void UpdateParticle(double delta_t)
	{
		this->position += this->velocity * delta_t;
	}
};

#endif