#pragma once
//Time Class
static class Time
{
private:

public:
	static float lastFrame;
	static float timeScale;
	static void CalculateDelta();

	static float currenttime;
	static float deltaTime;
};

void Time::CalculateDelta()
{
	Time::deltaTime = (Time::currenttime - Time::lastFrame)*Time::timeScale;
	Time::lastFrame = Time::currenttime;
}

float Time::lastFrame;
float Time::currenttime;
float Time::deltaTime;
float Time::timeScale = 1;