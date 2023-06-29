#include<hzpch.h>


#include "GLFW/glfw3.h"
#include "Application.h"

#include "Log.h"


namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispathcer(event);
		dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", event);
	}



	void  Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	HZ_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	HZ_TRACE(e);
		//}
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}

	
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	
}

