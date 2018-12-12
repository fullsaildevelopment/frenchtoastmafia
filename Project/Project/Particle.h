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

	float random_color;

	float random_alpha;

	tFloat3 pos;

	tFloat3 prevPos;

	tFloat3 delta;

	float particle_timer = 0;

	int num_particles = 50;

	particle* temp_particle_effects[50];  

	particle* p_arr = new particle[50];
	//particle* part_array[300];
	//particle temp_p_array[300];

	Effects <particle, 50> particle_pool;

public:
	Particle();
	~Particle();
	void create_particles(tFloat4 color, double timer, tFloat3 acceleration, float particle_kill_condition);
	particle* Particle::get_particles();
};

