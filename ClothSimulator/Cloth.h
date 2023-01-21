#ifndef CLOTH_H
#define CLOTH_H

#include <vector>

#include "vec2.h"
#include "Particle.h"

class Cloth
{
public:
	vec2 position;
	std::vector<std::vector<Particle>> particles;
	std::vector<std::vector<std::vector<std::pair<int, int>>>> springs;
	// Spring variables
	double spring_constant;
	double spring_length;
	double damping;
	Cloth(vec2 position, int nx, int ny, double spring_length, double spring_constant, double damping);
	void UpdateGrid(double delta_t);
};

#endif
