#include <Dooda.h>

class SandBox : public Dooda::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Dooda::Application* Dooda::CreateApplication()
{
	return new SandBox;
}