#pragma once
#include "../../Includes/includes.hpp"
#include "../../SDK/UnityEngine/UnityEngine.hpp"

class c_notify_text
{
public:
	Unity_String m_text;
	Color m_color;
	float m_time;

public:
	c_notify_text(const Unity_String text, Color color, float time) : m_text(text), m_color(color), m_time(time) { }
};
#include <vector>
#include <memory>
#include "../Visuals/Visuals.hpp"

class c_notify
{
private:
	std::vector< std::shared_ptr< c_notify_text > > m_notify_text;
public:
	c_notify() : m_notify_text{} {}

	auto push(Unity_String text, float timestamp, Color color = Color(255, 255, 255, 255.f)) -> void {
		m_notify_text.push_back(std::make_shared< c_notify_text >(text, color, timestamp));
	}

	auto run() -> void {
		float x{ 8 }, y{ 5 }, size{ 11 };

		for (size_t idx{ }; idx < m_notify_text.size() && !m_notify_text.empty(); idx++)
		{
			auto& notify = m_notify_text[idx];

			if (Math::fabsf(UnityEngine::Time::get_time() - notify->m_time) > 5.f)
			{
				m_notify_text.erase(m_notify_text.begin() + idx);

				if (!m_notify_text.size())
					return;
			}
		}

		if (m_notify_text.empty())
			return;

		for (size_t i{}; i < m_notify_text.size(); ++i) {
			auto& notify = m_notify_text[i];

			float time_delta = Math::fabsf(UnityEngine::Time::get_time() - notify->m_time);

			Color color = notify->m_color;

			float alpha = 255.f;
			float height = 5 + (16 * i);

			if (time_delta > 5.f - 0.2f)
				alpha = (255 - (((time_delta - (5.f - 0.2f)) / 0.2f) * 255.f));

			if (time_delta < 0.3f)
				alpha = ((time_delta / 0.3f) * 255.f);

			float width = 5;

			if (time_delta < 0.3f)
				width = (time_delta / 0.3f) * static_cast<float>(5);

			if (time_delta > 5.f - 0.2f)
				width = -((time_delta / 0.3f) * static_cast<float>(5));

			color.m_alpha = alpha / 255.f;

			char str[256];
			auto test = utf16_to_utf8(notify->m_text.GetWchar());
			sprintf(str, XS("%ls"), test.c_str());
			std::string WaterMark = str;

			UnityEngine::GL().TextOutline(Vector2(width, height), color, Color::Black(), WaterMark.c_str(), false, 10); 
		}
	}
};

namespace notifcations
{
	inline c_notify object;
}