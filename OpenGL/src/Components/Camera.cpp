#include "Camera.h"

#include <glm/gtx/transform.hpp>
#include <imgui/imgui.h>
#include <stdlib.h>

#include "../Styling/ImguiCustomized.h"


///Implementation of Perspective Camera
Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) :
	m_position(pos),
	m_fov(fov),
	m_aspect(aspect),
	m_zNear(zNear),
	m_zFar(zFar),
	m_type(CameraType::Perspective),
	m_pitch(0.0f),
	m_yaw(-90.0f),
	m_roll(0.0f),
	m_inspectorID(std::to_string(rand()))
{
	m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_forward.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
	this->m_forward.y = sin(glm::radians(this->m_pitch));
	this->m_forward.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
	this->m_forward = glm::normalize(this->m_forward);
	this->m_rightvec = glm::normalize(glm::cross(this->m_forward, this->m_worldUp));
	this->m_up = glm::normalize(glm::cross(this->m_rightvec, this->m_forward));
	//m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
	//m_rightvec = glm::vec3(1.0f, 0.0f, 0.0f);
}

///Implementation of Orthographic Camera
Camera::Camera(float bottom, float top, float left, float right) :
	m_bottom(bottom),
	m_top(top),
	m_left(left),
	m_right(right),
	m_type(CameraType::Orthographic),
	m_inspectorID(std::to_string(rand()))
{
	m_orthographic = glm::ortho(left, right, bottom, top);
	m_translation = glm::vec3(0, 0, 0);
}

glm::mat4 Camera::GetViewProjection() const {
	if (m_type == CameraType::Perspective)
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	if (m_type == CameraType::Orthographic)
		return m_orthographic * glm::translate(glm::mat4(1.0f), m_translation);
}


void Camera::MoveCamera(GLFWwindow * window, float deltaTime, double mouseOffsetX, double mouseOffsetY, double scrollOffset) {
	if (this->m_type == CameraType::Perspective) {
		{
			if (scrollOffset != 0.0f) {
				this->m_position += this->m_forward * (static_cast<float>(scrollOffset) * 5.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_W)) {
				this->m_position += this->m_forward * 10.0f * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				this->m_position -= this->m_forward * 10.0f * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				this->m_position -= this->m_rightvec * 10.0f * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_D)) {
				this->m_position += this->m_rightvec * 10.0f * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE)) {
				this->m_position += this->m_worldUp * 10.0f * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
				this->m_position -= this->m_worldUp * 10.0f * deltaTime;
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
				this->m_position += this->m_up * (static_cast<float>(mouseOffsetY) / 10.0f);
				this->m_position -= this->m_rightvec * (static_cast<float>(mouseOffsetX) / 10.0f);
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
				this->m_pitch += (-mouseOffsetY) * 100.0f * deltaTime;
				this->m_yaw += mouseOffsetX * 100.0f * deltaTime;

				if (this->m_pitch > 85.0f) {
					this->m_pitch = 85.0f;
				}
				else if (this->m_pitch < -85.0f) {
					this->m_pitch = -85.0f;
				}

				if (this->m_yaw > 360.0f || this->m_yaw < -360.0f) {
					this->m_yaw = 0.0f;
				}

				this->m_forward.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
				this->m_forward.y = sin(glm::radians(this->m_pitch));
				this->m_forward.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
				this->m_forward = glm::normalize(this->m_forward);
				this->m_rightvec = glm::normalize(glm::cross(this->m_forward, this->m_worldUp));
				this->m_up = glm::normalize(glm::cross(this->m_rightvec, this->m_forward));
			}
		}
		return;
	}
	if (this->m_type == CameraType::Orthographic) {
		if (glfwGetKey(window, GLFW_KEY_W)) {
			this->m_translation.y -= 10.0f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			this->m_translation.y += 10.0f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			this->m_translation.x += 10.0f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			this->m_translation.x -= 10.0f * deltaTime;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
			this->m_translation.x +=   mouseOffsetX;
			this->m_translation.y -=   mouseOffsetY;
		}
		return;
	}
}

void Camera::ShowInspector() {
	ImGui::Separator();
	if (m_type == CameraType::Perspective) {
		if (ImGui::CollapsingHeader("Perspective Camera")) {
			DragFloat3Styled(this->m_inspectorID, "Position", m_position);
			glm::vec3 rotation(this->m_pitch, this->m_yaw, this->m_roll);
			if (DragFloat3Styled(this->m_inspectorID, "Rotation", rotation, "Pitch", "Yaw", "Roll")) {
				this->m_pitch = rotation.x;
				this->m_yaw = rotation.y;
				this->m_roll = rotation.z;
				this->m_forward.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
				this->m_forward.y = sin(glm::radians(this->m_pitch));
				this->m_forward.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
				this->m_forward = glm::normalize(this->m_forward);
				this->m_rightvec = glm::normalize(glm::cross(this->m_forward, this->m_worldUp));
				this->m_up = glm::normalize(glm::cross(this->m_rightvec, this->m_forward));
			}
			if (DragFloat1Styled(this->m_inspectorID, "Field of View", m_fov, 70.0f, 150.0f)) {
				m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
			}
		}
	}
	if (m_type == CameraType::Orthographic) {
		if (ImGui::CollapsingHeader("Orthographic Camera")) {
			//ImGui::DragFloat3("Position", &m_translation.x, 0.1f, -1000.0f, 1000.0f);
			glm::vec2 translation{ m_translation.x, m_translation.y };
			if (DragFloat2Styled(this->m_inspectorID, "Position", translation)) {
				m_translation.x = translation.x;
				m_translation.y = translation.y;
			}
		}
	}
	ImGui::Separator();
}

