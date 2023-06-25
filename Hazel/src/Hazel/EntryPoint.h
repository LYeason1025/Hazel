#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplicaton();

int main(int argc,char** argv) {

	Hazel::Log::Init();
	HZ_CORE_WARN("Initialied Log!");
	HZ_INFO("Hello!");

	auto app = Hazel::CreateApplicaton();
	app->Run();
	delete app;

}

#endif // HZ_PLATFORM_WINDOWS
