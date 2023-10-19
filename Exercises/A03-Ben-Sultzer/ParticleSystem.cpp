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
		// Initialize the initial positions for each particle randomly placed within the grid
		// around the origin
		positions[i * 3] = getRandomValue(-10.0f, 10.0f); // STOPPED HERE WITH SETTING POSITIONS
		positions[i * 3 + 1] = getRandomValue(25.0f, 50.0f);
		positions[i * 3 + 2] = getRandomValue(25.0f, 50.0f);

		// Initialize the initial velocities to random values between 25 and 50 for
		// each component
		velocities[i * 3] = getRandomValue(25.0f, 50.0f);
		velocities[i * 3 + 1] = getRandomValue(25.0f, 50.0f);
		velocities[i * 3 + 2] = getRandomValue(25.0f, 50.0f);


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
