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
	smokeFlag = false;				// Set whether or not smoke should begin
	colorsWereSet = false;			// Set whether or not particle colors have been set to the
									// starting grey color

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
		// Initialize the initial positions for each particle, randomly placing them within a 
		// square around the origin with varying starting heights and distances from the center
		positions[i * 3] = getRandomValue(-5.0f, 5.0f);
		positions[i * 3 + 1] = getRandomValue(0.0f, 2.0f);
		positions[i * 3 + 2] = getRandomValue(-5.0f, 5.0f);

		// Define a random direction angle for the current initial velocity
		float angle = getRandomValue(0.0f, 2 * PI);

		// Get a random speed value for the current initial x-velocity
		float speedX = getRandomValue(minSpeedX, maxSpeedX);

		// Get a random speed value for the current initial z-velocity
		float speedZ = getRandomValue(minSpeedZ, maxSpeedZ);

		// Initialize the initial velocities to random values between each component's min and
		// max values, using a sine and cosine relationship for the x- and z-components to create
		// a circular shape for the particle system.
		velocities[i * 3] = speedX * cos(angle);
		velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
		velocities[i * 3 + 2] = speedZ * sin(angle);

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
			positions[i * 3] = getRandomValue(-5.0f, 5.0f);
			positions[i * 3 + 1] = getRandomValue(0.0f, 2.0f);
			positions[i * 3 + 2] = getRandomValue(-5.0f, 5.0f);

			// Define a random direction angle for the current new velocity
			float angle = getRandomValue(0.0f, 2 * PI);

			// Get a random speed value for the current new x-velocity
			float speedX = getRandomValue(minSpeedX, maxSpeedX);

			// Get a random speed value for the current new z-velocity
			float speedZ = getRandomValue(minSpeedZ, maxSpeedZ);

			// Set the particle's new velocity
			velocities[i * 3] = speedX * cos(angle);
			velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
			velocities[i * 3 + 2] = speedZ * sin(angle);

			// Set the particle's new acceleration
			accelerations[i * 3] = getRandomValue(-0.5f, 0.5f);
			accelerations[i * 3 + 1] = 0.25f;
			accelerations[i * 3 + 2] = getRandomValue(-0.5f, 0.5f);

			// Set the particle's new color
			colors[i * 4] = 1.0f;
			colors[i * 4 + 1] = 0.0f;
			colors[i * 4 + 2] = 0.0f;
			colors[i * 4 + 3] = 1.0f;

			// Reset the smoke flag
			smokeFlag = false;

			// Reset the indicator for colors being set to grey
			colorsWereSet = false;
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

			if ((colors[i * 4 + 1] < 1.0f) && !smokeFlag) {
				colors[i * 4 + 1] += (lifeTimes[i] / maxLifeTime) * deltaTime;
			}
			else if (!colorsWereSet && !smokeFlag) {
				smokeFlag = true;
				colorsWereSet = true;
				colors[i * 4] = 0.25f;
				colors[i * 4 + 1] = 0.25f;
				colors[i * 4 + 2] = 0.25f;
			}

			if (smokeFlag) {
				colors[i * 4] += (lifeTimes[i] / maxLifeTime) * deltaTime;
				colors[i * 4 + 1] += (lifeTimes[i] / maxLifeTime) * deltaTime;
				colors[i * 4 + 2] += (lifeTimes[i] / maxLifeTime) * deltaTime;
			}

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
