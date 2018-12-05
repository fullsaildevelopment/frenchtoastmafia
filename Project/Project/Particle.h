#pragma once
#include "Effects.h"
#include "XTime.h"
#include "Render_Manager.h"
#include "basic_structs.h"

class Particle
{
	//struct particle
	//{
	//	tFloat3 position;
	//	tFloat3 prev_Position;
	//	tFloat4 color;

	//	particle()
	//	{
	//		position.fX = 0;      // % / * by small #
	//		position.fY = 0;
	//		position.fZ = 0;

	//		prev_Position.fX = rand() % 10 * -0.0015f;
	//		prev_Position.fY = rand() % 10 * -0.005f;
	//		prev_Position.fZ = rand() % 10 * -0.0015f;

	//		color.fX = rand() % 10 * 0.10f;        // % / * by small #
	//		color.fY = rand() % 10 * 0.10f;
	//		color.fZ = rand() % 10 * 0.10f;
	//		color.fW = 1.0f;

	//	}
	//};

	//cRender_Manager renderer;
	particle* p_arr;
	particle* part_array[300];
	particle temp_p_array[300];

	Effects <particle, 300> particle_pool;

	int num_particles = 300;
	particle* temp_particle_effects[300];

public:
	Particle();
	~Particle();
	void create_particles(tFloat4 color, double timer, tFloat3 acceleration);
	particle* Particle::get_particles();
};

