#include "Transform.h"

#include <glm/gtx/transform.hpp>
#include <imgui/imgui.h>

#include "../Styling/ImguiCustomized.h"

Transform::Transform(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_inspectorID(std::to_string(rand()))
{
}

glm::mat4 Transform::GetModel() const {
	glm::mat4 positionMatrix = glm::translate(m_position);

	glm::mat4 rotationXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotationYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotationZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

	glm::mat4 scaleMatrix = glm::scale(m_scale);

	return (positionMatrix * rotationMatrix * scaleMatrix);
}

glm::vec3& Transform::GetPosition() {
	return this->m_position;
}

glm::vec3& Transform::GetRotation() {
	return this->m_rotation;
}

glm::vec3& Transform::GetScale() {
	return this->m_scale;
}

void Transform::SetPosition(const glm::vec3& position) {
	this->m_position = position;
}
void Transform::SetRotation(const glm::vec3& rotation) {
	this->m_rotation = rotation;
}
void Transform::SetScale(const glm::vec3& scale) {
	this->m_scale = scale;
}

void Transform::ShowInspector() {
	ImGui::Separator();
	std::string headerID = "Transform" + this->m_inspectorID;
	ImGui::PushID(headerID.c_str());
	if (ImGui::CollapsingHeader("Transform")) {
		DragFloat3Styled(this->m_inspectorID, "Position", this->m_position);
		glm::vec3 rotation = glm::degrees(this->m_rotation);
		if (DragFloat3Styled(this->m_inspectorID, "Rotation", rotation))
			this->m_rotation = glm::radians(rotation);
		DragFloat3Styled(this->m_inspectorID, "Scale", this->m_scale, 1.0f);
	}
	ImGui::PopID();
	ImGui::Separator();
}