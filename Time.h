#pragma once
static class Time
{
private:
	static float lastFrame;
	static float timeScale;
public:
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