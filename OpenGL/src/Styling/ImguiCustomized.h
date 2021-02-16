#pragma once
#include<iostream>
#include<imgui/imgui.h>
#include<imgui/imgui_internal.h>
#include<glm/glm.hpp>

bool DragFloat3Styled(const std::string& varID, const std::string& label, glm::vec3& value, const std::string& button1, const std::string& button2, const std::string& button3, float resetValue = 0.0f, float columnWidth = 100.0f);

bool DragFloat3Styled(const std::string& varID, const std::string& label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 100.0f);

bool DragFloat2Styled(const std::string& varID, const std::string& label, glm::vec2& value, float resetValue = 0.0f, float columnWidth = 100.0f);

bool DragFloat1Styled(const std::string& varID, const std::string& label, float& value, float resetValue = 0.0f, float columnWidth = 100.0f);