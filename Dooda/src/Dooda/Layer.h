#pragma once

#include "Dooda/Core.h"
//#include "Dooda/Core/Timestep.h"
#include "Dooda/Events/Event.h"

namespace Dooda
{

	class DOODA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(/*Timestep ts*/) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}