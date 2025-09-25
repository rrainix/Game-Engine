#include "Renderer2D.hpp"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Engine {
	void Renderer2D::Initialize() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			// To do
		}

		glClearColor(0.05f, 0.15f, 0.45f, 0.45f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void  Renderer2D::BeginFrame() {

	}

	void Renderer2D::EndFrame() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::Shutdown() {

	}
}