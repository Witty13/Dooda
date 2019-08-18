#pragma once

#include "Event.h"

namespace Dooda {

	class DOODA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: d_MouseX(x), d_MouseY(y) {}

		inline float GetX() const { return d_MouseX; }
		inline float GetY() const { return d_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << d_MouseX << ", " << d_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float d_MouseX, d_MouseY;
	};

	class DOODA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: d_XOffset(xOffset), d_YOffset(yOffset) {}

		inline float GetXOffset() const { return d_XOffset; }
		inline float GetYOffset() const { return d_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float d_XOffset, d_YOffset;
	};

	class DOODA_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return d_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: d_Button(button) {}

		int d_Button;
	};

	class DOODA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << d_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class DOODA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << d_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}