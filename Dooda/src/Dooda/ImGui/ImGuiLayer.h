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
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float d_time = 0.0f;
	};

}