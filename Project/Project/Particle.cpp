#include "Particle.h"



Particle::Particle()
{
}


Particle::~Particle()
{
}

void Particle::create_particles(tFloat4 color, XTime timer, tFloat3 acceleration)
{
	tVertex part_array[888];

	int num_particles = 888;

	Effects <particle, 888> particle_pool;

	particle* temp_particle_effects[888];

	particle temp_particle;

	for (int i = 0; i < num_particles; i++)
	{
		temp_particle_effects[i] = nullptr;
	}

	float particle_timer;
	particle_timer = 0;

	double t;
	t = timer.Delta();

	tFloat3 accel;
	accel = acceleration;

	tFloat3 pos;
	tFloat3 prevPos;

	tFloat3 delta;

	particle_timer += timer.Delta();

	if (particle_timer < 0.8f)
	{
		for (int i = 0; i < num_particles; i++)
		{
			if (temp_particle_effects[i] == nullptr)
			{
				particle part{};

				part.color.fX = color.fX;
				part.color.fY = color.fY;
				part.color.fZ = color.fZ;
				part.color.fW = color.fW;

				temp_particle_effects[i] = particle_pool.allocate(part);
			}
		}
	}

	for (int i = 0; i < num_particles; i++)
	{
		if (temp_particle_effects[i] == nullptr)
		{
			continue;
		}
		// DRAW PARTICLES HERE
		//renderer.get_particle_array()[i] = temp_particle_effects[i];
		part_array[i] = temp_particle_effects[i]
	}



	for (int i = 0; i < num_particles; i++)
	{
		if (temp_particle_effects[i] == nullptr)
		{
			particle part{};

			part.color.fX = color.fX;
			part.color.fY = color.fY;
			part.color.fZ = color.fZ;
			part.color.fW = color.fW;

			temp_particle_effects[i] = particle_pool.allocate(part);

			if (temp_particle_effects[i] == nullptr)
			{
				continue;
			}
		}

		(float)pos.fX = temp_particle_effects[i]->position.fX;
		(float)pos.fY = temp_particle_effects[i]->position.fY;
		(float)pos.fZ = temp_particle_effects[i]->position.fZ;
		(float)prevPos.fX = temp_particle_effects[i]->prev_Position.fX;
		(float)prevPos.fY = temp_particle_effects[i]->prev_Position.fY;
		(float)prevPos.fZ = temp_particle_effects[i]->prev_Position.fZ;

		delta.fX = (pos.fX - prevPos.fX);
		delta.fY = (pos.fY - prevPos.fY);
		delta.fZ = (pos.fZ - prevPos.fZ);

		prevPos.fX = pos.fX;
		prevPos.fY = pos.fY;
		prevPos.fZ = pos.fZ;

		pos.fX += (delta.fX) + accel.fX * (t * t);
		pos.fY += (delta.fY) + accel.fY * (t * t);
		pos.fZ += (delta.fZ) + accel.fZ * (t * t);

		temp_particle_effects[i]->position.fX = pos.fX;
		temp_particle_effects[i]->position.fY = pos.fY;
		temp_particle_effects[i]->position.fZ = pos.fZ;

		temp_particle_effects[i]->prev_Position.fX = prevPos.fX;
		temp_particle_effects[i]->prev_Position.fY = prevPos.fY;
		temp_particle_effects[i]->prev_Position.fZ = prevPos.fZ;

		if (pos.fY < 0)
		{
			particle_pool.release(temp_particle_effects[i]);
			temp_particle_effects[i] = nullptr;
		}
	}
}
