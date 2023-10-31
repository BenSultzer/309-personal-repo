#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ParticleSystem.h"
#include <iostream>
#include <math.h>

// Define a value for pi
#define PI 3.14159

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = _numParticles;	// Set the number of particles

	// Allocate memory for positions, velocities, accelerations, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	accelerations = new float[numParticles * 3];
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
		positions[i * 3] = getRandomValue(-3.0f, 3.0f) * cos(((2 * PI) / numParticles) * i);
		positions[i * 3 + 1] = getRandomValue(0.0f, 1.0f);
		positions[i * 3 + 2] = getRandomValue(-3.0f, 3.0f) * sin(((2 * PI) / numParticles) * i);

		// Initialize the initial velocities to random values between -1 and 1 for the x- and
		// z- components, and 1 and 2 for the y-component
		velocities[i * 3] = getRandomValue(-1.0f, 1.0f);
		velocities[i * 3 + 1] = getRandomValue(1.0f, 2.0f);
		velocities[i * 3 + 2] = getRandomValue(-1.0f, 1.0f);

		// Initialize the initial accelerations to random values between -0.5 and 0.5 for the
		// x- and z-components and a constant acceleration of 0.25 for the y-component
		accelerations[i * 3] = getRandomValue(-0.5f, 0.5f);
		accelerations[i * 3 + 1] = 0.25f;
		accelerations[i * 3 + 2] = getRandomValue(-0.5f, 0.5f);

		// Initialize the initial colors of the particles to red with 0% transparency
		colors[i * 4] = 1.0f;
		colors[i * 4 + 1] = 0.0f;
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
		// Reset particle states (acceleration (turbulence), positions, velocities, colors, and lifetimes) when the lifetime 
		// reaches the maxLifeTime. If the current particle has reached the end of its life, reset its acceleration 
		// (turbulence), velocity, position, color, and lifetime. Otherwise, update its properties (except acceleration, 
		// which should remain constant throughout the particle's life)
		if (lifeTimes[i] >= maxLifeTime) {
			// Set the particle's new lifetime
			lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

			// Set the particle's new position
			positions[i * 3] = getRandomValue(-3.0f, 3.0f) * cos(((2 * PI) / numParticles) * i);
			positions[i * 3 + 1] = getRandomValue(0.0f, 1.0f);
			positions[i * 3 + 2] = getRandomValue(-3.0f, 3.0f) * sin(((2 * PI) / numParticles) * i);

			// Set the particle's new velocity
			velocities[i * 3] = getRandomValue(-1.0f, 1.0f);
			velocities[i * 3 + 1] = getRandomValue(1.0f, 2.0f);
			velocities[i * 3 + 2] = getRandomValue(-1.0f, 1.0f);

			// Set the particle's new acceleration
			accelerations[i * 3] = getRandomValue(-0.5f, 0.5f);
			accelerations[i * 3 + 1] = 0.25f;
			accelerations[i * 3 + 2] = getRandomValue(-0.5f, 0.5f);

			// Set the particle's new color
			colors[i * 4] = 1.0f;
			colors[i * 4 + 1] = 0.0f;
			colors[i * 4 + 2] = 0.0f;
			colors[i * 4 + 3] = 1.0f;
		}
		else {
			// Update the particle's lifetime
			lifeTimes[i] += deltaTime;

			// Update the particle's velocity
			velocities[i * 3] += accelerations[i * 3] * deltaTime;
			velocities[i * 3 + 1] += accelerations[i * 3 + 1] * deltaTime;
			velocities[i * 3 + 2] += accelerations[i * 3 + 2] * deltaTime;

			// Update the particle's position
			positions[i * 3] += velocities[i * 3] * deltaTime;
			positions[i * 3 + 1] += velocities[i * 3 + 1] * deltaTime;
			positions[i * 3 + 2] += velocities[i * 3 + 2] * deltaTime;

			// Scale the particle color's transparency value down and green value up (every second 
			// and fourth elements of the colors array) by how long the particle has been alive 
			// (closer to end of living period means more transparency and more green) CHECK THIS COMMENT!!!
			colors[i * 4 + 1] += (lifeTimes[i] / maxLifeTime) * deltaTime;
			colors[i * 4 + 3] -= (lifeTimes[i] / maxLifeTime) * deltaTime;
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
	// Set the point size
	glPointSize(3.0f);

	// Set the colors with Color Array
	glEnableClientState(GL_COLOR_ARRAY);
	// Draw with Vertex Array
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, positions);
	glDrawArrays(GL_POINTS, 0, numParticles);
	glDisableClientState(GL_VERTEX_ARRAY);	
	glDisableClientState(GL_COLOR_ARRAY);

	// Reset the point size
	glPointSize(1.0f);
	// Write your code above
	/***************************/
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
