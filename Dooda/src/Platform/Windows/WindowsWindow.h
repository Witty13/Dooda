#pragma once

#include "Dooda/Window.h"
#include <GLFW/glfw3.h>

namespace Dooda
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return d_Data.Width; }
		inline unsigned int GetHeight() const override { return d_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { d_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return d_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* d_Window;
		//GraphicsContext* d_Context;

		struct WindowData
		{
			std::string Title = std::string("Defult");
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData d_Data;
	};
}