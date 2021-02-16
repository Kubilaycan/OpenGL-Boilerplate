#pragma once

class Time {
public:
	Time();
	void CalculateDelta();
	float deltaTime;
private:
	float m_currentTime;
	float m_lastTime;
};