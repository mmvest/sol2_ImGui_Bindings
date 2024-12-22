// MIT License

// Copyright (c) 2020 MSeys

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"
#include "sol/sol.hpp"

#include <string>
#include <tuple>
#include <type_traits> // For checking type of argument passed to templated functions sol_ImGui::Init and sol_ImGui::InitEnum

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#endif

namespace sol_ImGui
{
	// Windows
	inline bool Begin(const std::string& name)															{ return ImGui::Begin(name.c_str()); }
	inline std::tuple<bool, bool> Begin(const std::string& name, bool open)
	{
		if (!open) return std::make_tuple(false, false);

		bool shouldDraw = ImGui::Begin(name.c_str(), &open);

		if(!open)
		{
			ImGui::End();
			return std::make_tuple(false, false);
		}
		
		return std::make_tuple(open, shouldDraw);
	}
	inline std::tuple<bool, bool> Begin(const std::string& name, bool open, int flags)
	{
		if (!open) return std::make_tuple(false, false);
		bool shouldDraw = ImGui::Begin(name.c_str(), &open, static_cast<ImGuiWindowFlags_>(flags));

		if(!open)
		{
			ImGui::End();
			return std::make_tuple(false, false);
		}
		
		return std::make_tuple(open, shouldDraw);
	}
	inline void End()																					{ ImGui::End(); }
	
	// Child Windows
	inline bool BeginChild(const std::string& name)														{ return ImGui::BeginChild(name.c_str()); }
	inline bool BeginChild(const std::string& name, float sizeX)										{ return ImGui::BeginChild(name.c_str(), { sizeX, 0 }); }
	inline bool BeginChild(const std::string& name, float sizeX, float sizeY)							{ return ImGui::BeginChild(name.c_str(), { sizeX, sizeY }); }
	inline bool BeginChild(const std::string& name, float sizeX, float sizeY, int childFlags)			{ return ImGui::BeginChild(name.c_str(), { sizeX, sizeY }, static_cast<ImGuiChildFlags>(childFlags)); }
	inline bool BeginChild(const std::string& name, float sizeX, float sizeY, int childFlags, int flags){ return ImGui::BeginChild(name.c_str(), { sizeX, sizeY }, static_cast<ImGuiChildFlags>(childFlags), static_cast<ImGuiWindowFlags>(flags)); }
	inline void EndChild()																				{ ImGui::EndChild(); }

	// Windows Utilities
	inline bool IsWindowAppearing()																		{ return ImGui::IsWindowAppearing(); }
	inline bool IsWindowCollapsed()																		{ return ImGui::IsWindowCollapsed(); }
	inline bool IsWindowFocused()																		{ return ImGui::IsWindowFocused(); }
	inline bool IsWindowFocused(int flags)																{ return ImGui::IsWindowFocused(static_cast<ImGuiFocusedFlags>(flags)); }
	inline bool IsWindowHovered()																		{ return ImGui::IsWindowHovered(); }
	inline bool IsWindowHovered(int flags)																{ return ImGui::IsWindowHovered(static_cast<ImGuiHoveredFlags>(flags)); }
	inline ImDrawList* GetWindowDrawList()																{ return ImGui::GetWindowDrawList(); }
	
	#ifndef IMGUI_NO_DOCKING	// Define IMGUI_NO_DOCKING to disable this for compatibility with ImGui's master branch
	inline float GetWindowDpiScale()																	{ return ImGui::GetWindowDpiScale(); }
	#endif
	
