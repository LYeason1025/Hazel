#include "hzpch.h"
#include "WindowsWindow.h"


namespace Hazel 
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) 
	{
		m_WindowData.Height = props.Height;
		m_WindowData.Width = props.Width;
		m_WindowData.Title = props.Title;

		HZ_CORE_INFO("Create window {0} {1},{2}", props.Title, props.Height, props.Width);
		
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			HZ_CORE_ASSERT(success, "could not initialized GLFW");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_WindowData.Title.c_str(),nullptr,nullptr);

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		SetVSync(true);
	}

	void WindowsWindow::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() 
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enbale)
	{
		if (enbale)
			glfwSwapInterval(1);
		else
			glfwSwapBuffers(0);

		m_WindowData.VSync = enbale;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_WindowData.VSync;
	}
}