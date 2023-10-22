#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = _numParticles;	// Set the number of particles
	
	// Allocate memory for positions, velocities, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	colors = new float[numParticles * 4];	
	lifeTimes = new float[numParticles];

	for (int i = 0; i < numParticles; i++) {
		// Initialize the life times
		lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

		/***************************/
		// Write your code below
		// Please add initializations for other arrays as you see appropriate.
		// Initialize the initial positions for each particle, randomly placing them around
		// the origin with varying starting heights and distances from the center
		positions[i * 3] = getRandomValue(-10.0f, 10.0f);
		positions[i * 3 + 1] = getRandomValue(0.0f, 5.0f);
		positions[i * 3 + 2] = getRandomValue(-10.0f, 10.0f);

		// Initialize the initial velocities to random values between 25 and 50 for
		// each component
		velocities[i * 3] = getRandomValue(-5.0f, 5.0f);
		velocities[i * 3 + 1] = getRandomValue(10.0f, 20.0f);
		velocities[i * 3 + 2] = getRandomValue(-5.0f, 5.0f);

		// Initialize the initial colors of the particles to an orange red with 0% transparency
		colors[i * 4] = 255.0f;
		colors[i * 4 + 1] = 89.0f;
		colors[i * 4 + 2] = 0.0f;
		colors[i * 4 + 3] = 1.0f;
		/***************************/
	}
}

void ParticleSystem::update(float deltaTime)
{
	for (int i = 0; i < numParticles; i++) {
		/***************************/
		// Write your code below
		// Update lifetime, velocity, position, and color.
		// Reset particle states (positions, velocities, colors, and lifetimes) when the lifetime reaches the maxLifeTime
		// If the current particle has reached the end of its life, reset its velocity, position,
		// color, and lifetime. Otherwise, updates its properties
		if (lifeTimes[i] == maxLifeTime) {
			// Set the particle's new lifetime
			lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

			// Set the particle's new position
			positions[i * 3] = getRandomValue(-10.0f, 10.0f);
			positions[i * 3 + 1] = getRandomValue(0.0f, 5.0f);
			positions[i * 3 + 2] = getRandomValue(-10.0f, 10.0f);

			// Set the particle's new velocity
			velocities[i * 3] = getRandomValue(-5.0f, 5.0f);
			velocities[i * 3 + 1] = getRandomValue(10.0f, 20.0f);
			velocities[i * 3 + 2] = getRandomValue(-5.0f, 5.0f);

			// Set the particle's new color
			colors[i * 4] = 255.0f;
			colors[i * 4 + 1] = 89.0f;
			colors[i * 4 + 2] = 0.0f;
			colors[i * 4 + 3] = 1.0f;
		}
		else {
			// Update the particle's lifetime
			lifeTimes[i] += deltaTime;

			// Update the particle's velocity
			velocities[i * 3] += acceleration[0] * deltaTime;
			velocities[i * 3 + 1] += acceleration[1] * deltaTime;
			velocities[i * 3 + 2] += acceleration[2] * deltaTime;

			// Update the particle's position
			positions[i * 3] += velocities[i * 3];
			positions[i * 3 + 1] += velocities[i * 3 + 1];
			positions[i * 3 + 2] += velocities[i * 3 + 2];

			// Scale the particle color's transparency value (every fourth element 
			// of the colors array) by how long it's been alive (closer to end of
			// living period means more transparency)
			colors[i * 4 + 3] -= lifeTimes[i] / maxLifeTime;
		}		
		// Write your code above
		/***************************/
	}
}

void ParticleSystem::draw()
{
	/***************************/
	// Write your code below
	// Use GL_POINTS for rendering
	
	// Write your code above
	/***************************/
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