	inline ImGuiViewport* GetWindowViewport()															{ return nullptr; /* TODO: GetWindowViewport() ==> UNSUPPORTED */ }
	inline std::tuple<float, float> GetWindowPos()														{ const auto vec2{ ImGui::GetWindowPos() };  return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetWindowSize()														{ const auto vec2{ ImGui::GetWindowSize() };  return std::make_tuple(vec2.x, vec2.y); }
	inline float GetWindowWidth()																		{ return ImGui::GetWindowWidth(); }
	inline float GetWindowHeight()																		{ return ImGui::GetWindowHeight(); }

	// Prefer using SetNext...
	inline void SetNextWindowPos(float posX, float posY)												{ ImGui::SetNextWindowPos({ posX, posY }); }
	inline void SetNextWindowPos(float posX, float posY, int cond)										{ ImGui::SetNextWindowPos({ posX, posY }, static_cast<ImGuiCond>(cond)); }
	inline void SetNextWindowPos(float posX, float posY, int cond, float pivotX, float pivotY)			{ ImGui::SetNextWindowPos({ posX, posY }, static_cast<ImGuiCond>(cond), { pivotX, pivotY }); }
	inline void SetNextWindowSize(float sizeX, float sizeY)												{ ImGui::SetNextWindowSize({ sizeX, sizeY }); }
	inline void SetNextWindowSize(float sizeX, float sizeY, int cond)									{ ImGui::SetNextWindowSize({ sizeX, sizeY }, static_cast<ImGuiCond>(cond)); }
	inline void SetNextWindowSizeConstraints(float minX, float minY, float maxX, float maxY)			{ ImGui::SetNextWindowSizeConstraints({ minX, minY }, { maxX, maxY }); }
	inline void SetNextWindowContentSize(float sizeX, float sizeY)										{ ImGui::SetNextWindowContentSize({ sizeX, sizeY }); }
	inline void SetNextWindowCollapsed(bool collapsed)													{ ImGui::SetNextWindowCollapsed(collapsed); }
	inline void SetNextWindowCollapsed(bool collapsed, int cond)										{ ImGui::SetNextWindowCollapsed(collapsed, static_cast<ImGuiCond>(cond)); }
	inline void SetNextWindowFocus()																	{ ImGui::SetNextWindowFocus(); }
	inline void SetNextWindowBgAlpha(float alpha)														{ ImGui::SetNextWindowBgAlpha(alpha); }
	inline void SetWindowPos(float posX, float posY)													{ ImGui::SetWindowPos({ posX, posY }); }
	inline void SetWindowPos(float posX, float posY, int cond)											{ ImGui::SetWindowPos({ posX, posY }, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowSize(float sizeX, float sizeY)													{ ImGui::SetWindowSize({ sizeX, sizeY }); }
	inline void SetWindowSize(float sizeX, float sizeY, int cond)										{ ImGui::SetWindowSize({ sizeX, sizeY }, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowCollapsed(bool collapsed)														{ ImGui::SetWindowCollapsed(collapsed); }
	inline void SetWindowCollapsed(bool collapsed, int cond)											{ ImGui::SetWindowCollapsed(collapsed, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowFocus()																		{ ImGui::SetWindowFocus(); }
	inline void SetWindowFontScale(float scale)															{ ImGui::SetWindowFontScale(scale); }
	inline void SetWindowPos(const std::string& name, float posX, float posY)							{ ImGui::SetWindowPos(name.c_str(), { posX, posY }); }
	inline void SetWindowPos(const std::string& name, float posX, float posY, int cond)					{ ImGui::SetWindowPos(name.c_str(), { posX, posY }, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowSize(const std::string& name, float sizeX, float sizeY)						{ ImGui::SetWindowSize(name.c_str(), { sizeX, sizeY }); }
	inline void SetWindowSize(const std::string& name, float sizeX, float sizeY, int cond)				{ ImGui::SetWindowSize(name.c_str(), { sizeX, sizeY }, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowCollapsed(const std::string& name, bool collapsed)								{ ImGui::SetWindowCollapsed(name.c_str(), collapsed); }
	inline void SetWindowCollapsed(const std::string& name, bool collapsed, int cond)					{ ImGui::SetWindowCollapsed(name.c_str(), collapsed, static_cast<ImGuiCond>(cond)); }
	inline void SetWindowFocus(const std::string& name)													{ ImGui::SetWindowFocus(name.c_str()); }

	// Content Region
	inline std::tuple<float, float> GetContentRegionMax()												{ const auto vec2{ ImGui::GetContentRegionMax() };  return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetContentRegionAvail()												{ const auto vec2{ ImGui::GetContentRegionAvail() };  return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetWindowContentRegionMin()											{ const auto vec2{ ImGui::GetWindowContentRegionMin() };  return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetWindowContentRegionMax()											{ const auto vec2{ ImGui::GetWindowContentRegionMax() };  return std::make_tuple(vec2.x, vec2.y); }
	inline float GetWindowContentRegionWidth()															{ return ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x; }

	// Windows Scrolling
	inline float GetScrollX()																			{ return ImGui::GetScrollX(); }
	inline float GetScrollY()																			{ return ImGui::GetScrollY(); }
	inline float GetScrollMaxX()																		{ return ImGui::GetScrollMaxX(); }
	inline float GetScrollMaxY()																		{ return ImGui::GetScrollMaxY(); }
	inline void SetScrollX(float scrollX)																{ ImGui::SetScrollX(scrollX); }
	inline void SetScrollY(float scrollY)																{ ImGui::SetScrollY(scrollY); }
	inline void SetScrollHereX()																		{ ImGui::SetScrollHereX(); }
	inline void SetScrollHereX(float centerXRatio)														{ ImGui::SetScrollHereX(centerXRatio); }
	inline void SetScrollHereY()																		{ ImGui::SetScrollHereY(); }
	inline void SetScrollHereY(float centerYRatio)														{ ImGui::SetScrollHereY(centerYRatio); }	
	inline void SetScrollFromPosX(float localX)															{ ImGui::SetScrollFromPosX(localX); }
	inline void SetScrollFromPosX(float localX, float centerXRatio)										{ ImGui::SetScrollFromPosX(localX, centerXRatio); }
	inline void SetScrollFromPosY(float localY)															{ ImGui::SetScrollFromPosY(localY); }
	inline void SetScrollFromPosY(float localY, float centerYRatio)										{ ImGui::SetScrollFromPosY(localY, centerYRatio); }

	// Parameters stacks (shared)
	inline void PushFont(ImFont* pFont)																	{ ImGui::PushFont(pFont); }
	inline void PopFont()																				{ ImGui::PopFont(); }
	inline void PushStyleColor(int idx, int col)														{ ImGui::PushStyleColor(static_cast<ImGuiCol>(idx), ImU32(col)); }
	inline void PushStyleColor(int idx, float colR, float colG, float colB, float colA)					{ ImGui::PushStyleColor(static_cast<ImGuiCol>(idx), { colR, colG, colB, colA }); }
	inline void PopStyleColor()																			{ ImGui::PopStyleColor(); }
	inline void PopStyleColor(int count)																{ ImGui::PopStyleColor(count); }
	inline void PushStyleVar(int idx, float val)														{ ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(idx), val); }
	inline void PushStyleVar(int idx, float valX, float valY)											{ ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(idx), { valX, valY }); }
	inline void PopStyleVar()																			{ ImGui::PopStyleVar(); }
	inline void PopStyleVar(int count)																	{ ImGui::PopStyleVar(count); }
	inline std::tuple<float, float, float, float> GetStyleColorVec4(int idx)							{ const auto col{ ImGui::GetStyleColorVec4(static_cast<ImGuiCol>(idx)) };	return std::make_tuple(col.x, col.y, col.z, col.w); }
	inline ImFont* GetFont()																			{ return ImGui::GetFont(); }
	inline float GetFontSize()																			{ return ImGui::GetFontSize(); }
	inline std::tuple<float, float> GetFontTexUvWhitePixel()											{ const auto vec2{ ImGui::GetFontTexUvWhitePixel() };	return std::make_tuple(vec2.x, vec2.y); }
	inline int GetColorU32(int idx, float alphaMul)														{ return ImGui::GetColorU32(static_cast<ImGuiCol>(idx), alphaMul); }
	inline int GetColorU32(float colR, float colG, float colB, float colA)								{ return ImGui::GetColorU32({ colR, colG, colB, colA }); }
	inline int GetColorU32(int col)																		{ return ImGui::GetColorU32(ImU32(col)); }
	
	// Parameters stacks (current window)
	inline void PushItemWidth(float itemWidth)															{ ImGui::PushItemWidth(itemWidth); }
	inline void PopItemWidth()																			{ ImGui::PopItemWidth(); }
	inline void SetNextItemWidth(float itemWidth)														{ ImGui::SetNextItemWidth(itemWidth); }
	inline float CalcItemWidth()																		{ return ImGui::CalcItemWidth(); }
	inline void PushTextWrapPos()																		{ ImGui::PushTextWrapPos(); }
	inline void PushTextWrapPos(float wrapLocalPosX)													{ ImGui::PushTextWrapPos(wrapLocalPosX); }
	inline void PopTextWrapPos()																		{ ImGui::PopTextWrapPos(); }
	//inline void PushAllowKeyboardFocus(bool allowKeyboardFocus)											{ ImGui::PushAllowKeyboardFocus(allowKeyboardFocus); }
	//inline void PopAllowKeyboardFocus()																	{ ImGui::PopAllowKeyboardFocus(); }
	//inline void PushButtonRepeat(bool repeat)															{ ImGui::PushButtonRepeat(repeat); }
	//inline void PopButtonRepeat()																		{ ImGui::PopButtonRepeat(); }

	// Cursor / Layout
	inline void Separator()																				{ ImGui::Separator(); }
	inline void SameLine()																				{ ImGui::SameLine(); }
	inline void SameLine(float offsetFromStartX)														{ ImGui::SameLine(offsetFromStartX); }
	inline void SameLine(float offsetFromStartX, float spacing)											{ ImGui::SameLine(offsetFromStartX, spacing); }
	inline void NewLine()																				{ ImGui::NewLine(); }
	inline void Spacing()																				{ ImGui::Spacing(); }
	inline void Dummy(float sizeX, float sizeY)															{ ImGui::Dummy({ sizeX, sizeY }); }
	inline void Indent()																				{ ImGui::Indent(); }
	inline void Indent(float indentW)																	{ ImGui::Indent(indentW); }
	inline void Unindent()																				{ ImGui::Unindent(); }
	inline void Unindent(float indentW)																	{ ImGui::Unindent(indentW); }
	inline void BeginGroup()																			{ ImGui::BeginGroup(); }
	inline void EndGroup()																				{ ImGui::EndGroup(); }
	inline std::tuple<float, float> GetCursorPos()														{ const auto vec2{ ImGui::GetCursorPos() };  return std::make_tuple(vec2.x, vec2.y); }
	inline float GetCursorPosX()																		{ return ImGui::GetCursorPosX(); }
	inline float GetCursorPosY()																		{ return ImGui::GetCursorPosY(); }
	inline void SetCursorPos(float localX, float localY)												{ ImGui::SetCursorPos({ localX, localY }); }
	inline void SetCursorPosX(float localX)																{ ImGui::SetCursorPosX(localX); }
	inline void SetCursorPosY(float localY)																{ ImGui::SetCursorPosY(localY); }
	inline std::tuple<float, float> GetCursorStartPos()													{ const auto vec2{ ImGui::GetCursorStartPos() };  return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetCursorScreenPos()												{ const auto vec2{ ImGui::GetCursorScreenPos() };  return std::make_tuple(vec2.x, vec2.y); }
	inline void SetCursorScreenPos(float posX, float posY)												{ ImGui::SetCursorScreenPos({ posX, posY }); }
	inline void AlignTextToFramePadding()																{ ImGui::AlignTextToFramePadding(); }
	inline float GetTextLineHeight()																	{ return ImGui::GetTextLineHeight(); }
	inline float GetTextLineHeightWithSpacing()															{ return ImGui::GetTextLineHeightWithSpacing(); }
	inline float GetFrameHeight()																		{ return ImGui::GetFrameHeight(); }
	inline float GetFrameHeightWithSpacing()															{ return ImGui::GetFrameHeightWithSpacing(); }

	// ID stack / scopes
	inline void PushID(const std::string& stringID)														{ ImGui::PushID(stringID.c_str()); }
	inline void PushID(const std::string& stringIDBegin, const std::string& stringIDEnd)				{ ImGui::PushID(stringIDBegin.c_str(), stringIDEnd.c_str()); }
	inline void PushID(const void*)																		{ /* TODO: PushID(void*) ==> UNSUPPORTED */ }
	inline void PushID(int intID)																		{ ImGui::PushID(intID); }
	inline void PopID()																					{ ImGui::PopID(); }
	inline int GetID(const std::string& stringID)														{ return ImGui::GetID(stringID.c_str()); }
	inline int GetID(const std::string& stringIDBegin, const std::string& stringIDEnd)					{ return ImGui::GetID(stringIDBegin.c_str(), stringIDEnd.c_str()); }
	inline int GetID(const void*)																		{ return 0;  /* TODO: GetID(void*) ==> UNSUPPORTED */ }

	// Widgets: Text
	inline void TextUnformatted(const std::string& text)												{ ImGui::TextUnformatted(text.c_str()); }
	inline void TextUnformatted(const std::string& text, const std::string& textEnd)					{ ImGui::TextUnformatted(text.c_str(), textEnd.c_str()); }
	inline void Text(const std::string& text)															{ ImGui::Text(text.c_str()); }
	inline void TextColored(float colR, float colG, float colB, float colA, const std::string& text)	{ ImGui::TextColored({ colR, colG, colB, colA }, text.c_str()); }
	inline void TextDisabled(const std::string& text)													{ ImGui::TextDisabled(text.c_str()); }
	inline void TextWrapped(const std::string text)														{ ImGui::TextWrapped(text.c_str()); }
	inline void LabelText(const std::string& label, const std::string& text)							{ ImGui::LabelText(label.c_str(), text.c_str()); }
	inline void BulletText(const std::string& text)														{ ImGui::BulletText(text.c_str()); }

	// Widgets: Main
	inline bool Button(const std::string& label)														{ return ImGui::Button(label.c_str()); }
	inline bool Button(const std::string& label, float sizeX, float sizeY)								{ return ImGui::Button(label.c_str(), { sizeX, sizeY }); }
	inline bool SmallButton(const std::string& label)													{ return ImGui::SmallButton(label.c_str()); }
	inline bool InvisibleButton(const std::string& stringID, float sizeX, float sizeY)					{ return ImGui::InvisibleButton(stringID.c_str(), { sizeX, sizeY }); }
	inline bool ArrowButton(const std::string& stringID, int dir)										{ return ImGui::ArrowButton(stringID.c_str(), static_cast<ImGuiDir>(dir)); }
	inline void Image(void* textureID, float width, float height)										{ ImGui::Image(textureID, ImVec2(width, height)); }
	//inline void ImageButton()																			{ /* TODO: ImageButton(...) ==> UNSUPPORTED */ }
	inline std::tuple<bool, bool> Checkbox(const std::string& label, bool v)
	{
		bool value{ v };
		bool pressed = ImGui::Checkbox(label.c_str(), &value);

		return std::make_tuple(value, pressed);
	}
	inline bool CheckboxFlags()																			{ return false; /* TODO: CheckboxFlags(...) ==> UNSUPPORTED */ }
	inline bool RadioButton(const std::string& label, bool active)										{ return ImGui::RadioButton(label.c_str(), active); }
	inline std::tuple<int, bool> RadioButton(const std::string& label, int v, int vButton)				{ bool ret{ ImGui::RadioButton(label.c_str(), &v, vButton) }; return std::make_tuple(v, ret); }
	inline void ProgressBar(float fraction)																{ ImGui::ProgressBar(fraction); }
	inline void ProgressBar(float fraction, float sizeX, float sizeY)									{ ImGui::ProgressBar(fraction, { sizeX, sizeY }); }
	inline void ProgressBar(float fraction, float sizeX, float sizeY, const std::string& overlay)		{ ImGui::ProgressBar(fraction, { sizeX, sizeY }, overlay.c_str()); }
	inline void Bullet()																				{ ImGui::Bullet(); }

	// Widgets: Combo Box
	inline bool BeginCombo(const std::string& label, const std::string& previewValue)					{ return ImGui::BeginCombo(label.c_str(), previewValue.c_str()); }
	inline bool BeginCombo(const std::string& label, const std::string& previewValue, int flags)		{ return ImGui::BeginCombo(label.c_str(), previewValue.c_str(), static_cast<ImGuiComboFlags>(flags)); }
	inline void EndCombo()																				{ ImGui::EndCombo(); }
	inline std::tuple<int, bool> Combo(const std::string& label, int currentItem, const sol::table& items, int itemsCount)
	{
		std::vector<std::string> strings;
		for (int i{ 1 }; i <= itemsCount; i++)
		{
			const auto& stringItem = items.get<sol::optional<std::string>>(i);
			strings.push_back(stringItem.value_or("Missing"));
		}
		
		std::vector<const char*> cstrings;
		for (auto& string : strings)
			cstrings.push_back(string.c_str());
			
		bool clicked = ImGui::Combo(label.c_str(), &currentItem, cstrings.data(), itemsCount);
		return std::make_tuple(currentItem, clicked);
	}
	inline std::tuple<int, bool> Combo(const std::string& label, int currentItem, const sol::table& items, int itemsCount, int popupMaxHeightInItems)
	{
		std::vector<std::string> strings;
		for (int i{ 1 }; i <= itemsCount; i++)
		{
			const auto& stringItem = items.get<sol::optional<std::string>>(i);
			strings.push_back(stringItem.value_or("Missing"));
		}

		std::vector<const char*> cstrings;
		for (auto& string : strings)
			cstrings.push_back(string.c_str());

		bool clicked = ImGui::Combo(label.c_str(), &currentItem, cstrings.data(), itemsCount, popupMaxHeightInItems);
		return std::make_tuple(currentItem, clicked);
	}
	inline std::tuple<int, bool> Combo(const std::string& label, int currentItem, const std::string& itemsSeparatedByZeros)
	{
		bool clicked = ImGui::Combo(label.c_str(), &currentItem, itemsSeparatedByZeros.c_str());
		return std::make_tuple(currentItem, clicked);
	}
	inline std::tuple<int, bool> Combo(const std::string& label, int currentItem, const std::string& itemsSeparatedByZeros, int popupMaxHeightInItems)
	{
		bool clicked = ImGui::Combo(label.c_str(), &currentItem, itemsSeparatedByZeros.c_str(), popupMaxHeightInItems);
		return std::make_tuple(currentItem, clicked);
	}
	// TODO: 3rd Combo from ImGui not Supported

	// Widgets: Drags
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v)																											{ bool used = ImGui::DragFloat(label.c_str(), &v); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v, float v_speed)																							{ bool used = ImGui::DragFloat(label.c_str(), &v, v_speed); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v, float v_speed, float v_min)																				{ bool used = ImGui::DragFloat(label.c_str(), &v, v_speed, v_min); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v, float v_speed, float v_min, float v_max)																{ bool used = ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v, float v_speed, float v_min, float v_max, const std::string& format)										{ bool used = ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> DragFloat(const std::string& label, float v, float v_speed, float v_min, float v_max, const std::string& format, int flags)							{ bool used = ImGui::DragFloat(label.c_str(), &v, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags) flags); return std::make_tuple(v, used); }
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value, v_speed);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v, float v_speed, float v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value, v_speed, v_min);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat2(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::DragFloat2(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value, v_speed);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v, float v_speed, float v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value, v_speed, v_min);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat3(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::DragFloat3(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value, v_speed);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v, float v_speed, float v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value, v_speed, v_min);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> DragFloat4(const std::string& label, const sol::table& v, float v_speed, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::DragFloat4(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline void DragFloatRange2()																																						{ /* TODO: DragFloatRange2(...) ==> UNSUPPORTED */ }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v)																												{ bool used = ImGui::DragInt(label.c_str(), &v); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v, float v_speed)																								{ bool used = ImGui::DragInt(label.c_str(), &v, v_speed); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v, float v_speed, int v_min)																						{ bool used = ImGui::DragInt(label.c_str(), &v, v_speed, v_min); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v, float v_speed, int v_min, int v_max)																			{ bool used = ImGui::DragInt(label.c_str(), &v, v_speed, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v, float v_speed, int v_min, int v_max, const std::string& format)												{ bool used = ImGui::DragInt(label.c_str(), &v, v_speed, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> DragInt(const std::string& label, int v, float v_speed, int v_min, int v_max, const std::string& format, int flags)									{ bool used = ImGui::DragInt(label.c_str(), &v, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v, used); }
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value, v_speed);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v, float v_speed, int v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value, v_speed, v_min);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt2(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::DragInt2(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value, v_speed);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v, float v_speed, int v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value, v_speed, v_min);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt3(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::DragInt3(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v, float v_speed)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value, v_speed);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v, float v_speed, int v_min)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value, v_speed, v_min);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value, v_speed, v_min, v_max);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value, v_speed, v_min, v_max, format.c_str());

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> DragInt4(const std::string& label, const sol::table& v, float v_speed, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::DragInt4(label.c_str(), value, v_speed, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline void DragIntRange2()																																							{ /* TODO: DragIntRange2(...) ==> UNSUPPORTED */ }
	inline void DragScalar()																																							{ /* TODO: DragScalar(...) ==> UNSUPPORTED */ }
	inline void DragScalarN()																																							{ /* TODO: DragScalarN(...) ==> UNSUPPORTED */ }

	// Widgets: Sliders
	inline std::tuple<float, bool> SliderFloat(const std::string& label, float v, float v_min, float v_max)																				{ bool used = ImGui::SliderFloat(label.c_str(), &v, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> SliderFloat(const std::string& label, float v, float v_min, float v_max, const std::string& format)													{ bool used = ImGui::SliderFloat(label.c_str(), &v, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> SliderFloat(const std::string& label, float v, float v_min, float v_max, const std::string& format, int flags)										{ bool used = ImGui::SliderFloat(label.c_str(), &v, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v, used); }
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat2(const std::string& label, const sol::table& v, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::SliderFloat2(label.c_str(), value, v_min, v_max);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat2(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::SliderFloat2(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat2(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::SliderFloat2(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat3(const std::string& label, const sol::table& v, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::SliderFloat3(label.c_str(), value, v_min, v_max);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[3]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat3(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::SliderFloat3(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[3]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat3(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::SliderFloat3(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[3]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat4(const std::string& label, const sol::table& v, float v_min, float v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::SliderFloat4(label.c_str(), value, v_min, v_max);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat4(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::SliderFloat4(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> SliderFloat4(const std::string& label, const sol::table& v, float v_min, float v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::SliderFloat4(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<float, bool> SliderAngle(const std::string& label, float v_rad)																									{ bool used = ImGui::SliderAngle(label.c_str(), &v_rad); return std::make_tuple(v_rad, used); }
	inline std::tuple<float, bool> SliderAngle(const std::string& label, float v_rad, float v_degrees_min)																				{ bool used = ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min); return std::make_tuple(v_rad, used); }
	inline std::tuple<float, bool> SliderAngle(const std::string& label, float v_rad, float v_degrees_min, float v_degrees_max)															{ bool used = ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min, v_degrees_max); return std::make_tuple(v_rad, used); }
	inline std::tuple<float, bool> SliderAngle(const std::string& label, float v_rad, float v_degrees_min, float v_degrees_max, const std::string& format)								{ bool used = ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min, v_degrees_max, format.c_str()); return std::make_tuple(v_rad, used); }
	inline std::tuple<float, bool> SliderAngle(const std::string& label, float v_rad, float v_degrees_min, float v_degrees_max, const std::string& format, int flags)					{ bool used = ImGui::SliderAngle(label.c_str(), &v_rad, v_degrees_min, v_degrees_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v_rad, used); }
	inline std::tuple<int, bool> SliderInt(const std::string& label, int v, int v_min, int v_max)																						{ bool used = ImGui::SliderInt(label.c_str(), &v, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> SliderInt(const std::string& label, int v, int v_min, int v_max, const std::string& format)															{ bool used = ImGui::SliderInt(label.c_str(), &v, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> SliderInt(const std::string& label, int v, int v_min, int v_max, const std::string& format, int flags)													{ bool used = ImGui::SliderInt(label.c_str(), &v, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v, used); }
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt2(const std::string& label, const sol::table& v, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::SliderInt2(label.c_str(), value, v_min, v_max);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt2(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::SliderInt2(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt2(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::SliderInt2(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt3(const std::string& label, const sol::table& v, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::SliderInt3(label.c_str(), value, v_min, v_max);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt3(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::SliderInt3(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt3(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::SliderInt3(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt4(const std::string& label, const sol::table& v, int v_min, int v_max)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::SliderInt4(label.c_str(), value, v_min, v_max);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt4(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::SliderInt4(label.c_str(), value, v_min, v_max, format.c_str());

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<int>>, bool> SliderInt4(const std::string& label, const sol::table& v, int v_min, int v_max, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::SliderInt4(label.c_str(), value, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline void SliderScalar()																																							{ /* TODO: SliderScalar(...) ==> UNSUPPORTED */ }
	inline void SliderScalarN()																																							{ /* TODO: SliderScalarN(...) ==> UNSUPPORTED */ }
	inline std::tuple<float, bool> VSliderFloat(const std::string& label, float sizeX, float sizeY, float v, float v_min, float v_max)													{ bool used = ImGui::VSliderFloat(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> VSliderFloat(const std::string& label, float sizeX, float sizeY, float v, float v_min, float v_max, const std::string& format)						{ bool used = ImGui::VSliderFloat(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<float, bool> VSliderFloat(const std::string& label, float sizeX, float sizeY, float v, float v_min, float v_max, const std::string& format, int flags)			{ bool used = ImGui::VSliderFloat(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> VSliderInt(const std::string& label, float sizeX, float sizeY, int v, int v_min, int v_max)															{ bool used = ImGui::VSliderInt(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> VSliderInt(const std::string& label, float sizeX, float sizeY, int v, int v_min, int v_max, const std::string& format)									{ bool used = ImGui::VSliderInt(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max, format.c_str()); return std::make_tuple(v, used); }
	inline std::tuple<int, bool> VSliderInt(const std::string& label, float sizeX, float sizeY, int v, int v_min, int v_max, const std::string& format, int flags)						{ bool used = ImGui::VSliderInt(label.c_str(), { sizeX, sizeY }, &v, v_min, v_max, format.c_str(), (ImGuiSliderFlags)flags); return std::make_tuple(v, used); }
	inline void VSliderScalar()																																							{ /* TODO: VSliderScalar(...) ==> UNSUPPORTED */ }

	// Widgets: Input with Keyboard
	inline std::tuple<std::string, bool> InputText(const std::string& label, std::string text)																							{ bool selected = ImGui::InputText(label.c_str(), &text); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputText(const std::string& label, std::string text, int flags)																				{ bool selected = ImGui::InputText(label.c_str(), &text, static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputTextMultiline(const std::string& label, std::string text)																					{ bool selected = ImGui::InputTextMultiline(label.c_str(), &text); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputTextMultiline(const std::string& label, std::string text, float sizeX, float sizeY)														{ bool selected = ImGui::InputTextMultiline(label.c_str(), &text, { sizeX, sizeY }); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputTextMultiline(const std::string& label, std::string text, float sizeX, float sizeY, int flags)											{ bool selected = ImGui::InputTextMultiline(label.c_str(), &text, { sizeX, sizeY }, static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputTextWithHint(const std::string& label, const std::string& hint, std::string text)															{ bool selected = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), &text); return std::make_tuple(text, selected); }
	inline std::tuple<std::string, bool> InputTextWithHint(const std::string& label, const std::string& hint, std::string text, int flags)												{ bool selected = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), &text, static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(text, selected); }
	inline std::tuple<float, bool> InputFloat(const std::string& label, float v)																										{ bool selected = ImGui::InputFloat(label.c_str(), &v); return std::make_tuple(v, selected); }
	inline std::tuple<float, bool> InputFloat(const std::string& label, float v, float step)																							{ bool selected = ImGui::InputFloat(label.c_str(), &v, step); return std::make_tuple(v, selected); }
	inline std::tuple<float, bool> InputFloat(const std::string& label, float v, float step, float step_fast)																			{ bool selected = ImGui::InputFloat(label.c_str(), &v, step, step_fast); return std::make_tuple(v, selected); }
	inline std::tuple<float, bool> InputFloat(const std::string& label, float v, float step, float step_fast, const std::string& format)												{ bool selected = ImGui::InputFloat(label.c_str(), &v, step, step_fast, format.c_str()); return std::make_tuple(v, selected); }
	inline std::tuple<float, bool> InputFloat(const std::string& label, float v, float step, float step_fast, const std::string& format, int flags)										{ bool selected = ImGui::InputFloat(label.c_str(), &v, step, step_fast, format.c_str(), static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(v, selected); }
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat2(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::InputFloat2(label.c_str(), value);

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat2(const std::string& label, const sol::table& v, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::InputFloat2(label.c_str(), value, format.c_str());

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat2(const std::string& label, const sol::table& v, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[2] = { float(v1), float(v2) };
		bool used = ImGui::InputFloat2(label.c_str(), value, format.c_str(), static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t float2 = sol::as_table(std::vector<float>{
			value[0], value[1]
		});

		return std::make_tuple(float2, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat3(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::InputFloat3(label.c_str(), value);

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat3(const std::string& label, const sol::table& v, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::InputFloat3(label.c_str(), value, format.c_str());

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat3(const std::string& label, const sol::table& v, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[3] = { float(v1), float(v2), float(v3) };
		bool used = ImGui::InputFloat3(label.c_str(), value, format.c_str(), static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t float3 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(float3, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat4(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::InputFloat4(label.c_str(), value);

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat4(const std::string& label, const sol::table& v, const std::string& format)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::InputFloat4(label.c_str(), value, format.c_str());

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<float>>, bool> InputFloat4(const std::string& label, const sol::table& v, const std::string& format, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float value[4] = { float(v1), float(v2), float(v3), float(v4) };
		bool used = ImGui::InputFloat4(label.c_str(), value, format.c_str(), static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t float4 = sol::as_table(std::vector<float>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(float4, used);
	}
	inline std::tuple<int, bool> InputInt(const std::string& label, int v)																												{ bool selected = ImGui::InputInt(label.c_str(), &v); return std::make_tuple(v, selected); }
	inline std::tuple<int, bool> InputInt(const std::string& label, int v, int step)																									{ bool selected = ImGui::InputInt(label.c_str(), &v, step); return std::make_tuple(v, selected); }
	inline std::tuple<int, bool> InputInt(const std::string& label, int v, int step, int step_fast)																						{ bool selected = ImGui::InputInt(label.c_str(), &v, step, step_fast); return std::make_tuple(v, selected); }
	inline std::tuple<int, bool> InputInt(const std::string& label, int v, int step, int step_fast, int flags)																			{ bool selected = ImGui::InputInt(label.c_str(), &v, step, step_fast, static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(v, selected); }
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt2(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::InputInt2(label.c_str(), value);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt2(const std::string& label, const sol::table& v, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[2] = { int(v1), int(v2) };
		bool used = ImGui::InputInt2(label.c_str(), value, static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			value[0], value[1]
		});

		return std::make_tuple(int2, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt3(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::InputInt3(label.c_str(), value);

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt3(const std::string& label, const sol::table& v, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[3] = { int(v1), int(v2), int(v3) };
		bool used = ImGui::InputInt3(label.c_str(), value, static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t int3 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2]
		});

		return std::make_tuple(int3, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt4(const std::string& label, const sol::table& v)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::InputInt4(label.c_str(), value);

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple <sol::as_table_t<std::vector<int>>, bool> InputInt4(const std::string& label, const sol::table& v, int flags)
	{
		const lua_Number	v1{ v[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v2{ v[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v3{ v[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							v4{ v[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		int value[4] = { int(v1), int(v2), int(v3), int(v4) };
		bool used = ImGui::InputInt4(label.c_str(), value, static_cast<ImGuiInputTextFlags>(flags));

		sol::as_table_t int4 = sol::as_table(std::vector<int>{
			value[0], value[1], value[2], value[3]
		});

		return std::make_tuple(int4, used);
	}
	inline std::tuple<double, bool> InputDouble(const std::string& label, double v)																										{ bool selected = ImGui::InputDouble(label.c_str(), &v); return std::make_tuple(v, selected); }
	inline std::tuple<double, bool> InputDouble(const std::string& label, double v, double step)																						{ bool selected = ImGui::InputDouble(label.c_str(), &v, step); return std::make_tuple(v, selected); }
	inline std::tuple<double, bool> InputDouble(const std::string& label, double v, double step, double step_fast)																		{ bool selected = ImGui::InputDouble(label.c_str(), &v, step, step_fast); return std::make_tuple(v, selected); }
	inline std::tuple<double, bool> InputDouble(const std::string& label, double v, double step, double step_fast, const std::string& format)											{ bool selected = ImGui::InputDouble(label.c_str(), &v, step, step_fast, format.c_str()); return std::make_tuple(v, selected); }
	inline std::tuple<double, bool> InputDouble(const std::string& label, double v, double step, double step_fast, const std::string& format, int flags)								{ bool selected = ImGui::InputDouble(label.c_str(), &v, step, step_fast, format.c_str(), static_cast<ImGuiInputTextFlags>(flags)); return std::make_tuple(v, selected); }
	inline void InputScalar()																																							{ /* TODO: InputScalar(...) ==> UNSUPPORTED */ }
	inline void InputScalarN()																																							{ /* TODO: InputScalarN(...) ==> UNSUPPORTED */ }

	// Widgets: Color Editor / Picker
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorEdit3(const std::string& label, const sol::table& col)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
			b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[3] = { float(r), float(g), float(b) };
		bool used = ImGui::ColorEdit3(label.c_str(), color);

		sol::as_table_t rgb = sol::as_table(std::vector<float>{
			color[0], color[1], color[2]
		});

		return std::make_tuple(rgb, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorEdit3(const std::string& label, const sol::table& col, int flags)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[3] = { float(r), float(g), float(b) };
		bool used = ImGui::ColorEdit3(label.c_str(), color, static_cast<ImGuiColorEditFlags>(flags));

		sol::as_table_t rgb = sol::as_table(std::vector<float>{
			color[0], color[1], color[2]
		});

		return std::make_tuple(rgb, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorEdit4(const std::string& label, const sol::table& col)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[4] = { float(r), float(g), float(b), float(a) };
		bool used = ImGui::ColorEdit4(label.c_str(), color);

		sol::as_table_t rgba = sol::as_table(std::vector<float>{
			color[0], color[1], color[2], color[3]
		});

		return std::make_tuple(rgba, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorEdit4(const std::string& label, const sol::table& col, int flags)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[4] = { float(r), float(g), float(b), float(a) };
		bool used = ImGui::ColorEdit4(label.c_str(), color, static_cast<ImGuiColorEditFlags>(flags));

		sol::as_table_t rgba = sol::as_table(std::vector<float>{
			color[0], color[1], color[2], color[3]
		});

		return std::make_tuple(rgba, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorPicker3(const std::string& label, const sol::table& col)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[3] = { float(r), float(g), float(b) };
		bool used = ImGui::ColorPicker3(label.c_str(), color);

		sol::as_table_t rgb = sol::as_table(std::vector<float>{
			color[0], color[1], color[2]
		});

		return std::make_tuple(rgb, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorPicker3(const std::string& label, const sol::table& col, int flags)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[3] = { float(r), float(g), float(b) };
		bool used = ImGui::ColorPicker3(label.c_str(), color, static_cast<ImGuiColorEditFlags>(flags));

		sol::as_table_t rgb = sol::as_table(std::vector<float>{
			color[0], color[1], color[2]
		});

		return std::make_tuple(rgb, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorPicker4(const std::string& label, const sol::table& col)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[4] = { float(r), float(g), float(b), float(a) };
		bool used = ImGui::ColorPicker4(label.c_str(), color);

		sol::as_table_t rgba = sol::as_table(std::vector<float>{
			color[0], color[1], color[2], color[3]
		});

		return std::make_tuple(rgba, used);
	}
	inline std::tuple<sol::as_table_t<std::vector<float>>, bool> ColorPicker4(const std::string& label, const sol::table& col, int flags)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		float color[4] = { float(r), float(g), float(b), float(a) };
		bool used = ImGui::ColorPicker4(label.c_str(), color, static_cast<ImGuiColorEditFlags>(flags));

		sol::as_table_t rgba = sol::as_table(std::vector<float>{
			color[0], color[1], color[2], color[3]
		});

		return std::make_tuple(rgba, used);
	}
	inline bool ColorButton(const std::string& desc_id, const sol::table& col)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		const ImVec4 color{ float(r), float(g), float(b), float(a) };
		return ImGui::ColorButton(desc_id.c_str(), color);
	}
	inline bool ColorButton(const std::string& desc_id, const sol::table& col, int flags)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		const ImVec4 color{ float(r), float(g), float(b), float(a) };
		return ImGui::ColorButton(desc_id.c_str(), color, static_cast<ImGuiColorEditFlags>(flags));
	}
	inline bool ColorButton(const std::string& desc_id, const sol::table& col, int flags, float sizeX, float sizeY)
	{
		const lua_Number	r{ col[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ col[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ col[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ col[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		const ImVec4 color{ float(r), float(g), float(b), float(a) };
		return ImGui::ColorButton(desc_id.c_str(), color, static_cast<ImGuiColorEditFlags>(flags), { sizeX, sizeY });
	}
	inline void SetColorEditOptions(int flags)																																			{ ImGui::SetColorEditOptions(static_cast<ImGuiColorEditFlags>(flags)); }

	// Widgets: Trees
	inline bool TreeNode(const std::string& label)														{ return ImGui::TreeNode(label.c_str()); }
	inline bool TreeNode(const std::string& label, const std::string& fmt)								{ return ImGui::TreeNode(label.c_str(), fmt.c_str()); }
	/* TODO: TreeNodeV(...) (2) ==> UNSUPPORTED */
	inline bool TreeNodeEx(const std::string& label)													{ return ImGui::TreeNodeEx(label.c_str()); }
	inline bool TreeNodeEx(const std::string& label, int flags)											{ return ImGui::TreeNodeEx(label.c_str(), static_cast<ImGuiTreeNodeFlags>(flags)); }
	inline bool TreeNodeEx(const std::string& label, int flags, const std::string& fmt)					{ return ImGui::TreeNodeEx(label.c_str(), static_cast<ImGuiTreeNodeFlags>(flags), fmt.c_str()); }
	/* TODO: TreeNodeExV(...) (2) ==> UNSUPPORTED */
	inline void TreePush(const std::string& str_id)														{ ImGui::TreePush(str_id.c_str()); }
	/* TODO: TreePush(const void*) ==> UNSUPPORTED */
	inline void TreePop()																				{ ImGui::TreePop(); }
	inline float GetTreeNodeToLabelSpacing()															{ return ImGui::GetTreeNodeToLabelSpacing(); }
	inline bool CollapsingHeader(const std::string& label)												{ return ImGui::CollapsingHeader(label.c_str()); }
	inline bool CollapsingHeader(const std::string& label, int flags)									{ return ImGui::CollapsingHeader(label.c_str(), static_cast<ImGuiTreeNodeFlags>(flags)); }
	inline std::tuple<bool, bool> CollapsingHeader(const std::string& label, bool open)					{ bool notCollapsed = ImGui::CollapsingHeader(label.c_str(), &open); return std::make_tuple(open, notCollapsed); }
	inline std::tuple<bool, bool> CollapsingHeader(const std::string& label, bool open, int flags)		{ bool notCollapsed = ImGui::CollapsingHeader(label.c_str(), &open, static_cast<ImGuiTreeNodeFlags>(flags)); return std::make_tuple(open, notCollapsed); }
	inline void SetNextItemOpen(bool is_open)															{ ImGui::SetNextItemOpen(is_open); }
	inline void SetNextItemOpen(bool is_open, int cond)													{ ImGui::SetNextItemOpen(is_open, static_cast<ImGuiCond>(cond)); }

	// Widgets: Selectables
	// TODO: Only one of Selectable variations is possible due to same parameters for Lua
	inline bool Selectable(const std::string& label)													{ return ImGui::Selectable(label.c_str()); }
	inline bool Selectable(const std::string& label, bool selected)										{ ImGui::Selectable(label.c_str(), &selected); return selected; }
	inline bool Selectable(const std::string& label, bool selected, int flags)							{ ImGui::Selectable(label.c_str(), &selected, static_cast<ImGuiSelectableFlags>(flags)); return selected; }
	inline bool Selectable(const std::string& label, bool selected, int flags, float sizeX, float sizeY){ ImGui::Selectable(label.c_str(), &selected, static_cast<ImGuiSelectableFlags>(flags), { sizeX, sizeY }); return selected; }

	// Widgets: List Boxes
	inline std::tuple<int, bool> ListBox(const std::string& label, int current_item, const sol::table& items, int items_count)
	{
		std::vector<std::string> strings;
		for (int i{ 1 }; i <= items_count; i++)
		{
			const auto& stringItem = items.get<sol::optional<std::string>>(i);
			strings.push_back(stringItem.value_or("Missing"));
		}

		std::vector<const char*> cstrings;
		for (auto& string : strings)
			cstrings.push_back(string.c_str());

		bool clicked = ImGui::ListBox(label.c_str(), &current_item, cstrings.data(), items_count);
		return std::make_tuple(current_item, clicked);
	}
	inline std::tuple<int, bool> ListBox(const std::string& label, int current_item, const sol::table& items, int items_count, int height_in_items)
	{
		std::vector<std::string> strings;
		for (int i{ 1 }; i <= items_count; i++)
		{
			const auto& stringItem = items.get<sol::optional<std::string>>(i);
			strings.push_back(stringItem.value_or("Missing"));
		}

		std::vector<const char*> cstrings;
		for (auto& string : strings)
			cstrings.push_back(string.c_str());

		bool clicked = ImGui::ListBox(label.c_str(), &current_item, cstrings.data(), items_count, height_in_items);
		return std::make_tuple(current_item, clicked);
	}
	inline bool BeginListBox(const std::string& label, float sizeX, float sizeY)						{ return ImGui::BeginListBox(label.c_str(), { sizeX, sizeY }); }
	inline bool BeginListBox(const std::string& label)													{ return ImGui::BeginListBox(label.c_str()); }
	inline void EndListBox()																			{ ImGui::EndListBox(); }

	// Widgets: Data Plotting
	/* TODO: Widgets Data Plotting ==> UNSUPPORTED (barely used and quite long functions) */

	// Widgets: Value() helpers
	inline void Value(const std::string& prefix, bool b)												{ ImGui::Value(prefix.c_str(), b); }
	inline void Value(const std::string& prefix, int v)													{ ImGui::Value(prefix.c_str(), v); }
	inline void Value(const std::string& prefix, unsigned int v)										{ ImGui::Value(prefix.c_str(), v); }
	inline void Value(const std::string& prefix, float v)												{ ImGui::Value(prefix.c_str(), v); }
	inline void Value(const std::string& prefix, float v, const std::string& float_format)				{ ImGui::Value(prefix.c_str(), v, float_format.c_str()); }

	// Widgets: Menus
	inline bool BeginMenuBar()																			{ return ImGui::BeginMenuBar(); }
	inline void EndMenuBar()																			{ ImGui::EndMenuBar(); }
	inline bool BeginMainMenuBar()																		{ return ImGui::BeginMainMenuBar(); }
	inline void EndMainMenuBar()																		{ ImGui::EndMainMenuBar(); }
	inline bool BeginMenu(const std::string& label)														{ return ImGui::BeginMenu(label.c_str()); }
	inline bool BeginMenu(const std::string& label, bool enabled)										{ return ImGui::BeginMenu(label.c_str(), enabled); }
	inline void EndMenu()																				{ ImGui::EndMenu(); }
	inline bool MenuItem(const std::string& label)																					{ return ImGui::MenuItem(label.c_str()); }
	inline bool MenuItem(const std::string& label, const std::string& shortcut)														{ return ImGui::MenuItem(label.c_str(), shortcut.c_str()); }
	inline std::tuple<bool, bool> MenuItem(const std::string& label, const std::string& shortcut, bool selected)					{ bool activated = ImGui::MenuItem(label.c_str(), shortcut.c_str(), &selected); return std::make_tuple(selected, activated); }
	inline std::tuple<bool, bool> MenuItem(const std::string& label, const std::string& shortcut, bool selected, bool enabled)		{ bool activated = ImGui::MenuItem(label.c_str(), shortcut.c_str(), &selected, enabled); return std::make_tuple(selected, activated); }

	// Tooltips
	inline void BeginTooltip()																			{ ImGui::BeginTooltip(); }
	inline void EndTooltip()																			{ ImGui::EndTooltip(); }
	inline void SetTooltip(const std::string& fmt)														{ ImGui::SetTooltip(fmt.c_str()); }
	inline void SetTooltipV()																			{ /* TODO: SetTooltipV(...) ==> UNSUPPORTED */ }

	// Popups, Modals
	inline bool BeginPopup(const std::string& str_id)													{ return ImGui::BeginPopup(str_id.c_str()); }
	inline bool BeginPopup(const std::string& str_id, int flags)										{ return ImGui::BeginPopup(str_id.c_str(), static_cast<ImGuiWindowFlags>(flags)); }
	inline bool BeginPopupModal(const std::string& name)												{ return ImGui::BeginPopupModal(name.c_str()); }
	inline bool BeginPopupModal(const std::string& name, bool open)										{ return ImGui::BeginPopupModal(name.c_str(), &open); }
	inline bool BeginPopupModal(const std::string& name, bool open, int flags)							{ return ImGui::BeginPopupModal(name.c_str(), &open, static_cast<ImGuiWindowFlags>(flags)); }
	inline void EndPopup()																				{ ImGui::EndPopup(); }
	inline void OpenPopup(const std::string& str_id)													{ ImGui::OpenPopup(str_id.c_str()); }
	inline void OpenPopup(const std::string& str_id, int popup_flags)									{ ImGui::OpenPopup(str_id.c_str(), static_cast<ImGuiPopupFlags>(popup_flags)); }
	inline void CloseCurrentPopup()																		{ ImGui::CloseCurrentPopup(); }
	inline bool BeginPopupContextItem()																	{ return ImGui::BeginPopupContextItem(); }
	inline bool BeginPopupContextItem(const std::string& str_id)										{ return ImGui::BeginPopupContextItem(str_id.c_str()); }
	inline bool BeginPopupContextItem(const std::string& str_id, int popup_flags)						{ return ImGui::BeginPopupContextItem(str_id.c_str(), static_cast<ImGuiPopupFlags>(popup_flags)); }
	inline bool BeginPopupContextWindow()																{ return ImGui::BeginPopupContextWindow(); }
	inline bool BeginPopupContextWindow(const std::string& str_id)										{ return ImGui::BeginPopupContextWindow(str_id.c_str()); }
	inline bool BeginPopupContextWindow(const std::string& str_id, int popup_flags)						{ return ImGui::BeginPopupContextWindow(str_id.c_str(), static_cast<ImGuiPopupFlags>(popup_flags)); }
	inline bool BeginPopupContextVoid()																	{ return ImGui::BeginPopupContextVoid(); }
	inline bool BeginPopupContextVoid(const std::string& str_id)										{ return ImGui::BeginPopupContextVoid(str_id.c_str()); }
	inline bool BeginPopupContextVoid(const std::string& str_id, int popup_flags)						{ return ImGui::BeginPopupContextVoid(str_id.c_str(), static_cast<ImGuiPopupFlags>(popup_flags)); }
	inline bool IsPopupOpen(const std::string& str_id)													{ return ImGui::IsPopupOpen(str_id.c_str()); }
	inline bool IsPopupOpen(const std::string& str_id, int popup_flags)									{ return ImGui::IsPopupOpen(str_id.c_str(), popup_flags); }

	// Columns
	inline void Columns()																				{ ImGui::Columns(); }
	inline void Columns(int count)																		{ ImGui::Columns(count); }
	inline void Columns(int count, const std::string& id)												{ ImGui::Columns(count, id.c_str()); }
	inline void Columns(int count, const std::string& id, bool border)									{ ImGui::Columns(count, id.c_str(), border); }
	inline void NextColumn()																			{ ImGui::NextColumn(); }
	inline int GetColumnIndex()																			{ return ImGui::GetColumnIndex(); }
	inline float GetColumnWidth()																		{ return ImGui::GetColumnWidth(); }
	inline float GetColumnWidth(int column_index)														{ return ImGui::GetColumnWidth(column_index); }
	inline void SetColumnWidth(int column_index, float width)											{ ImGui::SetColumnWidth(column_index, width); }
	inline float GetColumnOffset()																		{ return ImGui::GetColumnOffset(); }
	inline float GetColumnOffset(int column_index)														{ return ImGui::GetColumnOffset(column_index); }
	inline void SetColumnOffset(int column_index, float offset_x)										{ ImGui::SetColumnOffset(column_index, offset_x); }
	inline int GetColumnsCount()																		{ return ImGui::GetColumnsCount(); }

	// Tab Bars, Tabs
	inline bool BeginTabBar(const std::string& str_id)													{ return ImGui::BeginTabBar(str_id.c_str()); }
	inline bool BeginTabBar(const std::string& str_id, int flags)										{ return ImGui::BeginTabBar(str_id.c_str(), static_cast<ImGuiTabBarFlags>(flags)); }
	inline void EndTabBar()																				{ ImGui::EndTabBar(); }
	inline bool BeginTabItem(const std::string& label)													{ return ImGui::BeginTabItem(label.c_str()); }
	inline std::tuple<bool, bool> BeginTabItem(const std::string& label, bool open)						{ bool selected = ImGui::BeginTabItem(label.c_str(), &open); return std::make_tuple(open, selected); }
	inline std::tuple<bool, bool> BeginTabItem(const std::string& label, bool open, int flags)			{ bool selected = ImGui::BeginTabItem(label.c_str(), &open, static_cast<ImGuiTabItemFlags>(flags)); return std::make_tuple(open, selected); }
	inline void EndTabItem()																			{ ImGui::EndTabItem(); }
	inline void SetTabItemClosed(const std::string& tab_or_docked_window_label)							{ ImGui::SetTabItemClosed(tab_or_docked_window_label.c_str()); }

	// Docking
	#ifndef IMGUI_NO_DOCKING	// Define IMGUI_NO_DOCKING to disable these for compatibility with ImGui's master branch
	inline void DockSpace(unsigned int id)																{ ImGui::DockSpace(id); }
	inline void DockSpace(unsigned int id, float sizeX, float sizeY)									{ ImGui::DockSpace(id, { sizeX, sizeY }); }
	inline void DockSpace(unsigned int id, float sizeX, float sizeY, int flags)							{ ImGui::DockSpace(id, { sizeX, sizeY }, static_cast<ImGuiDockNodeFlags>(flags)); }
	inline unsigned int DockSpaceOverViewport()															{ return 0; /* TODO: DockSpaceOverViwport(...) ==> UNSUPPORTED */ }
	inline void SetNextWindowDockID(unsigned int dock_id)												{ ImGui::SetNextWindowDockID(dock_id); }
	inline void SetNextWindowDockID(unsigned int dock_id, int cond)										{ ImGui::SetNextWindowDockID(dock_id, static_cast<ImGuiCond>(cond)); }
	inline void SetNextWindowClass()																	{  /* TODO: SetNextWindowClass(...) ==> UNSUPPORTED */ }
	inline unsigned int GetWindowDockID()																{ return ImGui::GetWindowDockID(); }
	inline bool IsWindowDocked()																		{ return ImGui::IsWindowDocked(); }
	#endif

	// Logging
	inline void LogToTTY()																				{ ImGui::LogToTTY(); }
	inline void LogToTTY(int auto_open_depth)															{ ImGui::LogToTTY(auto_open_depth); }
	inline void LogToFile()																				{ ImGui::LogToFile(); }
	inline void LogToFile(int auto_open_depth)															{ ImGui::LogToFile(auto_open_depth); }
	inline void LogToFile(int auto_open_depth, const std::string& filename)								{ ImGui::LogToFile(auto_open_depth, filename.c_str()); }
	inline void LogToClipboard()																		{ ImGui::LogToClipboard(); }
	inline void LogToClipboard(int auto_open_depth)														{ ImGui::LogToClipboard(auto_open_depth); }
	inline void LogFinish()																				{ ImGui::LogFinish(); }
	inline void LogButtons()																			{ ImGui::LogButtons(); }
	inline void LogText(const std::string& fmt)															{ ImGui::LogText(fmt.c_str()); }

	// Drag and Drop
	// TODO: Drag and Drop ==> UNSUPPORTED

	// Clipping
	inline void PushClipRect(float min_x, float min_y, float max_x, float max_y, bool intersect_current) { ImGui::PushClipRect({ min_x, min_y }, { max_x, max_y }, intersect_current); }
	inline void PopClipRect()																			{ ImGui::PopClipRect(); }

	// Focus, Activation
	inline void SetItemDefaultFocus()																	{ ImGui::SetItemDefaultFocus(); }
	inline void SetKeyboardFocusHere()																	{ ImGui::SetKeyboardFocusHere(); }
	inline void SetKeyboardFocusHere(int offset)														{ ImGui::SetKeyboardFocusHere(offset); }

	// Item/Widgets Utilities
	inline bool IsItemHovered()																			{ return ImGui::IsItemHovered(); }
	inline bool IsItemHovered(int flags)																{ return ImGui::IsItemHovered(static_cast<ImGuiHoveredFlags>(flags)); }
	inline bool IsItemActive()																			{ return ImGui::IsItemActive(); }
	inline bool IsItemFocused()																			{ return ImGui::IsItemFocused(); }
	inline bool IsItemClicked()																			{ return ImGui::IsItemClicked(); }
	inline bool IsItemClicked(int mouse_button)															{ return ImGui::IsItemClicked(static_cast<ImGuiMouseButton>(mouse_button)); }
	inline bool IsItemVisible()																			{ return ImGui::IsItemVisible(); }
	inline bool IsItemEdited()																			{ return ImGui::IsItemEdited(); }
	inline bool IsItemActivated()																		{ return ImGui::IsItemActivated(); }
	inline bool IsItemDeactivated()																		{ return ImGui::IsItemDeactivated(); }
	inline bool IsItemDeactivatedAfterEdit()															{ return ImGui::IsItemDeactivatedAfterEdit(); }
	inline bool IsItemToggledOpen()																		{ return ImGui::IsItemToggledOpen(); }
	inline bool IsAnyItemHovered()																		{ return ImGui::IsAnyItemHovered(); }
	inline bool IsAnyItemActive()																		{ return ImGui::IsAnyItemActive(); }
	inline bool IsAnyItemFocused()																		{ return ImGui::IsAnyItemFocused(); }
	inline std::tuple<float, float> GetItemRectMin()													{ const auto vec2{ ImGui::GetItemRectMin() }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetItemRectMax()													{ const auto vec2{ ImGui::GetItemRectMax() }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetItemRectSize()													{ const auto vec2{ ImGui::GetItemRectSize() }; return std::make_tuple(vec2.x, vec2.y); }
	inline void SetNextItemAllowOverlap()																{ ImGui::SetNextItemAllowOverlap(); }

	// Miscellaneous Utilities
	inline bool IsRectVisible(float sizeX, float sizeY)													{ return ImGui::IsRectVisible({ sizeX, sizeY }); }
	inline bool IsRectVisible(float minX, float minY, float maxX, float maxY)							{ return ImGui::IsRectVisible({ minX, minY }, { maxX, maxY }); }
	inline double GetTime()																				{ return ImGui::GetTime(); }
	inline int GetFrameCount()																			{ return ImGui::GetFrameCount(); }
	/* TODO: GetBackgroundDrawList(), GetForeGroundDrawList(), GetDrawListSharedData() ==> UNSUPPORTED */
	inline std::string GetStyleColorName(int idx)														{ return std::string(ImGui::GetStyleColorName(static_cast<ImGuiCol>(idx))); }
	/* TODO: SetStateStorage(), GetStateStorage(), CalcListClipping() ==> UNSUPPORTED */
	//inline bool BeginChild(unsigned int id, float sizeX, float sizeY)								{ return ImGui::BeginChild(id, { sizeX, sizeY }); }
	//inline bool BeginChild(unsigned int id, float sizeX, float sizeY, int flags)					{ return ImGui::BeginChild(id, { sizeX, sizeY }, static_cast<ImGuiWindowFlags>(flags)); }
	//inline void EndChild()																			{ return ImGui::EndChild(); }

	// Text Utilities
	inline std::tuple<float, float> CalcTextSize(const std::string& text)																					{ const auto vec2{ ImGui::CalcTextSize(text.c_str()) }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> CalcTextSize(const std::string& text, const std::string& text_end)														{ const auto vec2{ ImGui::CalcTextSize(text.c_str(), text_end.c_str()) }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> CalcTextSize(const std::string& text, const std::string& text_end, bool hide_text_after_double_hash)					{ const auto vec2{ ImGui::CalcTextSize(text.c_str(), text_end.c_str(), hide_text_after_double_hash) }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> CalcTextSize(const std::string& text, const std::string& text_end, bool hide_text_after_double_hash, float wrap_width)	{ const auto vec2{ ImGui::CalcTextSize(text.c_str(), text_end.c_str(), hide_text_after_double_hash, wrap_width) }; return std::make_tuple(vec2.x, vec2.y); }

	// Color Utilities
	inline sol::as_table_t<std::vector<float>> ColorConvertU32ToFloat4(unsigned int in)
	{
		const auto vec4 = ImGui::ColorConvertU32ToFloat4(in);
		sol::as_table_t rgba = sol::as_table(std::vector<float>{
			vec4.x, vec4.y, vec4.z, vec4.w
		});

		return rgba;
	}
	inline unsigned int ColorConvertFloat4ToU32(const sol::table& rgba)
	{
		const lua_Number	r{ rgba[1].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							g{ rgba[2].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							b{ rgba[3].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) },
							a{ rgba[4].get<std::optional<lua_Number>>().value_or(static_cast<lua_Number>(0)) };
		
		return ImGui::ColorConvertFloat4ToU32({ float(r), float(g), float(b), float(a) });
	}

	inline std::tuple<float, float, float> ColorConvertRGBtoHSV(float r, float g, float b)
	{
		float h{}, s{}, v{};
		ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
		return std::make_tuple(h, s, v);
	}
	inline std::tuple<float, float, float> ColorConvertHSVtoRGB(float h, float s, float v)
	{
		float r{}, g{}, b{};
		ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
		return std::make_tuple(r, g, b);
	}

	// Inputs Utilities: Keyboard
	//inline int GetKeyIndex(int imgui_key)																{ return ImGui::GetKeyIndex(static_cast<ImGuiKey>(imgui_key)); }
	inline bool IsKeyDown(int user_key_index)															{ return ImGui::IsKeyDown((ImGuiKey)user_key_index); }
	inline bool IsKeyPressed(int user_key_index)														{ return ImGui::IsKeyPressed((ImGuiKey)user_key_index); }
	inline bool IsKeyPressed(int user_key_index, bool repeat)											{ return ImGui::IsKeyPressed((ImGuiKey)user_key_index, repeat); }
	inline bool IsKeyReleased(int user_key_index)														{ return ImGui::IsKeyReleased((ImGuiKey)user_key_index); }
	inline int GetKeyPressedAmount(int key_index, float repeat_delay, float rate)						{ return ImGui::GetKeyPressedAmount((ImGuiKey)key_index, repeat_delay, rate); }
	inline void SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard_value)						{ ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard_value); }

	// Inputs Utilities: Mouse
	inline bool IsMouseDown(int button)																	{ return ImGui::IsMouseDown(static_cast<ImGuiMouseButton>(button)); }
	inline bool IsMouseClicked(int button)																{ return ImGui::IsMouseClicked(static_cast<ImGuiMouseButton>(button)); }
	inline bool IsMouseClicked(int button, bool repeat)													{ return ImGui::IsMouseClicked(static_cast<ImGuiMouseButton>(button), repeat); }
	inline bool IsMouseReleased(int button)																{ return ImGui::IsMouseReleased(static_cast<ImGuiMouseButton>(button)); }
	inline bool IsMouseDoubleClicked(int button)														{ return ImGui::IsMouseDoubleClicked(static_cast<ImGuiMouseButton>(button)); }
	inline bool IsMouseHoveringRect(float min_x, float min_y, float max_x, float max_y)					{ return ImGui::IsMouseHoveringRect({ min_x, min_y }, { max_x, max_y }); }
	inline bool IsMouseHoveringRect(float min_x, float min_y, float max_x, float max_y, bool clip)		{ return ImGui::IsMouseHoveringRect({ min_x, min_y }, { max_x, max_y }, clip); }
	inline bool IsMousePosValid()																		{ return false; /* TODO: IsMousePosValid() ==> UNSUPPORTED */ }
	inline bool IsAnyMouseDown()																		{ return ImGui::IsAnyMouseDown(); }
	inline std::tuple<float, float> GetMousePos()														{ const auto vec2{ ImGui::GetMousePos() }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetMousePosOnOpeningCurrentPopup()									{ const auto vec2{ ImGui::GetMousePosOnOpeningCurrentPopup() }; return std::make_tuple(vec2.x, vec2.y); }
	inline bool IsMouseDragging(int button)																{ return ImGui::IsMouseDragging(static_cast<ImGuiMouseButton>(button)); }
	inline bool IsMouseDragging(int button, float lock_threshold)										{ return ImGui::IsMouseDragging(static_cast<ImGuiMouseButton>(button), lock_threshold); }
	inline std::tuple<float, float> GetMouseDragDelta()													{ const auto vec2{ ImGui::GetMouseDragDelta() }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetMouseDragDelta(int button)										{ const auto vec2{ ImGui::GetMouseDragDelta(static_cast<ImGuiMouseButton>(button)) }; return std::make_tuple(vec2.x, vec2.y); }
	inline std::tuple<float, float> GetMouseDragDelta(int button, float lock_threshold)					{ const auto vec2{ ImGui::GetMouseDragDelta(static_cast<ImGuiMouseButton>(button), lock_threshold) }; return std::make_tuple(vec2.x, vec2.y); }
	inline void ResetMouseDragDelta()																	{ ImGui::ResetMouseDragDelta(); }
	inline void ResetMouseDragDelta(int button)															{ ImGui::ResetMouseDragDelta(static_cast<ImGuiMouseButton>(button)); }
	inline int GetMouseCursor()																			{ return ImGui::GetMouseCursor(); }
	inline void SetMouseCursor(int cursor_type)															{ ImGui::SetMouseCursor(static_cast<ImGuiMouseCursor>(cursor_type)); }
	inline void SetNextFrameWantCaptureMouse(bool want_capture_mouse) { ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse); }

	// Clipboard Utilities
	inline std::string GetClipboardText()																{ return std::string(ImGui::GetClipboardText()); }
	inline void SetClipboardText(const std::string& text)												{ ImGui::SetClipboardText(text.c_str()); }
	
// helper to fill enum values.
#define ENUM_HELPER(prefix, val) #val , prefix##_##val
	template <typename SolStateOrView>
	inline void InitEnums(SolStateOrView& lua)
	{
		static_assert( std::is_same_v<SolStateOrView, sol::state> || std::is_same_v<SolStateOrView, sol::state_view>, "sol_ImGui::InitEnums only accepts sol::state& or sol::state_view&");
#pragma region Window Flags
		lua.new_enum("ImGuiWindowFlags",
			ENUM_HELPER(ImGuiWindowFlags, None),
			ENUM_HELPER(ImGuiWindowFlags, NoTitleBar),
			ENUM_HELPER(ImGuiWindowFlags, NoResize),
			ENUM_HELPER(ImGuiWindowFlags, NoMove),
			ENUM_HELPER(ImGuiWindowFlags, NoScrollbar),
			ENUM_HELPER(ImGuiWindowFlags, NoScrollWithMouse),
			ENUM_HELPER(ImGuiWindowFlags, NoCollapse),
			ENUM_HELPER(ImGuiWindowFlags, AlwaysAutoResize),
			ENUM_HELPER(ImGuiWindowFlags, NoBackground),
			ENUM_HELPER(ImGuiWindowFlags, NoSavedSettings),
			ENUM_HELPER(ImGuiWindowFlags, NoMouseInputs),
			ENUM_HELPER(ImGuiWindowFlags, MenuBar),
			ENUM_HELPER(ImGuiWindowFlags, HorizontalScrollbar),
			ENUM_HELPER(ImGuiWindowFlags, NoFocusOnAppearing),
			ENUM_HELPER(ImGuiWindowFlags, NoBringToFrontOnFocus),
			ENUM_HELPER(ImGuiWindowFlags, AlwaysVerticalScrollbar),
			ENUM_HELPER(ImGuiWindowFlags, AlwaysHorizontalScrollbar),
			ENUM_HELPER(ImGuiWindowFlags, NoNavInputs),
			ENUM_HELPER(ImGuiWindowFlags, NoNavFocus),
			ENUM_HELPER(ImGuiWindowFlags, UnsavedDocument),
			#ifndef IMGUI_NO_DOCKING
			,	// Gotta add the comma for correct syntax
			ENUM_HELPER(ImGuiWindowFlags, NoDocking),
			#endif
			ENUM_HELPER(ImGuiWindowFlags, NoNav),
			ENUM_HELPER(ImGuiWindowFlags, NoDecoration),
			ENUM_HELPER(ImGuiWindowFlags, NoInputs),
			ENUM_HELPER(ImGuiWindowFlags, ChildWindow),
			ENUM_HELPER(ImGuiWindowFlags, Tooltip),
			ENUM_HELPER(ImGuiWindowFlags, Popup),
			ENUM_HELPER(ImGuiWindowFlags, Modal),
			ENUM_HELPER(ImGuiWindowFlags, ChildMenu)
			#ifndef IMGUI_NO_DOCKING
			,
			ENUM_HELPER(ImGuiWindowFlags, DockNodeHost)
			#endif
		);
#pragma endregion Window Flags

#pragma region Child Flags
		lua.new_enum("ImGuiChildFlags",
			ENUM_HELPER(ImGuiChildFlags, None),
			ENUM_HELPER(ImGuiChildFlags, Border),
			ENUM_HELPER(ImGuiChildFlags, AlwaysUseWindowPadding),
			ENUM_HELPER(ImGuiChildFlags, ResizeX),
			ENUM_HELPER(ImGuiChildFlags, ResizeY),
			ENUM_HELPER(ImGuiChildFlags, AutoResizeX),
			ENUM_HELPER(ImGuiChildFlags, AutoResizeY),
			ENUM_HELPER(ImGuiChildFlags, AlwaysAutoResize),
			ENUM_HELPER(ImGuiChildFlags, FrameStyle),
			ENUM_HELPER(ImGuiChildFlags, NavFlattened)
		);
#pragma endregion Child Flags

#pragma region Item Flags
		lua.new_enum("ImGuiItemFlags",
			ENUM_HELPER(ImGuiItemFlags, None),
			ENUM_HELPER(ImGuiItemFlags, NoTabStop),
			ENUM_HELPER(ImGuiItemFlags, NoNav),
			ENUM_HELPER(ImGuiItemFlags, NoNavDefaultFocus),
			ENUM_HELPER(ImGuiItemFlags, ButtonRepeat),
			ENUM_HELPER(ImGuiItemFlags, AutoClosePopups)
		);

#pragma endregion Item Flags

#pragma region InputText Flags
		lua.new_enum("ImGuiInputTextFlags",
			ENUM_HELPER(ImGuiInputTextFlags, None),
			ENUM_HELPER(ImGuiInputTextFlags, CharsDecimal),
			ENUM_HELPER(ImGuiInputTextFlags, CharsHexadecimal),
			ENUM_HELPER(ImGuiInputTextFlags, CharsScientific),
			ENUM_HELPER(ImGuiInputTextFlags, CharsUppercase),
			ENUM_HELPER(ImGuiInputTextFlags, CharsNoBlank),
			ENUM_HELPER(ImGuiInputTextFlags, AllowTabInput),
			ENUM_HELPER(ImGuiInputTextFlags, EnterReturnsTrue),
			ENUM_HELPER(ImGuiInputTextFlags, EscapeClearsAll),
			ENUM_HELPER(ImGuiInputTextFlags, CtrlEnterForNewLine),
			ENUM_HELPER(ImGuiInputTextFlags, ReadOnly),
			ENUM_HELPER(ImGuiInputTextFlags, Password),
			ENUM_HELPER(ImGuiInputTextFlags, AlwaysOverwrite),
			ENUM_HELPER(ImGuiInputTextFlags, AutoSelectAll),
			ENUM_HELPER(ImGuiInputTextFlags, ParseEmptyRefVal),
			ENUM_HELPER(ImGuiInputTextFlags, DisplayEmptyRefVal),
			ENUM_HELPER(ImGuiInputTextFlags, NoHorizontalScroll),
			ENUM_HELPER(ImGuiInputTextFlags, NoUndoRedo),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackCompletion),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackHistory),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackAlways),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackCharFilter),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackResize),
			ENUM_HELPER(ImGuiInputTextFlags, CallbackEdit)
		);
#pragma endregion InputText Flags

#pragma region TreeNode Flags
		lua.new_enum("ImGuiTreeNodeFlags",
			ENUM_HELPER(ImGuiTreeNodeFlags, None),
			ENUM_HELPER(ImGuiTreeNodeFlags, Selected),
			ENUM_HELPER(ImGuiTreeNodeFlags, Framed),
			ENUM_HELPER(ImGuiTreeNodeFlags, AllowOverlap),
			ENUM_HELPER(ImGuiTreeNodeFlags, NoTreePushOnOpen),
			ENUM_HELPER(ImGuiTreeNodeFlags, NoAutoOpenOnLog),
			ENUM_HELPER(ImGuiTreeNodeFlags, DefaultOpen),
			ENUM_HELPER(ImGuiTreeNodeFlags, OpenOnDoubleClick),
			ENUM_HELPER(ImGuiTreeNodeFlags, OpenOnArrow),
			ENUM_HELPER(ImGuiTreeNodeFlags, Leaf),
			ENUM_HELPER(ImGuiTreeNodeFlags, Bullet),
			ENUM_HELPER(ImGuiTreeNodeFlags, FramePadding),
			ENUM_HELPER(ImGuiTreeNodeFlags, SpanAvailWidth),
			ENUM_HELPER(ImGuiTreeNodeFlags, SpanFullWidth),
			ENUM_HELPER(ImGuiTreeNodeFlags, SpanTextWidth),
			ENUM_HELPER(ImGuiTreeNodeFlags, SpanAllColumns),
			ENUM_HELPER(ImGuiTreeNodeFlags, NavLeftJumpsBackHere),
			ENUM_HELPER(ImGuiTreeNodeFlags, CollapsingHeader)
			//ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 16,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
		);
#pragma endregion TreeNode Flags

#pragma region Popup Flags
		lua.new_enum("ImGuiPopupFlags",
			ENUM_HELPER(ImGuiPopupFlags,None),
			ENUM_HELPER(ImGuiPopupFlags,MouseButtonLeft),
			ENUM_HELPER(ImGuiPopupFlags,MouseButtonRight),
			ENUM_HELPER(ImGuiPopupFlags,MouseButtonMiddle),
			ENUM_HELPER(ImGuiPopupFlags,MouseButtonMask_),
			ENUM_HELPER(ImGuiPopupFlags,MouseButtonDefault_),
			ENUM_HELPER(ImGuiPopupFlags,NoReopen),
			ENUM_HELPER(ImGuiPopupFlags,NoOpenOverExistingPopup),
			ENUM_HELPER(ImGuiPopupFlags,NoOpenOverItems),
			ENUM_HELPER(ImGuiPopupFlags,AnyPopupId),
			ENUM_HELPER(ImGuiPopupFlags,AnyPopupLevel),
			ENUM_HELPER(ImGuiPopupFlags,AnyPopup)
		);
#pragma endregion Popup Flags

#pragma region Selectable Flags
		lua.new_enum("ImGuiSelectableFlags",
			ENUM_HELPER(ImGuiSelectableFlags, None),
			ENUM_HELPER(ImGuiSelectableFlags, NoAutoClosePopups),
			ENUM_HELPER(ImGuiSelectableFlags, SpanAllColumns),
			ENUM_HELPER(ImGuiSelectableFlags, AllowDoubleClick),
			ENUM_HELPER(ImGuiSelectableFlags, Disabled),
			ENUM_HELPER(ImGuiSelectableFlags, AllowOverlap)
		);
#pragma endregion Selectable Flags

#pragma region Combo Flags
		lua.new_enum("ImGuiComboFlags",
			ENUM_HELPER(ImGuiComboFlags, None),
			ENUM_HELPER(ImGuiComboFlags, PopupAlignLeft),
			ENUM_HELPER(ImGuiComboFlags, HeightSmall),
			ENUM_HELPER(ImGuiComboFlags, HeightRegular),
			ENUM_HELPER(ImGuiComboFlags, HeightLarge),
			ENUM_HELPER(ImGuiComboFlags, HeightLargest),
			ENUM_HELPER(ImGuiComboFlags, NoArrowButton),
			ENUM_HELPER(ImGuiComboFlags, NoPreview),
			ENUM_HELPER(ImGuiComboFlags, WidthFitPreview),
			ENUM_HELPER(ImGuiComboFlags, HeightMask_)
		);
#pragma endregion Combo Flags

#pragma region TabBar Flags
		lua.new_enum("ImGuiTabBarFlags",
			ENUM_HELPER(ImGuiTabBarFlags, None),
			ENUM_HELPER(ImGuiTabBarFlags, Reorderable),
			ENUM_HELPER(ImGuiTabBarFlags, AutoSelectNewTabs),
			ENUM_HELPER(ImGuiTabBarFlags, TabListPopupButton),
			ENUM_HELPER(ImGuiTabBarFlags, NoCloseWithMiddleMouseButton),
			ENUM_HELPER(ImGuiTabBarFlags, NoTabListScrollingButtons),
			ENUM_HELPER(ImGuiTabBarFlags, NoTooltip),
			ENUM_HELPER(ImGuiTabBarFlags, DrawSelectedOverline),
			ENUM_HELPER(ImGuiTabBarFlags, FittingPolicyResizeDown),
			ENUM_HELPER(ImGuiTabBarFlags, FittingPolicyScroll),
			ENUM_HELPER(ImGuiTabBarFlags, FittingPolicyMask_),
			ENUM_HELPER(ImGuiTabBarFlags, FittingPolicyDefault_)
		);
#pragma endregion TabBar Flags

#pragma region TabItem Flags
		lua.new_enum("ImGuiTabItemFlags",
			ENUM_HELPER(ImGuiTabItemFlags, None),
			ENUM_HELPER(ImGuiTabItemFlags, UnsavedDocument),
			ENUM_HELPER(ImGuiTabItemFlags, SetSelected),
			ENUM_HELPER(ImGuiTabItemFlags, NoCloseWithMiddleMouseButton),
			ENUM_HELPER(ImGuiTabItemFlags, NoPushId),
			ENUM_HELPER(ImGuiTabItemFlags, NoTooltip),
			ENUM_HELPER(ImGuiTabItemFlags, NoReorder),
			ENUM_HELPER(ImGuiTabItemFlags, Leading),
			ENUM_HELPER(ImGuiTabItemFlags, Trailing),
			ENUM_HELPER(ImGuiTabItemFlags, NoAssumedClosure)
		);
#pragma endregion TabItem Flags

#pragma region Focused Flags
		lua.new_enum("ImGuiFocusedFlags",
			ENUM_HELPER(ImGuiFocusedFlags, None),
			ENUM_HELPER(ImGuiFocusedFlags, ChildWindows),
			ENUM_HELPER(ImGuiFocusedFlags, RootWindow),
			ENUM_HELPER(ImGuiFocusedFlags, AnyWindow),
			ENUM_HELPER(ImGuiFocusedFlags, NoPopupHierarchy),
			#ifndef IMGUI_NO_DOCKING
			ENUM_HELPER(ImGuiFocusedFlags, DockHierarchy),
			#endif
			ENUM_HELPER(ImGuiFocusedFlags, RootAndChildWindows)
		);
#pragma endregion Focused Flags

#pragma region Hovered Flags
		lua.new_enum("ImGuiHoveredFlags",
			ENUM_HELPER(ImGuiHoveredFlags, None),
			ENUM_HELPER(ImGuiHoveredFlags, ChildWindows),
			ENUM_HELPER(ImGuiHoveredFlags, RootWindow),
			ENUM_HELPER(ImGuiHoveredFlags, AnyWindow),
			ENUM_HELPER(ImGuiHoveredFlags, NoPopupHierarchy),
			#ifndef IMGUI_NO_DOCKING
			ENUM_HELPER(ImGuiHoveredFlags, DockHierarchy),
			#endif
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenBlockedByPopup),
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenBlockedByActiveItem),
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenOverlappedByItem),
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenOverlappedByWindow),
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenDisabled),
			ENUM_HELPER(ImGuiHoveredFlags, NoNavOverride),
			ENUM_HELPER(ImGuiHoveredFlags, AllowWhenOverlapped),
			ENUM_HELPER(ImGuiHoveredFlags, RectOnly),
			ENUM_HELPER(ImGuiHoveredFlags, RootAndChildWindows),
			ENUM_HELPER(ImGuiHoveredFlags, ForTooltip),
			ENUM_HELPER(ImGuiHoveredFlags, Stationary),
			ENUM_HELPER(ImGuiHoveredFlags, DelayNone),
			ENUM_HELPER(ImGuiHoveredFlags, DelayShort),
			ENUM_HELPER(ImGuiHoveredFlags, DelayNormal),
			ENUM_HELPER(ImGuiHoveredFlags, NoSharedDelay)
		);
#pragma endregion Hovered Flags

#pragma region DockNode Flags
#ifndef IMGUI_NO_DOCKING
		lua.new_enum("ImGuiDockNodeFlags",
			ENUM_HELPER(ImGuiDockNodeFlags, None),
			ENUM_HELPER(ImGuiDockNodeFlags, KeepAliveOnly),
			ENUM_HELPER(ImGuiDockNodeFlags, NoDockingOverCentralNode),
			ENUM_HELPER(ImGuiDockNodeFlags, PassthruCentralNode),
			ENUM_HELPER(ImGuiDockNodeFlags, NoDockingSplit),
			ENUM_HELPER(ImGuiDockNodeFlags, NoResize),
			ENUM_HELPER(ImGuiDockNodeFlags, AutoHideTabBar),
			ENUM_HELPER(ImGuiDockNodeFlags, NoUndocking)
		);
#endif
#pragma endregion DockNode Flags

#pragma region DragDrop Flags
		lua.new_enum("ImGuiDragDropFlags",
			ENUM_HELPER(ImGuiDragDropFlags, None),
			ENUM_HELPER(ImGuiDragDropFlags, SourceNoPreviewTooltip),
			ENUM_HELPER(ImGuiDragDropFlags, SourceNoDisableHover),
			ENUM_HELPER(ImGuiDragDropFlags, SourceNoHoldToOpenOthers),
			ENUM_HELPER(ImGuiDragDropFlags, SourceAllowNullID),
			ENUM_HELPER(ImGuiDragDropFlags, SourceExtern),
			ENUM_HELPER(ImGuiDragDropFlags, PayloadAutoExpire),
			ENUM_HELPER(ImGuiDragDropFlags, PayloadNoCrossContext),
			ENUM_HELPER(ImGuiDragDropFlags, PayloadNoCrossProcess),
			ENUM_HELPER(ImGuiDragDropFlags, AcceptBeforeDelivery),
			ENUM_HELPER(ImGuiDragDropFlags, AcceptNoDrawDefaultRect),
			ENUM_HELPER(ImGuiDragDropFlags, AcceptNoPreviewTooltip),
			ENUM_HELPER(ImGuiDragDropFlags, AcceptPeekOnly)
		);
#pragma endregion DragDrop Flags

#pragma region Datatype
		lua.new_enum("ImGuiDataType",
			ENUM_HELPER(ImGuiDataType, S8),
			ENUM_HELPER(ImGuiDataType, U8),
			ENUM_HELPER(ImGuiDataType, S16),
			ENUM_HELPER(ImGuiDataType, U16),
			ENUM_HELPER(ImGuiDataType, S32),
			ENUM_HELPER(ImGuiDataType, U32),
			ENUM_HELPER(ImGuiDataType, S64),
			ENUM_HELPER(ImGuiDataType, U64),
			ENUM_HELPER(ImGuiDataType, Float),
			ENUM_HELPER(ImGuiDataType, Double),
			ENUM_HELPER(ImGuiDataType, Bool),
			ENUM_HELPER(ImGuiDataType, COUNT)
		);
#pragma endregion Datatype

#pragma region Dir
		lua.new_enum("ImGuiDir",
			ENUM_HELPER(ImGuiDir,None),
			ENUM_HELPER(ImGuiDir,Left),
			ENUM_HELPER(ImGuiDir,Right),
			ENUM_HELPER(ImGuiDir,Up),
			ENUM_HELPER(ImGuiDir,Down),
			ENUM_HELPER(ImGuiDir,COUNT)
		);
#pragma endregion Dir

#pragma region Sort Dir
		lua.new_enum("ImGuiSortDirection",
			ENUM_HELPER(ImGuiSortDirection, None),
			ENUM_HELPER(ImGuiSortDirection, Ascending),
			ENUM_HELPER(ImGuiSortDirection, Descending)
		);
#pragma endregion Sort Dir

#pragma region Key
		lua.new_enum("ImGuiKey",
			ENUM_HELPER(ImGuiKey, Tab),
			ENUM_HELPER(ImGuiKey, LeftArrow),
			ENUM_HELPER(ImGuiKey, RightArrow),
			ENUM_HELPER(ImGuiKey, UpArrow),
			ENUM_HELPER(ImGuiKey, DownArrow),
			ENUM_HELPER(ImGuiKey, PageUp),
			ENUM_HELPER(ImGuiKey, PageDown),
			ENUM_HELPER(ImGuiKey, Home),
			ENUM_HELPER(ImGuiKey, End),
			ENUM_HELPER(ImGuiKey, Insert),
			ENUM_HELPER(ImGuiKey, Delete),
			ENUM_HELPER(ImGuiKey, Backspace),
			ENUM_HELPER(ImGuiKey, Space),
			ENUM_HELPER(ImGuiKey, Enter),
			ENUM_HELPER(ImGuiKey, Escape),
			ENUM_HELPER(ImGuiKey, LeftCtrl),
			ENUM_HELPER(ImGuiKey, LeftShift),
			ENUM_HELPER(ImGuiKey, LeftAlt),
			ENUM_HELPER(ImGuiKey, LeftSuper),
			ENUM_HELPER(ImGuiKey, RightCtrl),
			ENUM_HELPER(ImGuiKey, RightShift),
			ENUM_HELPER(ImGuiKey, RightAlt),
			ENUM_HELPER(ImGuiKey, RightSuper),
			ENUM_HELPER(ImGuiKey, Menu),
			ENUM_HELPER(ImGuiKey, 0),
			ENUM_HELPER(ImGuiKey, 1),
			ENUM_HELPER(ImGuiKey, 2),
			ENUM_HELPER(ImGuiKey, 3),
			ENUM_HELPER(ImGuiKey, 4),
			ENUM_HELPER(ImGuiKey, 5),
			ENUM_HELPER(ImGuiKey, 6),
			ENUM_HELPER(ImGuiKey, 7),
			ENUM_HELPER(ImGuiKey, 8),
			ENUM_HELPER(ImGuiKey, 9),
			ENUM_HELPER(ImGuiKey, A),
			ENUM_HELPER(ImGuiKey, B),
			ENUM_HELPER(ImGuiKey, C),
			ENUM_HELPER(ImGuiKey, D),
			ENUM_HELPER(ImGuiKey, E),
			ENUM_HELPER(ImGuiKey, F),
			ENUM_HELPER(ImGuiKey, G),
			ENUM_HELPER(ImGuiKey, H),
			ENUM_HELPER(ImGuiKey, I),
			ENUM_HELPER(ImGuiKey, J),
			ENUM_HELPER(ImGuiKey, K),
			ENUM_HELPER(ImGuiKey, L),
			ENUM_HELPER(ImGuiKey, M),
			ENUM_HELPER(ImGuiKey, N),
			ENUM_HELPER(ImGuiKey, O),
			ENUM_HELPER(ImGuiKey, P),
			ENUM_HELPER(ImGuiKey, Q),
			ENUM_HELPER(ImGuiKey, R),
			ENUM_HELPER(ImGuiKey, S),
			ENUM_HELPER(ImGuiKey, T),
			ENUM_HELPER(ImGuiKey, U),
			ENUM_HELPER(ImGuiKey, V),
			ENUM_HELPER(ImGuiKey, W),
			ENUM_HELPER(ImGuiKey, X),
			ENUM_HELPER(ImGuiKey, Y),
			ENUM_HELPER(ImGuiKey, Z),
			ENUM_HELPER(ImGuiKey, F1),
			ENUM_HELPER(ImGuiKey, F2),
			ENUM_HELPER(ImGuiKey, F3),
			ENUM_HELPER(ImGuiKey, F4),
			ENUM_HELPER(ImGuiKey, F5),
			ENUM_HELPER(ImGuiKey, F6),
			ENUM_HELPER(ImGuiKey, F7),
			ENUM_HELPER(ImGuiKey, F8),
			ENUM_HELPER(ImGuiKey, F9),
			ENUM_HELPER(ImGuiKey, F10),
			ENUM_HELPER(ImGuiKey, F11),
			ENUM_HELPER(ImGuiKey, F12),
			ENUM_HELPER(ImGuiKey, F13),
			ENUM_HELPER(ImGuiKey, F14),
			ENUM_HELPER(ImGuiKey, F15),
			ENUM_HELPER(ImGuiKey, F16),
			ENUM_HELPER(ImGuiKey, F17),
			ENUM_HELPER(ImGuiKey, F18),
			ENUM_HELPER(ImGuiKey, F19),
			ENUM_HELPER(ImGuiKey, F20),
			ENUM_HELPER(ImGuiKey, F21),
			ENUM_HELPER(ImGuiKey, F22),
			ENUM_HELPER(ImGuiKey, F23),
			ENUM_HELPER(ImGuiKey, F24),
			ENUM_HELPER(ImGuiKey, Apostrophe),
			ENUM_HELPER(ImGuiKey, Comma),
			ENUM_HELPER(ImGuiKey, Minus),
			ENUM_HELPER(ImGuiKey, Period),
			ENUM_HELPER(ImGuiKey, Slash),
			ENUM_HELPER(ImGuiKey, Semicolon),
			ENUM_HELPER(ImGuiKey, Equal),
			ENUM_HELPER(ImGuiKey, LeftBracket),
			ENUM_HELPER(ImGuiKey, Backslash),
			ENUM_HELPER(ImGuiKey, RightBracket),
			ENUM_HELPER(ImGuiKey, GraveAccent),
			ENUM_HELPER(ImGuiKey, CapsLock),
			ENUM_HELPER(ImGuiKey, ScrollLock),
			ENUM_HELPER(ImGuiKey, NumLock),
			ENUM_HELPER(ImGuiKey, PrintScreen),
			ENUM_HELPER(ImGuiKey, Pause),
			ENUM_HELPER(ImGuiKey, Keypad0),
			ENUM_HELPER(ImGuiKey, Keypad1),
			ENUM_HELPER(ImGuiKey, Keypad2),
			ENUM_HELPER(ImGuiKey, Keypad3),
			ENUM_HELPER(ImGuiKey, Keypad4),
			ENUM_HELPER(ImGuiKey, Keypad5),
			ENUM_HELPER(ImGuiKey, Keypad6),
			ENUM_HELPER(ImGuiKey, Keypad7),
			ENUM_HELPER(ImGuiKey, Keypad8),
			ENUM_HELPER(ImGuiKey, Keypad9),
			ENUM_HELPER(ImGuiKey, KeypadDecimal),
			ENUM_HELPER(ImGuiKey, KeypadDivide),
			ENUM_HELPER(ImGuiKey, KeypadMultiply),
			ENUM_HELPER(ImGuiKey, KeypadSubtract),
			ENUM_HELPER(ImGuiKey, KeypadAdd),
			ENUM_HELPER(ImGuiKey, KeypadEnter),
			ENUM_HELPER(ImGuiKey, KeypadEqual),
			ENUM_HELPER(ImGuiKey, AppBack),
			ENUM_HELPER(ImGuiKey, AppForward),
			ENUM_HELPER(ImGuiKey, GamepadStart),
			ENUM_HELPER(ImGuiKey, GamepadBack),
			ENUM_HELPER(ImGuiKey, GamepadFaceLeft),
			ENUM_HELPER(ImGuiKey, GamepadFaceRight),
			ENUM_HELPER(ImGuiKey, GamepadFaceUp),
			ENUM_HELPER(ImGuiKey, GamepadFaceDown),
			ENUM_HELPER(ImGuiKey, GamepadDpadLeft),
			ENUM_HELPER(ImGuiKey, GamepadDpadRight),
			ENUM_HELPER(ImGuiKey, GamepadDpadUp),
			ENUM_HELPER(ImGuiKey, GamepadDpadDown),
			ENUM_HELPER(ImGuiKey, GamepadL1),
			ENUM_HELPER(ImGuiKey, GamepadR1),
			ENUM_HELPER(ImGuiKey, GamepadL2),
			ENUM_HELPER(ImGuiKey, GamepadR2),
			ENUM_HELPER(ImGuiKey, GamepadL3),
			ENUM_HELPER(ImGuiKey, GamepadR3),
			ENUM_HELPER(ImGuiKey, GamepadLStickLeft),
			ENUM_HELPER(ImGuiKey, GamepadLStickRight),
			ENUM_HELPER(ImGuiKey, GamepadLStickUp),
			ENUM_HELPER(ImGuiKey, GamepadLStickDown),
			ENUM_HELPER(ImGuiKey, GamepadRStickLeft),
			ENUM_HELPER(ImGuiKey, GamepadRStickRight),
			ENUM_HELPER(ImGuiKey, GamepadRStickUp),
			ENUM_HELPER(ImGuiKey, GamepadRStickDown),
			ENUM_HELPER(ImGuiKey, MouseLeft),
			ENUM_HELPER(ImGuiKey, MouseRight),
			ENUM_HELPER(ImGuiKey, MouseMiddle),
			ENUM_HELPER(ImGuiKey, MouseX1),
			ENUM_HELPER(ImGuiKey, MouseX2),
			ENUM_HELPER(ImGuiKey, MouseWheelX),
			ENUM_HELPER(ImGuiKey, MouseWheelY),
			ENUM_HELPER(ImGuiKey, ReservedForModCtrl),
			ENUM_HELPER(ImGuiKey, ReservedForModShift),
			ENUM_HELPER(ImGuiKey, ReservedForModAlt),
			ENUM_HELPER(ImGuiKey, ReservedForModSuper),
			ENUM_HELPER(ImGuiKey, COUNT),
			ENUM_HELPER(ImGuiMod, None),
			ENUM_HELPER(ImGuiMod, Ctrl),
			ENUM_HELPER(ImGuiMod, Shift),
			ENUM_HELPER(ImGuiMod, Alt),
			ENUM_HELPER(ImGuiMod, Super),
			ENUM_HELPER(ImGuiMod, Mask_),
			ENUM_HELPER(ImGuiKey, NamedKey_BEGIN),
			ENUM_HELPER(ImGuiKey, NamedKey_END),
			ENUM_HELPER(ImGuiKey, NamedKey_COUNT),
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
			ENUM_HELPER(ImGuiKey, NamedKey_COUNT),
			ENUM_HELPER(ImGuiKey, NamedKey_BEGIN)
#else
			ENUM_HELPER(ImGuiKey, KeysData_SIZE),
			ENUM_HELPER(ImGuiKey, KeysData_OFFSET)
#endif
		);
#pragma endregion Key

#pragma region Input Flags
		lua.new_enum("ImGuiInputFlags",
			ENUM_HELPER(ImGuiInputFlags, None),
			ENUM_HELPER(ImGuiInputFlags, Repeat),
			ENUM_HELPER(ImGuiInputFlags, RouteActive),
			ENUM_HELPER(ImGuiInputFlags, RouteFocused),
			ENUM_HELPER(ImGuiInputFlags, RouteGlobal),
			ENUM_HELPER(ImGuiInputFlags, RouteAlways),
			ENUM_HELPER(ImGuiInputFlags, RouteOverFocused),
			ENUM_HELPER(ImGuiInputFlags, RouteOverActive),
			ENUM_HELPER(ImGuiInputFlags, RouteUnlessBgFocused),
			ENUM_HELPER(ImGuiInputFlags, RouteFromRootWindow),
			ENUM_HELPER(ImGuiInputFlags, Tooltip)
		);
#pragma endregion Input Flags

#pragma region Config Flags
		lua.new_enum("ImGuiConfigFlags",
			ENUM_HELPER(ImGuiConfigFlags, None),
			ENUM_HELPER(ImGuiConfigFlags, NavEnableKeyboard),
			ENUM_HELPER(ImGuiConfigFlags, NavEnableGamepad),
			ENUM_HELPER(ImGuiConfigFlags, NavEnableSetMousePos),
			ENUM_HELPER(ImGuiConfigFlags, NavNoCaptureKeyboard),
			ENUM_HELPER(ImGuiConfigFlags, NoMouse),
			ENUM_HELPER(ImGuiConfigFlags, NoMouseCursorChange),
			ENUM_HELPER(ImGuiConfigFlags, NoKeyboard),
			#ifndef IMGUI_NO_DOCKING
			ENUM_HELPER(ImGuiConfigFlags, DockingEnable),
			ENUM_HELPER(ImGuiConfigFlags, ViewportsEnable),
			ENUM_HELPER(ImGuiConfigFlags, DpiEnableScaleViewports),
			ENUM_HELPER(ImGuiConfigFlags, DpiEnableScaleFonts),
			#endif
			ENUM_HELPER(ImGuiConfigFlags, IsSRGB),
			ENUM_HELPER(ImGuiConfigFlags, IsTouchScreen)
		);
#pragma endregion Config Flags

#pragma region Backend Flags
		lua.new_enum("ImGuiBackendFlags",
			ENUM_HELPER(ImGuiBackendFlags, None),
			ENUM_HELPER(ImGuiBackendFlags, HasGamepad),
			ENUM_HELPER(ImGuiBackendFlags, HasMouseCursors),
			ENUM_HELPER(ImGuiBackendFlags, HasSetMousePos),
			ENUM_HELPER(ImGuiBackendFlags, RendererHasVtxOffset)
			#ifndef IMGUI_NO_DOCKING
			,	// Gotta add the comma for correct syntax
			ENUM_HELPER(ImGuiBackendFlags, PlatformHasViewports),
			ENUM_HELPER(ImGuiBackendFlags, HasMouseHoveredViewport),
			ENUM_HELPER(ImGuiBackendFlags, RendererHasViewports)
			#endif
		);
#pragma endregion Backend Flags

#pragma region Col
		lua.new_enum("ImGuiCol",
			ENUM_HELPER(ImGuiCol, Text),
			ENUM_HELPER(ImGuiCol, TextDisabled),
			ENUM_HELPER(ImGuiCol, WindowBg),
			ENUM_HELPER(ImGuiCol, ChildBg),
			ENUM_HELPER(ImGuiCol, PopupBg),
			ENUM_HELPER(ImGuiCol, Border),
			ENUM_HELPER(ImGuiCol, BorderShadow),
			ENUM_HELPER(ImGuiCol, FrameBg),
			ENUM_HELPER(ImGuiCol, FrameBgHovered),
			ENUM_HELPER(ImGuiCol, FrameBgActive),
			ENUM_HELPER(ImGuiCol, TitleBg),
			ENUM_HELPER(ImGuiCol, TitleBgActive),
			ENUM_HELPER(ImGuiCol, TitleBgCollapsed),
			ENUM_HELPER(ImGuiCol, MenuBarBg),
			ENUM_HELPER(ImGuiCol, ScrollbarBg),
			ENUM_HELPER(ImGuiCol, ScrollbarGrab),
			ENUM_HELPER(ImGuiCol, ScrollbarGrabHovered),
			ENUM_HELPER(ImGuiCol, ScrollbarGrabActive),
			ENUM_HELPER(ImGuiCol, CheckMark),
			ENUM_HELPER(ImGuiCol, SliderGrab),
			ENUM_HELPER(ImGuiCol, SliderGrabActive),
			ENUM_HELPER(ImGuiCol, Button),
			ENUM_HELPER(ImGuiCol, ButtonHovered),
			ENUM_HELPER(ImGuiCol, ButtonActive),
			ENUM_HELPER(ImGuiCol, Header),
			ENUM_HELPER(ImGuiCol, HeaderHovered),
			ENUM_HELPER(ImGuiCol, HeaderActive),
			ENUM_HELPER(ImGuiCol, Separator),
			ENUM_HELPER(ImGuiCol, SeparatorHovered),
			ENUM_HELPER(ImGuiCol, SeparatorActive),
			ENUM_HELPER(ImGuiCol, ResizeGrip),
			ENUM_HELPER(ImGuiCol, ResizeGripHovered),
			ENUM_HELPER(ImGuiCol, ResizeGripActive),
			ENUM_HELPER(ImGuiCol, TabHovered),
			ENUM_HELPER(ImGuiCol, Tab),
			ENUM_HELPER(ImGuiCol, TabSelected),
			ENUM_HELPER(ImGuiCol, TabSelectedOverline),
			ENUM_HELPER(ImGuiCol, TabDimmed),
			ENUM_HELPER(ImGuiCol, TabDimmedSelected),
			ENUM_HELPER(ImGuiCol, TabDimmedSelectedOverline),
			#ifndef IMGUI_NO_DOCKING
			ENUM_HELPER(ImGuiCol, DockingPreview),
			ENUM_HELPER(ImGuiCol, DockingEmptyBg),
			#endif
			ENUM_HELPER(ImGuiCol, PlotLines),
			ENUM_HELPER(ImGuiCol, PlotLinesHovered),
			ENUM_HELPER(ImGuiCol, PlotHistogram),
			ENUM_HELPER(ImGuiCol, PlotHistogramHovered),
			ENUM_HELPER(ImGuiCol, TableHeaderBg),
			ENUM_HELPER(ImGuiCol, TableBorderStrong),
			ENUM_HELPER(ImGuiCol, TableBorderLight),
			ENUM_HELPER(ImGuiCol, TableRowBg),
			ENUM_HELPER(ImGuiCol, TableRowBgAlt),
			ENUM_HELPER(ImGuiCol, TextLink),
			ENUM_HELPER(ImGuiCol, TextSelectedBg),
			ENUM_HELPER(ImGuiCol, DragDropTarget),
			ENUM_HELPER(ImGuiCol, NavHighlight),
			ENUM_HELPER(ImGuiCol, NavWindowingHighlight),
			ENUM_HELPER(ImGuiCol, NavWindowingDimBg),
			ENUM_HELPER(ImGuiCol, ModalWindowDimBg),
			ENUM_HELPER(ImGuiCol, COUNT)
		);
#pragma endregion Col

#pragma region Style
		lua.new_enum("ImGuiStyleVar",
			ENUM_HELPER(ImGuiStyleVar, Alpha),
			ENUM_HELPER(ImGuiStyleVar, DisabledAlpha),
			ENUM_HELPER(ImGuiStyleVar, WindowPadding),
			ENUM_HELPER(ImGuiStyleVar, WindowRounding),
			ENUM_HELPER(ImGuiStyleVar, WindowBorderSize),
			ENUM_HELPER(ImGuiStyleVar, WindowMinSize),
			ENUM_HELPER(ImGuiStyleVar, WindowTitleAlign),
			ENUM_HELPER(ImGuiStyleVar, ChildRounding),
			ENUM_HELPER(ImGuiStyleVar, ChildBorderSize),
			ENUM_HELPER(ImGuiStyleVar, PopupRounding),
			ENUM_HELPER(ImGuiStyleVar, PopupBorderSize),
			ENUM_HELPER(ImGuiStyleVar, FramePadding),
			ENUM_HELPER(ImGuiStyleVar, FrameRounding),
			ENUM_HELPER(ImGuiStyleVar, FrameBorderSize),
			ENUM_HELPER(ImGuiStyleVar, ItemSpacing),
			ENUM_HELPER(ImGuiStyleVar, ItemInnerSpacing),
			ENUM_HELPER(ImGuiStyleVar, IndentSpacing),
			ENUM_HELPER(ImGuiStyleVar, CellPadding),
			ENUM_HELPER(ImGuiStyleVar, ScrollbarSize),
			ENUM_HELPER(ImGuiStyleVar, ScrollbarRounding),
			ENUM_HELPER(ImGuiStyleVar, GrabMinSize),
			ENUM_HELPER(ImGuiStyleVar, GrabRounding),
			ENUM_HELPER(ImGuiStyleVar, TabRounding),
			ENUM_HELPER(ImGuiStyleVar, TabBorderSize),
			ENUM_HELPER(ImGuiStyleVar, TabBarBorderSize),
			ENUM_HELPER(ImGuiStyleVar, TabBarOverlineSize),
			ENUM_HELPER(ImGuiStyleVar, TableAngledHeadersAngle),
			ENUM_HELPER(ImGuiStyleVar, TableAngledHeadersTextAlign),
			ENUM_HELPER(ImGuiStyleVar, ButtonTextAlign),
			ENUM_HELPER(ImGuiStyleVar, SelectableTextAlign),
			ENUM_HELPER(ImGuiStyleVar, SeparatorTextBorderSize),
			ENUM_HELPER(ImGuiStyleVar, SeparatorTextAlign),
			ENUM_HELPER(ImGuiStyleVar, SeparatorTextPadding),
			#ifndef IMGUI_NO_DOCKING
			ENUM_HELPER(ImGuiStyleVar, DockingSeparatorSize),
			#endif
			ENUM_HELPER(ImGuiStyleVar, COUNT)
		);
#pragma endregion Style

#pragma region Button Flags
		lua.new_enum("ImGuiButtonFlags",
			ENUM_HELPER(ImGuiButtonFlags, None),
			ENUM_HELPER(ImGuiButtonFlags, MouseButtonLeft),
			ENUM_HELPER(ImGuiButtonFlags, MouseButtonRight),
			ENUM_HELPER(ImGuiButtonFlags, MouseButtonMiddle),
			ENUM_HELPER(ImGuiButtonFlags, MouseButtonMask_)
		);
#pragma endregion Button Flags

#pragma region ColorEdit Flags
		lua.new_enum("ImGuiColorEditFlags",
			ENUM_HELPER(ImGuiColorEditFlags, None),
			ENUM_HELPER(ImGuiColorEditFlags, NoAlpha),
			ENUM_HELPER(ImGuiColorEditFlags, NoPicker),
			ENUM_HELPER(ImGuiColorEditFlags, NoOptions),
			ENUM_HELPER(ImGuiColorEditFlags, NoSmallPreview),
			ENUM_HELPER(ImGuiColorEditFlags, NoInputs),
			ENUM_HELPER(ImGuiColorEditFlags, NoTooltip),
			ENUM_HELPER(ImGuiColorEditFlags, NoLabel),
			ENUM_HELPER(ImGuiColorEditFlags, NoSidePreview),
			ENUM_HELPER(ImGuiColorEditFlags, NoDragDrop),
			ENUM_HELPER(ImGuiColorEditFlags, NoBorder),
			ENUM_HELPER(ImGuiColorEditFlags, AlphaBar),
			ENUM_HELPER(ImGuiColorEditFlags, AlphaPreview),
			ENUM_HELPER(ImGuiColorEditFlags, AlphaPreviewHalf),
			ENUM_HELPER(ImGuiColorEditFlags, HDR),
			ENUM_HELPER(ImGuiColorEditFlags, DisplayRGB),
			ENUM_HELPER(ImGuiColorEditFlags, DisplayHSV),
			ENUM_HELPER(ImGuiColorEditFlags, DisplayHex),
			ENUM_HELPER(ImGuiColorEditFlags, Uint8),
			ENUM_HELPER(ImGuiColorEditFlags, Float),
			ENUM_HELPER(ImGuiColorEditFlags, PickerHueBar),
			ENUM_HELPER(ImGuiColorEditFlags, PickerHueWheel),
			ENUM_HELPER(ImGuiColorEditFlags, InputRGB),
			ENUM_HELPER(ImGuiColorEditFlags, InputHSV),
			ENUM_HELPER(ImGuiColorEditFlags, DefaultOptions_),
			ENUM_HELPER(ImGuiColorEditFlags, DisplayMask_),
			ENUM_HELPER(ImGuiColorEditFlags, DataTypeMask_),
			ENUM_HELPER(ImGuiColorEditFlags, PickerMask_),
			ENUM_HELPER(ImGuiColorEditFlags, InputMask_)
		);
#pragma endregion ColorEdit Flags

#pragma region Slider Flags
		lua.new_enum("ImGuiSliderFlags",
			ENUM_HELPER(ImGuiSliderFlags, None),
			ENUM_HELPER(ImGuiSliderFlags, AlwaysClamp),
			ENUM_HELPER(ImGuiSliderFlags, Logarithmic),
			ENUM_HELPER(ImGuiSliderFlags, NoRoundToFormat),
			ENUM_HELPER(ImGuiSliderFlags, NoInput),
			ENUM_HELPER(ImGuiSliderFlags, WrapAround),
			ENUM_HELPER(ImGuiSliderFlags, InvalidMask_)
		);
#pragma endregion Slider Flags

#pragma region MouseButton
		lua.new_enum("ImGuiMouseButton",
			ENUM_HELPER(ImGuiMouseButton, Left),
			ENUM_HELPER(ImGuiMouseButton, Right),
			ENUM_HELPER(ImGuiMouseButton, Middle),
			ENUM_HELPER(ImGuiMouseButton, COUNT)
		);
#pragma endregion MouseButton

#pragma region MouseCursor
		lua.new_enum("ImGuiMouseCursor",
			ENUM_HELPER(ImGuiMouseCursor, None),
			ENUM_HELPER(ImGuiMouseCursor, Arrow),
			ENUM_HELPER(ImGuiMouseCursor, TextInput),
			ENUM_HELPER(ImGuiMouseCursor, ResizeAll),
			ENUM_HELPER(ImGuiMouseCursor, ResizeNS),
			ENUM_HELPER(ImGuiMouseCursor, ResizeEW),
			ENUM_HELPER(ImGuiMouseCursor, ResizeNESW),
			ENUM_HELPER(ImGuiMouseCursor, ResizeNWSE),
			ENUM_HELPER(ImGuiMouseCursor, Hand),
			ENUM_HELPER(ImGuiMouseCursor, NotAllowed),
			ENUM_HELPER(ImGuiMouseCursor, COUNT)
		);
#pragma endregion MouseCursor

#pragma region Mouse Source
			lua.new_enum("ImGuiMouseSource",
				ENUM_HELPER(ImGuiMouseSource, Mouse),
				ENUM_HELPER(ImGuiMouseSource, TouchScreen),
				ENUM_HELPER(ImGuiMouseSource, Pen),
				ENUM_HELPER(ImGuiMouseSource, COUNT)
			);
#pragma endregion Sort Dir

#pragma region Cond
		lua.new_enum("ImGuiCond",
			ENUM_HELPER(ImGuiCond, None),
			ENUM_HELPER(ImGuiCond, Always),
			ENUM_HELPER(ImGuiCond, Once),
			ENUM_HELPER(ImGuiCond, FirstUseEver),
			ENUM_HELPER(ImGuiCond, Appearing)
		);
#pragma endregion Cond

	}
	
	template <typename SolStateOrView>
	inline void InitUserTypes(SolStateOrView& lua)
	{
		static_assert( std::is_same_v<SolStateOrView, sol::state> || std::is_same_v<SolStateOrView, sol::state_view>, "sol_ImGui::InitUserTypes only accepts sol::state& or sol::state_view&");
		
		lua.new_usertype<ImVec2>("ImVec2",
			sol::constructors<ImVec2(), ImVec2(float, float)>(),
			"x", &ImVec2::x,
			"y", &ImVec2::y
		);

		lua.new_usertype<ImVec4>("ImVec4",
			sol::constructors<ImVec4(), ImVec4(float, float, float, float)>(),
			"x", &ImVec4::x,
			"y", &ImVec4::y,
			"z", &ImVec4::z,
			"w", &ImVec4::w
		);

		lua.new_usertype<ImDrawList>("ImDrawList",
			sol::no_constructor, // Prevent creating ImDrawList directly in Lua

			// Clip Rects
			"PushClipRect", 			&ImDrawList::PushClipRect,
			"PushClipRectFullScreen", 	&ImDrawList::PushClipRectFullScreen,
			"PopClipRect", 				&ImDrawList::PopClipRect,

			// Texture ID
			"PushTextureID", 			&ImDrawList::PushTextureID,
			"PopTextureID", 			&ImDrawList::PopTextureID,

			// Primitives
			"AddLine", 					&ImDrawList::AddLine,
			"AddRect", 					&ImDrawList::AddRect,
			"AddRectFilled", 			&ImDrawList::AddRectFilled,
			"AddCircle", 				&ImDrawList::AddCircle,
			"AddCircleFilled", 			&ImDrawList::AddCircleFilled,
			"AddTriangle", 				&ImDrawList::AddTriangle,
			"AddTriangleFilled", 		&ImDrawList::AddTriangleFilled,
			"AddText", 					static_cast<void(ImDrawList::*)(const ImVec2&, ImU32, const char*, const char*)>(&ImDrawList::AddText),
			"AddQuad", 					&ImDrawList::AddQuad,
			"AddQuadFilled", 			&ImDrawList::AddQuadFilled,
			"AddNgon", 					&ImDrawList::AddNgon,
			"AddNgonFilled", 			&ImDrawList::AddNgonFilled,

			// Path API
			"PathClear", 				&ImDrawList::PathClear,
			"PathLineTo", 				&ImDrawList::PathLineTo,
			"PathStroke", 				&ImDrawList::PathStroke,
			"PathFillConvex", 			&ImDrawList::PathFillConvex,
			"PathArcTo", 				&ImDrawList::PathArcTo,
			"PathBezierCubicCurveTo", 	&ImDrawList::PathBezierCubicCurveTo,
			"PathRect", 				&ImDrawList::PathRect,

			// Images
			"AddImage", 				&ImDrawList::AddImage,
			"AddImageQuad", 			&ImDrawList::AddImageQuad,
			"AddImageRounded", 			&ImDrawList::AddImageRounded
		);
	}

	template <typename SolStateOrView>
	inline void Init(SolStateOrView& lua)
	{
		static_assert( std::is_same_v<SolStateOrView, sol::state> || std::is_same_v<SolStateOrView, sol::state_view>, "sol_ImGui::Init only accepts sol::state& or sol::state_view&");
		InitEnums(lua);
		
		InitUserTypes(lua);

		sol::table ImGui = lua.create_named_table("ImGui");


#pragma region Windows
		ImGui.set_function("Begin"							, sol::overload(
																sol::resolve<bool(const std::string&)>(Begin),
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool)>(Begin), 
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool, int)>(Begin)
															));
		ImGui.set_function("End"							, End);
#pragma endregion Windows

#pragma region Child Windows
		ImGui.set_function("BeginChild"						, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginChild), 
																sol::resolve<bool(const std::string&, float)>(BeginChild), 
																sol::resolve<bool(const std::string&, float, float)>(BeginChild),
																sol::resolve<bool(const std::string&, float, float, int)>(BeginChild), 
																sol::resolve<bool(const std::string&, float, float, int, int)>(BeginChild)
															));
		ImGui.set_function("EndChild"						, EndChild);
#pragma endregion Child Windows

#pragma region Window Utilities
		ImGui.set_function("IsWindowAppearing"				, IsWindowAppearing);
		ImGui.set_function("IsWindowCollapsed"				, IsWindowCollapsed);
		ImGui.set_function("IsWindowFocused"				, sol::overload(
																sol::resolve<bool()>(IsWindowFocused),
																sol::resolve<bool(int)>(IsWindowFocused)
															));
		ImGui.set_function("IsWindowHovered"				, sol::overload(
																sol::resolve<bool()>(IsWindowHovered),
																sol::resolve<bool(int)>(IsWindowHovered)
															));
		
		#ifndef IMGUI_NO_DOCKING
		ImGui.set_function("GetWindowDpiScale"				, GetWindowDpiScale);
		#endif

		ImGui.set_function("GetWindowPos"					, GetWindowPos);
		ImGui.set_function("GetWindowSize"					, GetWindowSize);
		ImGui.set_function("GetWindowWidth"					, GetWindowWidth);
		ImGui.set_function("GetWindowHeight"				, GetWindowHeight);

		// Prefer  SetNext...
		ImGui.set_function("SetNextWindowPos"				, sol::overload(
																sol::resolve<void(float, float)>(SetNextWindowPos), 
																sol::resolve<void(float, float, int)>(SetNextWindowPos), 
																sol::resolve<void(float, float, int, float, float)>(SetNextWindowPos)
															));
		ImGui.set_function("SetNextWindowSize"				, sol::overload(
																sol::resolve<void(float, float)>(SetNextWindowSize),
																sol::resolve<void(float, float, int)>(SetNextWindowSize)
															));
		ImGui.set_function("SetNextWindowSizeConstraints"	, SetNextWindowSizeConstraints);
		ImGui.set_function("SetNextWindowContentSize"		, SetNextWindowContentSize);
		ImGui.set_function("SetNextWindowCollapsed"			, sol::overload(
																sol::resolve<void(bool)>(SetNextWindowCollapsed),
																sol::resolve<void(bool, int)>(SetNextWindowCollapsed)
															));
		ImGui.set_function("SetNextWindowFocus"				, SetNextWindowFocus);
		ImGui.set_function("SetNextWindowBgAlpha"			, SetNextWindowBgAlpha);
		ImGui.set_function("SetWindowPos"					, sol::overload(
																sol::resolve<void(float, float)>(SetWindowPos),
																sol::resolve<void(float, float, int)>(SetWindowPos),
																sol::resolve<void(const std::string&, float, float)>(SetWindowPos),
																sol::resolve<void(const std::string&, float, float, int)>(SetWindowPos)
															));
		ImGui.set_function("SetWindowSize"					, sol::overload(
																sol::resolve<void(float, float)>(SetWindowSize),
																sol::resolve<void(float, float, int)>(SetWindowSize),
																sol::resolve<void(const std::string&, float, float)>(SetWindowSize),
																sol::resolve<void(const std::string&, float, float, int)>(SetWindowSize)
															));
		ImGui.set_function("SetWindowCollapsed"				, sol::overload(
																sol::resolve<void(bool)>(SetWindowCollapsed),
																sol::resolve<void(bool, int)>(SetWindowCollapsed),
																sol::resolve<void(const std::string&, bool)>(SetWindowCollapsed),
																sol::resolve<void(const std::string&, bool, int)>(SetWindowCollapsed)
															));
		ImGui.set_function("SetWindowFocus"					, sol::overload(
																sol::resolve<void()>(SetWindowFocus),
																sol::resolve<void(const std::string&)>(SetWindowFocus)
															));
		ImGui.set_function("SetWindowFontScale"				, SetWindowFontScale);
		ImGui.set_function("GetWindowDrawList"				, GetWindowDrawList);
#pragma endregion Window Utilities
		
#pragma region Content Region
		ImGui.set_function("GetContentRegionMax"			, GetContentRegionMax);
		ImGui.set_function("GetContentRegionAvail"			, GetContentRegionAvail);
		ImGui.set_function("GetWindowContentRegionMin"		, GetWindowContentRegionMin);
		ImGui.set_function("GetWindowContentRegionMax"		, GetWindowContentRegionMax);
		ImGui.set_function("GetWindowContentRegionWidth"	, GetWindowContentRegionWidth);
#pragma endregion Content Region
		
#pragma region Windows Scrolling
		ImGui.set_function("GetScrollX"						, GetScrollX);
		ImGui.set_function("GetScrollY"						, GetScrollY);
		ImGui.set_function("GetScrollMaxX"					, GetScrollMaxX);
		ImGui.set_function("GetScrollMaxY"					, GetScrollMaxY);
		ImGui.set_function("SetScrollX"						, SetScrollX);
		ImGui.set_function("SetScrollY"						, SetScrollY);
		ImGui.set_function("SetScrollHereX"					, sol::overload(
																sol::resolve<void()>(SetScrollHereX),
																sol::resolve<void(float)>(SetScrollHereX)
															));
		ImGui.set_function("SetScrollHereY"					, sol::overload(
																sol::resolve<void()>(SetScrollHereY),
																sol::resolve<void(float)>(SetScrollHereY)
															));
		ImGui.set_function("SetScrollFromPosX"				, sol::overload(
																sol::resolve<void(float)>(SetScrollFromPosX),
																sol::resolve<void(float, float)>(SetScrollFromPosX)
															));
		ImGui.set_function("SetScrollFromPosY"				, sol::overload(
																sol::resolve<void(float)>(SetScrollFromPosY),
																sol::resolve<void(float, float)>(SetScrollFromPosY)
															));
#pragma endregion Windows Scrolling
		
#pragma region Parameters stacks (shared)
		ImGui.set_function("PushFont"						, PushFont);
		ImGui.set_function("PopFont"						, PopFont);
		ImGui.set_function("PushStyleColor"					, sol::overload(
																sol::resolve<void(int, int)>(PushStyleColor),
																sol::resolve<void(int, float, float, float, float)>(PushStyleColor)
															));
		ImGui.set_function("PopStyleColor"					, sol::overload(
																sol::resolve<void()>(PopStyleColor),
																sol::resolve<void(int)>(PopStyleColor)
															));
		ImGui.set_function("GetStyleColorVec4"				, GetStyleColorVec4);
		ImGui.set_function("GetFont"						, GetFont);
		ImGui.set_function("GetFontSize"					, GetFontSize);
		ImGui.set_function("GetFontTexUvWhitePixel"			, GetFontTexUvWhitePixel);
		ImGui.set_function("GetColorU32"					, sol::overload(
																sol::resolve<int(int, float)>(GetColorU32),
																sol::resolve<int(float, float, float, float)>(GetColorU32), 
																sol::resolve<int(int)>(GetColorU32)
															));
#pragma endregion Parameters stacks (shared)
		
#pragma region Parameters stacks (current window)
		ImGui.set_function("PushItemWidth"					, PushItemWidth);
		ImGui.set_function("PopItemWidth"					, PopItemWidth);
		ImGui.set_function("SetNextItemWidth"				, SetNextItemWidth);
		ImGui.set_function("CalcItemWidth"					, CalcItemWidth);
		ImGui.set_function("PushTextWrapPos"				, sol::overload(
																	sol::resolve<void()>(PushTextWrapPos),
																	sol::resolve<void(float)>(PushTextWrapPos)
															));
		ImGui.set_function("PopTextWrapPos"					, PopTextWrapPos);
		//ImGui.set_function("PushAllowKeyboardFocus"			, PushAllowKeyboardFocus);
		//ImGui.set_function("PopAllowKeyboardFocus"			, PopAllowKeyboardFocus);
		//ImGui.set_function("PushButtonRepeat"				, PushButtonRepeat);
		//ImGui.set_function("PopButtonRepeat"				, PopButtonRepeat);
#pragma endregion Parameters stacks (current window)
		
#pragma region Cursor / Layout
		ImGui.set_function("Separator"						, Separator);
		ImGui.set_function("SameLine"						, sol::overload(
																sol::resolve<void()>(SameLine), 
																sol::resolve<void(float)>(SameLine)
															));
		ImGui.set_function("NewLine"						, NewLine);
		ImGui.set_function("Spacing"						, Spacing);
		ImGui.set_function("Dummy"							, Dummy);
		ImGui.set_function("Indent"							, sol::overload(
																sol::resolve<void()>(Indent), 
																sol::resolve<void(float)>(Indent)
															));
		ImGui.set_function("Unindent"						, sol::overload(
																sol::resolve<void()>(Unindent),
																sol::resolve<void(float)>(Unindent)
															));
		ImGui.set_function("BeginGroup"						, BeginGroup);
		ImGui.set_function("EndGroup"						, EndGroup);
		ImGui.set_function("GetCursorPos"					, GetCursorPos);
		ImGui.set_function("GetCursorPosX"					, GetCursorPosX);
		ImGui.set_function("GetCursorPosY"					, GetCursorPosY);
		ImGui.set_function("SetCursorPos"					, SetCursorPos);
		ImGui.set_function("SetCursorPosX"					, SetCursorPosX);
		ImGui.set_function("SetCursorPosY"					, SetCursorPosY);
		ImGui.set_function("GetCursorStartPos"				, GetCursorStartPos);
		ImGui.set_function("GetCursorScreenPos"				, GetCursorScreenPos);
		ImGui.set_function("SetCursorScreenPos"				, SetCursorScreenPos);
		ImGui.set_function("AlignTextToFramePadding"		, AlignTextToFramePadding);
		ImGui.set_function("GetTextLineHeight"				, GetTextLineHeight);
		ImGui.set_function("GetTextLineHeightWithSpacing"	, GetTextLineHeightWithSpacing);
		ImGui.set_function("GetFrameHeight"					, GetFrameHeight);
		ImGui.set_function("GetFrameHeightWithSpacing"		, GetFrameHeightWithSpacing);
#pragma endregion Cursor / Layout
		
#pragma region ID stack / scopes
		ImGui.set_function("PushID"							, sol::overload(
																sol::resolve<void(const std::string&)>(PushID), 
																sol::resolve<void(const std::string&, const std::string&)>(PushID), 
																sol::resolve<void(int)>(PushID)
															));
		ImGui.set_function("PopID"							, PopID);
		ImGui.set_function("GetID"							, sol::overload(
																sol::resolve<int(const std::string&)>(GetID), 
																sol::resolve<int(const std::string&, const std::string&)>(GetID)
															));
#pragma endregion ID stack / scopes
		
#pragma region Widgets: Text
		ImGui.set_function("TextUnformatted"				, sol::overload(
																sol::resolve<void(const std::string&)>(TextUnformatted), 
																sol::resolve<void(const std::string&, const std::string&)>(TextUnformatted)
															));
		ImGui.set_function("Text"							, Text);
		ImGui.set_function("TextColored"					, TextColored);
		ImGui.set_function("TextDisabled"					, TextDisabled);
		ImGui.set_function("TextWrapped"					, TextWrapped);
		ImGui.set_function("LabelText"						, LabelText);
		ImGui.set_function("BulletText"						, BulletText);
#pragma endregion Widgets: Text
		
#pragma region Widgets: Main
		ImGui.set_function("Button"							, sol::overload(
																sol::resolve<bool(const std::string&)>(Button), 
																sol::resolve<bool(const std::string&, float, float)>(Button)
															));
		ImGui.set_function("SmallButton"					, SmallButton);
		ImGui.set_function("InvisibleButton"				, InvisibleButton);
		ImGui.set_function("ArrowButton"					, ArrowButton);
		ImGui.set_function("Checkbox"						, Checkbox);
		ImGui.set_function("RadioButton"					, sol::overload(
																sol::resolve<bool(const std::string&, bool)>(RadioButton), 
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int)>(RadioButton)
															));
		ImGui.set_function("ProgressBar"					, sol::overload(
																sol::resolve<void(float)>(ProgressBar), 
																sol::resolve<void(float, float, float)>(ProgressBar), 
																sol::resolve<void(float, float, float, const std::string&)>(ProgressBar)
															));
		ImGui.set_function("Bullet"							, Bullet);
		ImGui.set_function("Image"							, sol::overload(
																sol::resolve<void(void*, float, float)>(Image),
																sol::resolve<void(void*, const ImVec2&, const ImVec2&, const ImVec2&, const ImVec4&, const ImVec4&)>(ImGui::Image) // Original ImGui::Image
															));
#pragma endregion Widgets: Main
		
#pragma region Widgets: Combo Box
		ImGui.set_function("BeginCombo"						, sol::overload(
																sol::resolve<bool(const std::string&, const std::string&)>(BeginCombo), 
																sol::resolve<bool(const std::string&, const std::string&, int)>(BeginCombo)
															));
		ImGui.set_function("EndCombo"						, EndCombo);
		ImGui.set_function("Combo"							, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const sol::table&, int)>(Combo), 
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const sol::table&, int, int)>(Combo), 
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const std::string&)>(Combo), 
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const std::string&, int)>(Combo)
															));
#pragma endregion Widgets: Combo Box

#pragma region Widgets: Drags
		ImGui.set_function("DragFloat"						, sol::overload(
																sol::resolve<std::tuple<float, bool>(const std::string&, float)>(DragFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float)>(DragFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float)>(DragFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float)>(DragFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float, const std::string&)>(DragFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float, const std::string&, int)>(DragFloat)
															));
		ImGui.set_function("DragFloat2"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(DragFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float)>(DragFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(DragFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float)>(DragFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&)>(DragFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&, int)>(DragFloat2)
															));
		ImGui.set_function("DragFloat3"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(DragFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float)>(DragFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(DragFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float)>(DragFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&)>(DragFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&, int)>(DragFloat3)
															));
		ImGui.set_function("DragFloat4"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(DragFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float)>(DragFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(DragFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float)>(DragFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&)>(DragFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, float, const std::string&, int)>(DragFloat4)
															));
		ImGui.set_function("DragInt"						, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, int)>(DragInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, float)>(DragInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, float, int)>(DragInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, float, int, int)>(DragInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, float, int, int, const std::string&)>(DragInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, float, int, int, const std::string&, int)>(DragInt)
															));
		ImGui.set_function("DragInt2"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(DragInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float)>(DragInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int)>(DragInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int)>(DragInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&)>(DragInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&, int)>(DragInt2)
															));											
		ImGui.set_function("DragInt3"						, sol::overload(			
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(DragInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float)>(DragInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int)>(DragInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int)>(DragInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&)>(DragInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&, int)>(DragInt3)
															));														
		ImGui.set_function("DragInt4"						, sol::overload(			
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(DragInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float)>(DragInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int)>(DragInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int)>(DragInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&)>(DragInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, float, int, int, const std::string&, int)>(DragInt4)
															));
#pragma endregion Widgets: Drags

#pragma region Widgets: Sliders
		ImGui.set_function("SliderFloat"					, sol::overload(
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float)>(SliderFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&)>(SliderFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&, int)>(SliderFloat)
															));
		ImGui.set_function("SliderFloat2"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(SliderFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&)>(SliderFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&, int)>(SliderFloat2)
															));
		ImGui.set_function("SliderFloat3"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(SliderFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&)>(SliderFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&, int)>(SliderFloat3)
															));
		ImGui.set_function("SliderFloat4"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float)>(SliderFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&)>(SliderFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, float, float, const std::string&, int)>(SliderFloat4)
															));
		ImGui.set_function("SliderAngle"					, sol::overload(
																sol::resolve<std::tuple<float, bool>(const std::string&, float)>(SliderAngle),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float)>(SliderAngle),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float)>(SliderAngle),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&)>(SliderAngle),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&, int)>(SliderAngle)
															));
		ImGui.set_function("SliderInt"						, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int, int)>(SliderInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int, int, const std::string&)>(SliderInt)
															));
		ImGui.set_function("SliderInt2"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int)>(SliderInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&)>(SliderInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&, int)>(SliderInt2)
															));
		ImGui.set_function("SliderInt3"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int)>(SliderInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&)>(SliderInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&, int)>(SliderInt3)
															));
		ImGui.set_function("SliderInt4"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int)>(SliderInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&)>(SliderInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int, int, const std::string&, int)>(SliderInt4)
															));
		ImGui.set_function("VSliderFloat"					, sol::overload(
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float, float)>(VSliderFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float, float, const std::string&)>(VSliderFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, float, float, const std::string&, int)>(VSliderFloat)
															));
		ImGui.set_function("VSliderInt"						, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, float, float, int, int, int)>(VSliderInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, float, float, int, int, int, const std::string&)>(VSliderInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, float, float, int, int, int, const std::string&, int)>(VSliderInt)
															));
#pragma endregion Widgets: Sliders

#pragma region Widgets: Inputs using Keyboard
		ImGui.set_function("InputText"						, sol::overload(
																sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string)>(InputText),
																sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string, int)>(InputText)
															));
		ImGui.set_function("InputTextMultiline"				, sol::overload(
																sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string)>(InputTextMultiline),
																sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string, float, float)>(InputTextMultiline),
																sol::resolve<std::tuple<std::string, bool>(const std::string&, std::string, float, float, int)>(InputTextMultiline)
															));
		ImGui.set_function("InputTextWithHint"				, sol::overload(
																sol::resolve<std::tuple<std::string, bool>(const std::string&, const std::string&, std::string)>(InputTextWithHint),
																sol::resolve<std::tuple<std::string, bool>(const std::string&, const std::string&, std::string, int)>(InputTextWithHint)
															));
		ImGui.set_function("InputFloat"						, sol::overload(
																sol::resolve<std::tuple<float, bool>(const std::string&, float)>(InputFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float)>(InputFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float)>(InputFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&)>(InputFloat),
																sol::resolve<std::tuple<float, bool>(const std::string&, float, float, float, const std::string&, int)>(InputFloat)
															));
		ImGui.set_function("InputFloat2"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(InputFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&)>(InputFloat2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&, int)>(InputFloat2)
															));
		ImGui.set_function("InputFloat3"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(InputFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&)>(InputFloat3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&, int)>(InputFloat3)
															));
		ImGui.set_function("InputFloat4"					, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(InputFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&)>(InputFloat4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, const std::string&, int)>(InputFloat4)
															));
		ImGui.set_function("InputInt"						, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, int)>(InputInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int)>(InputInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int, int)>(InputInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int, int)>(InputInt),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, int, int, int)>(InputInt)
															));
		ImGui.set_function("InputInt2"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(InputInt2),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int)>(InputInt2)
															));
		ImGui.set_function("InputInt3"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(InputInt3),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int)>(InputInt3)
															));
		ImGui.set_function("InputInt4"						, sol::overload(
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&)>(InputInt4),
																sol::resolve<std::tuple<sol::as_table_t<std::vector<int>>, bool>(const std::string&, const sol::table&, int)>(InputInt4)
															));
		ImGui.set_function("InputDouble"					, sol::overload(
																sol::resolve<std::tuple<double, bool>(const std::string&, double)>(InputDouble),
																sol::resolve<std::tuple<double, bool>(const std::string&, double, double)>(InputDouble),
																sol::resolve<std::tuple<double, bool>(const std::string&, double, double, double)>(InputDouble),
																sol::resolve<std::tuple<double, bool>(const std::string&, double, double, double, const std::string&)>(InputDouble),
																sol::resolve<std::tuple<double, bool>(const std::string&, double, double, double, const std::string&, int)>(InputDouble)
															));
#pragma endregion Widgets: Inputs using Keyboard

#pragma region Widgets: Color Editor / Picker
		ImGui.set_function("ColorEdit3"						, sol::overload(
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(ColorEdit3),
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, int)>(ColorEdit3)
															));
		ImGui.set_function("ColorEdit4"						, sol::overload(
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(ColorEdit4),
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, int)>(ColorEdit4)
															));
		ImGui.set_function("ColorPicker3"					, sol::overload(
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(ColorPicker3),
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, int)>(ColorPicker3)
															));
		ImGui.set_function("ColorPicker4"					, sol::overload(
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&)>(ColorPicker4),
																sol::resolve<std::tuple <sol::as_table_t<std::vector<float>>, bool>(const std::string&, const sol::table&, int)>(ColorPicker4)
															));
#pragma endregion Widgets: Color Editor / Picker

#pragma region Widgets: Trees
		ImGui.set_function("TreeNode"						, sol::overload(
																sol::resolve<bool(const std::string&)>(TreeNode),
																sol::resolve<bool(const std::string&, const std::string&)>(TreeNode)
															));
		ImGui.set_function("TreeNodeEx"						, sol::overload(
																sol::resolve<bool(const std::string&)>(TreeNodeEx),
																sol::resolve<bool(const std::string&, int)>(TreeNodeEx),
																sol::resolve<bool(const std::string&, int, const std::string&)>(TreeNodeEx)
															));
		ImGui.set_function("TreePop"						, TreePop);
		ImGui.set_function("TreePush"						, TreePush);
		ImGui.set_function("GetTreeNodeToLabelSpacing"		, GetTreeNodeToLabelSpacing);
		ImGui.set_function("CollapsingHeader"				, sol::overload(
																sol::resolve<bool(const std::string&)>(CollapsingHeader),
																sol::resolve<bool(const std::string&, int)>(CollapsingHeader),
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool)>(CollapsingHeader),
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool, int)>(CollapsingHeader)
															));
		ImGui.set_function("SetNextItemOpen"				, sol::overload(
																sol::resolve<void(bool)>(SetNextItemOpen),
																sol::resolve<void(bool, int)>(SetNextItemOpen)
															));
#pragma endregion Widgets: Trees

#pragma region Widgets: Selectables
		ImGui.set_function("Selectable"						, sol::overload(
																sol::resolve<bool(const std::string&)>(Selectable),
																sol::resolve<bool(const std::string&, bool)>(Selectable),
																sol::resolve<bool(const std::string&, bool, int)>(Selectable),
																sol::resolve<bool(const std::string&, bool, int, float, float)>(Selectable)
															));
#pragma endregion Widgets: Selectables

#pragma region Widgets: List Boxes
		ImGui.set_function("ListBox"						, sol::overload(
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const sol::table&, int)>(ListBox),
																sol::resolve<std::tuple<int, bool>(const std::string&, int, const sol::table&, int, int)>(ListBox)
															));
		ImGui.set_function("BeginListBox"					, sol::overload(
																sol::resolve<bool(const std::string&, float, float)>(BeginListBox),
																sol::resolve<bool(const std::string&)>(BeginListBox)
															));
		ImGui.set_function("EndListBox"						, EndListBox);
#pragma endregion Widgets: List Boxes

#pragma region Widgets: Value() Helpers
		ImGui.set_function("Value"							, sol::overload(
																sol::resolve<void(const std::string&, bool)>(Value),
																sol::resolve<void(const std::string&, int)>(Value),
																sol::resolve<void(const std::string&, unsigned int)>(Value),
																sol::resolve<void(const std::string&, float)>(Value),
																sol::resolve<void(const std::string&, float, const std::string&)>(Value)
															));
#pragma endregion Widgets: Value() Helpers

#pragma region Widgets: Menu
		ImGui.set_function("BeginMenuBar"					, BeginMenuBar);
		ImGui.set_function("EndMenuBar"						, EndMenuBar);
		ImGui.set_function("BeginMainMenuBar"				, BeginMainMenuBar);
		ImGui.set_function("EndMainMenuBar"					, EndMainMenuBar);
		ImGui.set_function("BeginMenu"						, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginMenu),
																sol::resolve<bool(const std::string&, bool)>(BeginMenu)
															));
		ImGui.set_function("EndMenu"						, EndMenu);
		ImGui.set_function("MenuItem"						, sol::overload(
																sol::resolve<bool(const std::string&)>(MenuItem),
																sol::resolve<bool(const std::string&, const std::string&)>(MenuItem),
																sol::resolve<std::tuple<bool, bool>(const std::string&, const std::string&, bool)>(MenuItem),
																sol::resolve<std::tuple<bool, bool>(const std::string&, const std::string&, bool, bool)>(MenuItem)
															));
#pragma endregion Widgets: Menu

#pragma region Tooltips
		ImGui.set_function("BeginTooltip"					, BeginTooltip);
		ImGui.set_function("EndTooltip"						, EndTooltip);
		ImGui.set_function("SetTooltip"						, SetTooltip);
#pragma endregion Tooltips

#pragma region Popups, Modals
		ImGui.set_function("BeginPopup"						, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginPopup),
																sol::resolve<bool(const std::string&, int)>(BeginPopup)
															));
		ImGui.set_function("BeginPopupModal"				, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginPopupModal),
																sol::resolve<bool(const std::string&, bool)>(BeginPopupModal),
																sol::resolve<bool(const std::string&, bool, int)>(BeginPopupModal)
															));
		ImGui.set_function("EndPopup"						, EndPopup);
		ImGui.set_function("OpenPopup"						, sol::overload(
																sol::resolve<void(const std::string&)>(OpenPopup),
																sol::resolve<void(const std::string&, int)>(OpenPopup)
															));
		ImGui.set_function("CloseCurrentPopup"				, CloseCurrentPopup);
		ImGui.set_function("BeginPopupContextItem"			, sol::overload(
																sol::resolve<bool()>(BeginPopupContextItem),
																sol::resolve<bool(const std::string&)>(BeginPopupContextItem),
																sol::resolve<bool(const std::string&, int)>(BeginPopupContextItem)
															));
		ImGui.set_function("BeginPopupContextWindow"		, sol::overload(
																sol::resolve<bool()>(BeginPopupContextWindow),
																sol::resolve<bool(const std::string&)>(BeginPopupContextWindow),
																sol::resolve<bool(const std::string&, int)>(BeginPopupContextWindow)
															));
		ImGui.set_function("BeginPopupContextVoid"			, sol::overload(
																sol::resolve<bool()>(BeginPopupContextVoid),
																sol::resolve<bool(const std::string&)>(BeginPopupContextVoid),
																sol::resolve<bool(const std::string&, int)>(BeginPopupContextVoid)
															));
		ImGui.set_function("IsPopupOpen"					, sol::overload(
																sol::resolve<bool(const std::string&)>(IsPopupOpen),
																sol::resolve<bool(const std::string&, int)>(IsPopupOpen)
															));
#pragma endregion Popups, Modals

#pragma region Columns
		ImGui.set_function("Columns"						, sol::overload(
																sol::resolve<void()>(Columns),
																sol::resolve<void(int)>(Columns),
																sol::resolve<void(int, const std::string&)>(Columns),
																sol::resolve<void(int, const std::string&, bool)>(Columns)
															));
		ImGui.set_function("NextColumn"						, NextColumn);
		ImGui.set_function("GetColumnIndex"					, GetColumnIndex);
		ImGui.set_function("GetColumnWidth"					, sol::overload(
																sol::resolve<float()>(GetColumnWidth),
																sol::resolve<float(int)>(GetColumnWidth)
															));
		ImGui.set_function("SetColumnWidth"					, SetColumnWidth);
		ImGui.set_function("GetColumnOffset"				, sol::overload(
																sol::resolve<float()>(GetColumnOffset),
																sol::resolve<float(int)>(GetColumnOffset)
															));
		ImGui.set_function("SetColumnOffset"				, SetColumnOffset);
		ImGui.set_function("GetColumnsCount"				, GetColumnsCount);
#pragma endregion Columns

#pragma region Tab Bars, Tabs
		ImGui.set_function("BeginTabBar"					, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginTabBar),
																sol::resolve<bool(const std::string&, int)>(BeginTabBar)
															));
		ImGui.set_function("EndTabBar"						, EndTabBar);
		ImGui.set_function("BeginTabItem"					, sol::overload(
																sol::resolve<bool(const std::string&)>(BeginTabItem),
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool)>(BeginTabItem),
																sol::resolve<std::tuple<bool, bool>(const std::string&, bool, int)>(BeginTabItem)
															));
		ImGui.set_function("EndTabItem"						, EndTabItem);
		ImGui.set_function("SetTabItemClosed"				, SetTabItemClosed);
#pragma endregion Tab Bars, Tabs

#pragma region Docking
#ifndef IMGUI_NO_DOCKING	// Define IMGUI_NO_DOCKING to disable these for compatibility with ImGui's master branch
		ImGui.set_function("DockSpace"						, sol::overload(
																sol::resolve<void(unsigned int)>(DockSpace),
																sol::resolve<void(unsigned int, float, float)>(DockSpace),
																sol::resolve<void(unsigned int, float, float, int)>(DockSpace)
															));
		ImGui.set_function("SetNextWindowDockID"			, sol::overload(
																sol::resolve<void(unsigned int)>(SetNextWindowDockID),
																sol::resolve<void(unsigned int, int)>(SetNextWindowDockID)
															));
		ImGui.set_function("GetWindowDockID"				, GetWindowDockID);
		ImGui.set_function("IsWindowDocked"					, IsWindowDocked);
#endif
#pragma endregion Docking

#pragma region Logging / Capture
		ImGui.set_function("LogToTTY"						, sol::overload(
																sol::resolve<void()>(LogToTTY),
																sol::resolve<void(int)>(LogToTTY)
															));
		ImGui.set_function("LogToFile"						, sol::overload(
																sol::resolve<void(int)>(LogToFile),
																sol::resolve<void(int, const std::string&)>(LogToFile)
															));
		ImGui.set_function("LogToClipboard"					, sol::overload(
																sol::resolve<void()>(LogToClipboard),
																sol::resolve<void(int)>(LogToClipboard)
															));
		ImGui.set_function("LogFinish"						, LogFinish);
		ImGui.set_function("LogButtons"						, LogButtons);
		ImGui.set_function("LogText"						, LogText);
#pragma endregion Logging / Capture

#pragma region Clipping
		ImGui.set_function("PushClipRect"					, PushClipRect);
		ImGui.set_function("PopClipRect"					, PopClipRect);
#pragma endregion Clipping

#pragma region Focus, Activation
		ImGui.set_function("SetItemDefaultFocus"			, SetItemDefaultFocus);
		ImGui.set_function("SetKeyboardFocusHere"			, sol::overload(
																sol::resolve<void()>(SetKeyboardFocusHere),
																sol::resolve<void(int)>(SetKeyboardFocusHere)
															));
#pragma endregion Focus, Activation

#pragma region Item/Widgets Utilities
		ImGui.set_function("IsItemHovered"					, sol::overload(
																sol::resolve<bool()>(IsItemHovered),
																sol::resolve<bool(int)>(IsItemHovered)
															));
		ImGui.set_function("IsItemActive"					, IsItemActive);
		ImGui.set_function("IsItemFocused"					, IsItemFocused);
		ImGui.set_function("IsItemClicked"					, sol::overload(
																sol::resolve<bool()>(IsItemClicked),
																sol::resolve<bool(int)>(IsItemClicked)
															));
		ImGui.set_function("IsItemVisible"					, IsItemVisible);
		ImGui.set_function("IsItemEdited"					, IsItemEdited);
		ImGui.set_function("IsItemActivated"				, IsItemActivated);
		ImGui.set_function("IsItemDeactivated"				, IsItemDeactivated);
		ImGui.set_function("IsItemDeactivatedAfterEdit"		, IsItemDeactivatedAfterEdit);
		ImGui.set_function("IsItemToggledOpen"				, IsItemToggledOpen);
		ImGui.set_function("IsAnyItemHovered"				, IsAnyItemHovered);
		ImGui.set_function("IsAnyItemActive"				, IsAnyItemActive);
		ImGui.set_function("IsAnyItemFocused"				, IsAnyItemFocused);
		ImGui.set_function("GetItemRectMin"					, GetItemRectMin);
		ImGui.set_function("GetItemRectMax"					, GetItemRectMax);
		ImGui.set_function("GetItemRectSize"				, GetItemRectSize);
		ImGui.set_function("SetNextItemAllowOverlap"			, SetNextItemAllowOverlap);
#pragma endregion Item/Widgets Utilities

#pragma region Miscellaneous Utilities
		ImGui.set_function("IsRectVisible"					, sol::overload(
																sol::resolve<bool(float, float)>(IsRectVisible),
																sol::resolve<bool(float, float, float, float)>(IsRectVisible)
															));
		ImGui.set_function("GetTime"						, GetTime);
		ImGui.set_function("GetFrameCount"					, GetFrameCount);
		ImGui.set_function("GetStyleColorName"				, GetStyleColorName);
#pragma endregion Miscellaneous Utilities

#pragma region Text Utilities
		ImGui.set_function("CalcTextSize"					, sol::overload(
																sol::resolve<std::tuple<float, float>(const std::string&)>(CalcTextSize),
																sol::resolve<std::tuple<float, float>(const std::string&, const std::string&)>(CalcTextSize),
																sol::resolve<std::tuple<float, float>(const std::string&, const std::string&, bool)>(CalcTextSize),
																sol::resolve<std::tuple<float, float>(const std::string&, const std::string&, bool, float)>(CalcTextSize)
															));
#pragma endregion Text Utilities

#pragma region Color Utilities
		ImGui.set_function("ColorConvertU32ToFloat4"		, ColorConvertU32ToFloat4);
		ImGui.set_function("ColorConvertFloat4ToU32"		, ColorConvertFloat4ToU32);
		ImGui.set_function("ColorConvertRGBtoHSV"			, ColorConvertRGBtoHSV);
		ImGui.set_function("ColorConvertHSVtoRGB"			, ColorConvertHSVtoRGB);
		lua.set_function("IM_COL32", [](sol::variadic_args args) { 								// Want this exposed globally
			if (args.size() == 1 && args[0].is<sol::table>())
			{ 
				sol::table t = args[0].as<sol::table>(); 
				return IM_COL32(t.get_or(1, 0), t.get_or(2, 0), t.get_or(3, 0), t.get_or(4, 255)); 
			} 
			return IM_COL32(args.get<int>(0), args.get<int>(1), args.get<int>(2), args.size() >= 4 ? args.get<int>(3) : 255); 
		});
#pragma endregion Color Utilities

#pragma region Inputs Utilities: Keyboard
//		ImGui.set_function("GetKeyIndex"					, GetKeyIndex);
		ImGui.set_function("IsKeyDown"						, IsKeyDown);
		ImGui.set_function("IsKeyPressed"					, sol::overload(
																sol::resolve<bool(int)>(IsKeyPressed),
																sol::resolve<bool(int, bool)>(IsKeyPressed)
															));
		ImGui.set_function("IsKeyReleased"					, IsKeyReleased);
		ImGui.set_function("SetNextFrameWantCaptureKeyboard", SetNextFrameWantCaptureKeyboard);
#pragma endregion Inputs Utilities: Keyboard

#pragma region Inputs Utilities: Mouse
		ImGui.set_function("IsMouseDown"					, IsMouseDown);
		ImGui.set_function("IsMouseClicked"					, sol::overload(
																sol::resolve<bool(int)>(IsMouseClicked),
																sol::resolve<bool(int, bool)>(IsMouseClicked)
															));
		ImGui.set_function("IsMouseReleased"				, IsMouseReleased);
		ImGui.set_function("IsMouseDoubleClicked"			, IsMouseDoubleClicked);
		ImGui.set_function("IsMouseHoveringRect"			, sol::overload(
																sol::resolve<bool(float, float, float, float)>(IsMouseHoveringRect),
																sol::resolve<bool(float, float, float, float, bool)>(IsMouseHoveringRect)
															));
		ImGui.set_function("IsAnyMouseDown"					, IsAnyMouseDown);
		ImGui.set_function("GetMousePos"					, GetMousePos);
		ImGui.set_function("GetMousePosOnOpeningCurrentPopup", GetMousePosOnOpeningCurrentPopup);
		ImGui.set_function("IsMouseDragging"				, sol::overload(
																sol::resolve<bool(int)>(IsMouseDragging),
																sol::resolve<bool(int, float)>(IsMouseDragging)
															));
		ImGui.set_function("GetMouseDragDelta"				, sol::overload(
																sol::resolve<std::tuple<float, float>()>(GetMouseDragDelta),
																sol::resolve<std::tuple<float, float>(int)>(GetMouseDragDelta),
																sol::resolve<std::tuple<float, float>(int, float)>(GetMouseDragDelta)
															));
		ImGui.set_function("ResetMouseDragDelta"			, sol::overload(
																sol::resolve<void()>(ResetMouseDragDelta),
																sol::resolve<void(int)>(ResetMouseDragDelta)
															));
		ImGui.set_function("GetMouseCursor"					, GetMouseCursor);
		ImGui.set_function("SetMouseCursor"					, SetMouseCursor);
		ImGui.set_function("SetNextFrameWantCaptureMouse"			,SetNextFrameWantCaptureMouse);
#pragma endregion Inputs Utilities: Mouse
		
#pragma region Clipboard Utilities
		ImGui.set_function("GetClipboardText"				, GetClipboardText);
		ImGui.set_function("SetClipboardText"				, SetClipboardText);
#pragma endregion Clipboard Utilities
	}
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif