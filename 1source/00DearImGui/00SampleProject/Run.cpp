#include "App/App.hpp"

App app;

void main()
{
	if (app.Init()) {
		app.Run();
	}
}
