#include "Cloth.h"
#include <iostream>

Cloth::Cloth(vec2 position, int nx, int ny, double spring_length, double spring_constant, double damping)
{
	this->position = position;
	this->particles = std::vector<std::vector<Particle>>(ny);
	this->springs = std::vector<std::vector<std::vector<std::pair<int, int>>>>(ny);
	for (int i = 0; i < nx; i++)
	{
		this->particles[i] = std::vector<Particle>(nx);
		this->springs[i] = std::vector<std::vector<std::pair<int, int>>>(nx);
	}
	for (int j = 0; j < ny; j++)
	{
		for (int i = 0; i < nx; i++)
		{
			// Initialize particles
			this->particles[j][i] = Particle(vec2(i * spring_length, j * spring_length), vec2(0,0), 5);
			// Create 4 springs, connecting indices:
			//				   (i, j + 1)
			// (i - 1, j)		 (i, j)			(i + 1, j)
			//				   (i, j - 1)
			// This is a very simple model and uses just 4 springs
			this->springs[j][i] = std::vector<std::pair<int, int>>(4);
			this->springs[j][i][0] = {i + 1, j};
			this->springs[j][i][1] = { i - 1, j };
			this->springs[j][i][2] = { i, j + 1 };
			this->springs[j][i][3] = { i, j - 1 };
		}
	}

	this->spring_length = spring_length;
	this->spring_constant = spring_constant;
	this->damping = damping;
}

void Cloth::UpdateGrid(double delta_t)
{
	for (int i = 0; i < 10; i++)
	{
		// Iterate through each particle
		for (int j = 0; j < this->particles.size(); j++)
		{
			for (int i = 0; i < this->particles.size(); i++)
			{
				std::vector<std::pair<int, int>> sprs = this->springs[j][i];
				for (int k = 0; k < sprs.size(); k++)
				{
					// Iterate through each spring and apply spring force from each 
					// spring onto the particle and apply the restoring force on both
					// the particles.
					
					// Then apply damping force on the current particle to slow down its 
					// velocity.

					// Get indexes of the spring particle
					int i1 = sprs[k].first;
					int j1 = sprs[k].second;

					// Ensure the particle indices are proper
					if (i1 >= 0 && j1 >= 0 && i1 < this->particles[0].size() && j1 < this->particles.size()) {
						// Measure the length
						Particle other = this->particles[j1][i1];
						// Calculate dx
						double other_distance = (other.position - this->particles[j][i].position).length();
						double delta_x = (other_distance - this->spring_length);
						// If dx > 0 then apply spring force
						if (fabs(delta_x) > 0.01)
						{
							// F_sp = k * ((p - q) / |p - q|) * dx
							Force spring_force = (other.position - this->particles[j][i].position) * (2 * (delta_x) / other_distance);
							// Add damping
							Force damping_force = -(this->particles[j][i].velocity) * this->damping;
							this->particles[j][i].ApplyForce(spring_force, delta_t);
							this->particles[j][i].ApplyForce(damping_force, delta_t);						}
					}

					// Keep the top left and top right particles fixed.
					if (!(i == 0 && j == 0) && !(i == this->particles[0].size() - 1 && j == 0))
					{
						this->particles[j][i].UpdateParticle(delta_t);
					}
				}
			}
		}
	}
}