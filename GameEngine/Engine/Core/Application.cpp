#include "Application.hpp"


namespace Engine {
	void Application::Run()
	{
		Initialize();

		// Main loop
		while (!m_Window.value().ShouldClose()) {
			BeginFrame();
			EndFrame();
		}
	}

	void Application::BeginFrame() {
		m_Renderer2D.value().BeginFrame();
	}

	void Application::EndFrame() {
		m_Renderer2D.value().EndFrame();
		m_Window.value().SwapBuffers();
		glfwPollEvents();
	}

	void Application::Initialize() {

		m_Window.emplace(Window(800, 800, "Engine", WindowMode::WindowedFree));
		m_Window.value().SetVsync(true);

		m_Renderer2D.emplace(Renderer2D());
		m_Renderer2D.value().Initialize();
	}
}