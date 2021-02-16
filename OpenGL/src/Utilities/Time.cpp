#include "Time.h"

#include <GLFW/glfw3.h>

Time::Time() :
	deltaTime(0.0f),
	m_currentTime(0.0f),
	m_lastTime(0.0f)
{
}

void Time::CalculateDelta()
{
	this->m_currentTime = static_cast<float>(glfwGetTime());
	this->deltaTime = this->m_currentTime - this->m_lastTime;
	this->m_lastTime = m_currentTime;
}
