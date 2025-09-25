#include <iostream>
#include "Core/Application.hpp"


int main() {
	std::cout << "Engine!";
	Engine::Application app{};
	app.Run();
	return 0;
}