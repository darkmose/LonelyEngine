#pragma once

namespace Time 
{
	float lastFrame;
	float timeScale = 1;
	void CalculateDelta();

	float currenttime;
	float deltaTime;	

	void CalculateDelta()
	{
		deltaTime = (currenttime - lastFrame) * timeScale;
		lastFrame = currenttime;
	}
}
