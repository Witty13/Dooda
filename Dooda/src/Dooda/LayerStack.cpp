#include "Ddpch.h"
#include "LayerStack.h"

namespace Dooda
{

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : d_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		d_layers.emplace(d_layers.begin() + d_layerInsertIndex, layer);
		d_layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		d_layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(d_layers.begin(), d_layers.begin() + d_layerInsertIndex, layer);
		if (it != d_layers.begin() + d_layerInsertIndex)
		{
			layer->OnDetach();
			d_layers.erase(it);
			d_layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(d_layers.begin() + d_layerInsertIndex, d_layers.end(), overlay);
		if (it != d_layers.end())
		{
			overlay->OnDetach();
			d_layers.erase(it);
		}
	}
}