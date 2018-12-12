#include "Particle.h"



Particle::Particle()
{
	for (int i = 0; i < num_particles; i++)
	{
		temp_particle_effects[i] = nullptr;
		//part_array[i] = nullptr;
	}
}


Particle::~Particle()
{
}

void Particle::create_particles(tFloat4 color, double timer, tFloat3 acceleration, float particle_kill_condition)   // if it doesn't work try passing in the array as a parameter and fill it out in the &function
{
	//int num_particles = 300;   // 626              // May need to be a member variable
	//particle* temp_particle_effects[300];    // May need to be a mamber variable

	//for (int i = 0; i < num_particles; i++)
	//{
	//	temp_particle_effects[i] = nullptr;
	//	//part_array[i] = nullptr;
	//}

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

	// HAS INFO AFTER THIS

	//for (int i = 0; i < num_particles; i++)
	//{
	//	if (temp_particle_effects[i] == nullptr)    // STILL HAS DATA
	//	{
	//		continue;
	//	}
	//	// DRAW PARTICLES HERE
	//	//renderer.get_particle_array()[i] = temp_particle_effects[i];

	//	part_array[i] = temp_particle_effects[i];  // broke on commented out line

	//	//part_array[i]->position.fX = temp_particle_effects[i]->position.fX;   // BREAKS HERE      Exception thrown at 0x00007FF7ADAC682E in Project.exe: 0xC0000005: Access violation writing location 0x0000000000000000.
	//	//part_array[i]->position.fY = temp_particle_effects[i]->position.fY;
	//	//part_array[i]->position.fZ = temp_particle_effects[i]->position.fZ;

	//	//part_array[i]->prev_Position.fX = temp_particle_effects[i]->prev_Position.fX;
	//	//part_array[i]->prev_Position.fY = temp_particle_effects[i]->prev_Position.fY;
	//	//part_array[i]->prev_Position.fZ = temp_particle_effects[i]->prev_Position.fZ;

	//	//part_array[i]->color.fX = color.fX;
	//	//part_array[i]->color.fY = color.fY;
	//	//part_array[i]->color.fZ = color.fZ;
	//	//part_array[i]->color.fW = color.fW;

	//	//renderer.set_particle_array(part_array);
	//}
	// take the data from the array of pointers and put it into a regular array of non pointers

	//for (int i = 0; i < num_particles; i++)
	//{
	//	temp_p_array[i] = temp_particle_effects[i];
	//	/*temp_p_array[i].color.fX = part_array[i]->color.fX;
	//	temp_p_array[i].color.fY = part_array[i]->color.fY;
	//	temp_p_array[i].color.fZ = part_array[i]->color.fZ;
	//	temp_p_array[i].color.fW = part_array[i]->color.fW;

	//	temp_p_array[i].position.fX = part_array[i]->position.fX;
	//	temp_p_array[i].position.fY = part_array[i]->position.fY;
	//	temp_p_array[i].position.fZ = part_array[i]->position.fZ;

	//	temp_p_array[i].prev_Position.fX = part_array[i]->prev_Position.fX;
	//	temp_p_array[i].prev_Position.fY = part_array[i]->prev_Position.fY;
	//	temp_p_array[i].prev_Position.fZ = part_array[i]->prev_Position.fZ;*/
	//}

	//p_arr = temp_p_array;

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

		pos.fX += (delta.fX) + acceleration.fX * (timer * timer);
		pos.fY += (delta.fY) + acceleration.fY * (timer * timer);
		pos.fZ += (delta.fZ) + acceleration.fZ * (timer * timer);

		temp_particle_effects[i]->position.fX = pos.fX;
		temp_particle_effects[i]->position.fY = pos.fY;
		temp_particle_effects[i]->position.fZ = pos.fZ;

		temp_particle_effects[i]->prev_Position.fX = prevPos.fX;
		temp_particle_effects[i]->prev_Position.fY = prevPos.fY;
		temp_particle_effects[i]->prev_Position.fZ = prevPos.fZ;

		// changing the alpha over time

		random_color = 53 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (203 - 53)));

		random_alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (i % 2 == 0)
		{
			temp_particle_effects[i]->color.fX = random_color;
			temp_particle_effects[i]->color.fY = random_color;
			temp_particle_effects[i]->color.fZ = random_color;
			temp_particle_effects[i]->color.fW = random_alpha;
		}

		// changing the alpha over time

		     // y < -2
		if (pos.fZ < particle_kill_condition)  // kill condition for particles
		{
			particle_pool.release(temp_particle_effects[i]);
			temp_particle_effects[i] = nullptr;
		}

		if (temp_particle_effects[i] != nullptr)
			p_arr[i] = *temp_particle_effects[i];
	}
}

particle* Particle::get_particles()  // Gets called twice when break point is in the function
{
	//for (int i = 0; i < 300; i++)
	//{
	//	p_arr[i].position.fX = particle_pool[i].position.fX;
	//	p_arr[i].position.fY = particle_pool[i]->position.fY;
	//	p_arr[i].position.fZ = particle_pool[i]->position.fZ;

	//	p_arr[i].prev_Position.fX = particle_pool[i]->prev_Position.fX;
	//	p_arr[i].prev_Position.fY = particle_pool[i]->prev_Position.fY;
	//	p_arr[i].prev_Position.fZ = particle_pool[i]->prev_Position.fZ;

	//	p_arr[i].color.fX = particle_pool[i]->color.fX;
	//	p_arr[i].color.fY = particle_pool[i]->color.fY;
	//	p_arr[i].color.fZ = particle_pool[i]->color.fZ;
	//	p_arr[i].color.fW = particle_pool[i]->color.fW;
	//}
	//p_arr = *temp_particle_effects;

	return p_arr;  // has data the first time but isn't showing an array, is NULL the second time
}
