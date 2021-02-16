#include "ImguiCustomized.h"

bool DragFloat3Styled(const std::string & varID, const std::string & label, glm::vec3 & value, const std::string & button1, const std::string & button2, const std::string & button3, float resetValue, float columnWidth)
{
	bool is_changed = false;
	ImGui::PushID((label + varID).c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	//-----------------X----------------
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.1f, 0.1f, 1.0f });
	if (ImGui::Button(button1.c_str(), buttonSize)) {
		value.x = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &value.x, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	//-----------------Y----------------
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	if (ImGui::Button(button2.c_str(), buttonSize)) {
		value.y = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &value.y, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	//-----------------Z----------------
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.1f, 0.8f, 1.0f });
	if (ImGui::Button(button3.c_str(), buttonSize)) {
		value.z = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if (ImGui::DragFloat("##Z", &value.z, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
	return is_changed;
}

bool DragFloat3Styled(const std::string& varID, const std::string & label, glm::vec3& value, float resetValue, float columnWidth)
{
	bool is_changed = false;
	ImGui::PushID((label + varID).c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	//-----------------X----------------
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.1f, 0.1f, 1.0f });
	if (ImGui::Button("X", buttonSize)) {
		value.x = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if(ImGui::DragFloat("##X", &value.x, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	//-----------------Y----------------
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	if (ImGui::Button("Y", buttonSize)) {
		value.y = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if(ImGui::DragFloat("##Y", &value.y, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	//-----------------Z----------------
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.1f, 0.8f, 1.0f });
	if (ImGui::Button("Z", buttonSize)) {
		value.z = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if(ImGui::DragFloat("##Z", &value.z, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
	return is_changed;
}

bool DragFloat2Styled(const std::string& varID, const std::string & label, glm::vec2 & value, float resetValue, float columnWidth)
{
	bool is_changed = false;
	ImGui::PushID((label + varID).c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	//-----------------X----------------
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.1f, 0.1f, 1.0f });
	if (ImGui::Button("X", buttonSize)) {
		value.x = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if(ImGui::DragFloat("##X", &value.x, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	//-----------------Y----------------
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	if (ImGui::Button("Y", buttonSize)) {
		value.y = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	if(ImGui::DragFloat("##Y", &value.y, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
	return is_changed;
}

bool DragFloat1Styled(const std::string& varID, const std::string & label, float & value, float resetValue, float columnWidth)
{
	bool is_changed = false;
	ImGui::PushID((label + varID).c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 30.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.1f, 0.1f, 1.0f });
	if (ImGui::Button("Reset", buttonSize)) {
		value = resetValue;
		is_changed = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	std::string sliderLabel = "##" + label;
	if (ImGui::DragFloat(sliderLabel.c_str(), &value, 0.1f))
		is_changed = true;
	ImGui::PopItemWidth();


	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
	return is_changed;
}
