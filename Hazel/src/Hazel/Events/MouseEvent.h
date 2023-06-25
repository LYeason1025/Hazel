#pragma once

#include "Event.h"

namespace Hazel 
{
	class MouseMovedEvent:public Event
	{
	public:
		MouseMovedEvent(const float mouseX,const float mouseY)
			:m_MouseX(mouseX),m_MouseY(mouseY){}
		
		float GetMouseX() const { return m_MouseX;}
		float GetMouseY() const { return m_MouseY;}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseMoved)
	private:
		 float m_MouseX;
		 float m_MouseY;
	};

	class MouseScrollEvent :public Event
	{
	public:
		MouseScrollEvent(const float offsetX, const float offsetY)
			:m_OffsetX(offsetX), m_OffsetY(offsetY) {}

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetOffsetX() << "," << GetOffsetY();
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
			EVENT_CLASS_TYPE(MouseMoved)
	private:
		float m_OffsetX;
		float m_OffsetY;
	};

	class MouseButtonEvent :public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse| EventCategoryMouseButton| EventCategoryInput)
	protected:
		MouseButtonEvent(const int button)
			:m_Button(button){}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button)
			:MouseButtonEvent(button){}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss<< "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

	EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}

