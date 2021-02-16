#pragma once

#include <glm/glm.hpp>
#include <string>

class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 GetModel() const;

	glm::vec3& GetPosition();
	glm::vec3& GetRotation();
	glm::vec3& GetScale();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	void ShowInspector();

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	std::string m_inspectorID;
};