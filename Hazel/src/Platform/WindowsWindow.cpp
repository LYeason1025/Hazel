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

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_WindowData.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		SetVSync(true);



		glfwSetWindowSizeCallback(m_Window, []
		(GLFWwindow* Window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(Window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);

		data.EventCallback(event);

			});


		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			}
		);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
					}
				);
				
				glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
					}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			}
		);
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