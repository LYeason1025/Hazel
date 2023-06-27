#include <Hazel.h>
#include <hzpch.h>

class Sandbox:public Hazel::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

Hazel::Application*Hazel::CreateApplicaton() {
	return new Sandbox();
}