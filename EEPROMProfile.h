#pragma once
#include "Mode.c"

class EEPROMProfile
{
public:
	bool Setted_PlayMode = false;
	Mode PlayMode = Mode::FreeMode;
	bool Setted_IsMuted = false;
	bool IsMuted = false;
	bool Setted_WaitForConsole = false;
	bool WaitForConsole = false;
	bool Setted_WaitForSending = false;
	bool WaitForSending = false;


};

