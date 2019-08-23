#pragma once

#include "Dooda/Layer.h"

#include "Dooda/Events/KeyEvent.h"
#include "Dooda/Events/MouseEvent.h"
#include "Dooda/Events/ApplicationEvent.h"

namespace Dooda
{

	class DOODA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(/*Timestep ts*/);
		void OnEvent(Event& event);

	private: //Private Functions
		bool OnMouseBuutonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseBuutonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float d_time = 0.0f;
	};

}