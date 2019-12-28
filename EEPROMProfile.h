#pragma once
#include "Mode.c"

class EEPROMProfile
{
public:
	bool Setted_IsMuted = false;
	bool IsMuted = false;
	bool Setted_PlayMode = false;
	Mode PlayMode = Mode::FreeMode;


};

