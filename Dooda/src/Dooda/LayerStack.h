#pragma once

#include "Dooda/Core.h"
#include "Layer.h"

namespace Dooda
{
	class DOODA_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return d_layers.begin(); }
		std::vector<Layer*>::iterator end() { return d_layers.end(); }
	private:
		std::vector<Layer*> d_layers;
		unsigned int d_layerInsertIndex = 0;
	};
}