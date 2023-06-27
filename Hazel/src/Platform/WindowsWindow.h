#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>
namespace Hazel {
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		unsigned int GetWidth()  const override { return m_WindowData.Width; }
		unsigned int GetHeight() const override { return m_WindowData.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.EventCallback = callback; };
		void SetVSync(bool enbale) override;
		bool IsVSync() const override;
	private:
		void Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Height;
			unsigned int Width;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_WindowData;
	};
	
}