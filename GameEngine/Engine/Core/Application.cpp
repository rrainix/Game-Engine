#include "Application.hpp"


namespace Engine {
	void Application::Run()
	{
		m_Window.emplace(Window(800, 800, "Engine", WindowMode::WindowedFree));
		m_Window.value().SetVsync(true);

		while (!m_Window.value().ShouldClose()) {
			BeginFrame();
			EndFrame();
		}
	}

	void Application::BeginFrame() {

	}
	void Application::EndFrame() {
		m_Window.value().SwapBuffers();
		glfwPollEvents();
	}

	void Application::Initialize() {

	}
}