#pragma once
#include "Maths/WorldMaths.h"

class Player {
public:

	Player() {	};

	~Player() {  };

	void render();

	void update();

public:
	
	Vec3f pos;
	Vec3f vel;

};