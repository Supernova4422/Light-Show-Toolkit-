#pragma once
class Tick_Listener {
public:
	Tick_Listener() {};
	//On_Tick will execute after each function, or in the main when waiting.
	virtual void On_Tick() = 0;
	virtual ~Tick_Listener() = default;
};