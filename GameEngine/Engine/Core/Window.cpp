#include "../pch.hpp"
#include "Window.hpp"

namespace Engine {
	Window* Window::s_activeWindow = nullptr;

	Window::Window(int width, int height, const std::string& title, WindowMode windowMode)
		: m_Width{ width }, m_Height{ height }, m_Title{ title }, m_WindowMode{ windowMode } {
		InitWindow();
	}

	void Window::InitWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_SAMPLES, 8);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		if (m_WindowMode == Fullscreen) glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		if (m_WindowMode != WindowedFree) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Monitor = glfwGetPrimaryMonitor();
		k_Mode = glfwGetVideoMode(m_Monitor);


		if (m_WindowMode == Fullscreen) {
			m_Window = glfwCreateWindow(k_Mode->width, k_Mode->height, m_Title.c_str(), m_Monitor, nullptr);
			MaximizeWindow();
		}
		else if (m_WindowMode == WindowedMaximized) {
			m_Window = glfwCreateWindow(k_Mode->width, k_Mode->height, m_Title.c_str(), nullptr, nullptr);
			MaximizeWindow();
		}
		else {
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
			CenterWindow();
		}

		assert(m_Window && "Failed to create window!");

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetScrollCallback(m_Window, SetScrollCallback);

		if (m_WindowMode == WindowedFree) {
			glfwSetFramebufferSizeCallback(m_Window, SetWindowResizedCallback);
		}

		glfwSwapInterval(SetVsync ? 1 : 0); // V-Sync
		UpdateWindowSize();
		s_activeWindow = this;
	}

	void Window::SetScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

	}

	void Window::CenterWindow() {
		glm::ivec2 screenCenter = GetCenter();
		int windowWidth, windowHeight;
		glfwGetWindowSize(m_Window, &windowWidth, &windowHeight);
		int posX = screenCenter.x - windowWidth / 2;
		int posY = screenCenter.y - windowHeight / 2;
		glfwSetWindowPos(m_Window, posX, posY);
	}
	void Window::FocusWindow() {
		glfwFocusWindow(m_Window);
	}

	void Window::Destroy() {
		glfwDestroyWindow(m_Window);
	}

	glm::ivec2 Window::GetCenter() const {
		return glm::ivec2(k_Mode->width / 2, k_Mode->height / 2);
	}

	void Window::MaximizeWindow() {
		glfwMaximizeWindow(m_Window);
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	}

	void Window::MinimizeWindow() {
		glfwIconifyWindow(m_Window);
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	}

	bool Window::IsMaximized() const {
		if (m_WindowMode == Fullscreen) {
			return true;
		}
		return glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
	}

	bool Window::IsMinimized() const {
		if (m_WindowMode == Fullscreen) {
			return true;
		}
		return glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
	}

	void Window::SetWindowResizedCallback(GLFWwindow* window, int WIDTH, int HEIGHT) {
		auto _window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		_window->m_WindowResized = true;
		_window->m_Width = WIDTH;
		_window->m_Height = HEIGHT;
		_window->UpdateViewport();
	}

	void Window::UpdateViewport() {
		glViewport(0, 0, m_Width, m_Height);
	}

	void Window::UpdateWindowSize() {
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	}
}