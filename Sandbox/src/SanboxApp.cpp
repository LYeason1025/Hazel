#include <hzpch.h>
#include <Hazel.h>


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