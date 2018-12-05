#include "Particle.h"



Particle::Particle()
{
}


Particle::~Particle()
{
}

void Particle::create_particles(tFloat4 color, double timer, tFloat3 acceleration)   // if it doesn't work try passing in the array as a parameter and fill it out in the &function
{
	//int num_particles = 300;   // 626              // May need to be a member variable
	//particle* temp_particle_effects[300];    // May need to be a mamber variable

	particle temp_particle;

	for (int i = 0; i < num_particles; i++)
	{
		temp_particle_effects[i] = nullptr;
	}

	float particle_timer;
	particle_timer = 0;

	double t;
	t = timer;

	tFloat3 accel;
	accel = acceleration;

	tFloat3 pos;
	tFloat3 prevPos;

	tFloat3 delta;

	particle_timer += timer;

	if (particle_timer < 1.5f)  // was 0.8f
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

		//part_array[i] = temp_particle_effects[i];

		part_array[i]->position.fX = temp_particle_effects[i]->position.fX;
		part_array[i]->position.fY = temp_particle_effects[i]->position.fY;
		part_array[i]->position.fZ = temp_particle_effects[i]->position.fZ;

		part_array[i]->prev_Position.fX = temp_particle_effects[i]->prev_Position.fX;
		part_array[i]->prev_Position.fY = temp_particle_effects[i]->prev_Position.fY;
		part_array[i]->prev_Position.fZ = temp_particle_effects[i]->prev_Position.fZ;

		part_array[i]->color.fX = color.fX;
		part_array[i]->color.fY = color.fY;
		part_array[i]->color.fZ = color.fZ;
		part_array[i]->color.fW = color.fW;

		//renderer.set_particle_array(part_array);
	}
	// take the data from the array of pointers and put it into a regular array of non pointers

	for (int i = 0; i < num_particles; i++)
	{
		temp_p_array[i].color.fX = part_array[i]->color.fX;
		temp_p_array[i].color.fY = part_array[i]->color.fY;
		temp_p_array[i].color.fZ = part_array[i]->color.fZ;
		temp_p_array[i].color.fW = part_array[i]->color.fW;

		temp_p_array[i].position.fX = part_array[i]->position.fX;
		temp_p_array[i].position.fY = part_array[i]->position.fY;
		temp_p_array[i].position.fZ = part_array[i]->position.fZ;

		temp_p_array[i].prev_Position.fX = part_array[i]->prev_Position.fX;
		temp_p_array[i].prev_Position.fY = part_array[i]->prev_Position.fY;
		temp_p_array[i].prev_Position.fZ = part_array[i]->prev_Position.fZ;
	}

	p_arr = temp_p_array;

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

particle* Particle::get_particles()
{
	return p_arr;
}
