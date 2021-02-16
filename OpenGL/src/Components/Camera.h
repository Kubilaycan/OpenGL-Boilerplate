#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>

enum CameraType {
	Perspective,
	Orthographic
};

class Camera 
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	Camera(float bottom, float top, float left, float right);

	glm::mat4 GetViewProjection() const;

	void MoveCamera(GLFWwindow* window, float deltaTime, double mouseOffsetX, double mouseOffsetY, double scrollOffset);

	void ShowInspector();
private:
	CameraType m_type;
	//-------------Orthographic-------------
	glm::mat4 m_orthographic;
	glm::vec3 m_translation;
	float m_bottom, m_top, m_left, m_right;
	//-------------Perstective--------------
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_rightvec;
	glm::vec3 m_up;
	glm::vec3 m_worldUp;
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;
	float m_pitch;
	float m_yaw;
	float m_roll;

	std::string m_inspectorID;
};