#pragma once
#include "Window.hpp"
#include "../Graphics/Renderer2D.hpp"
#include <optional>

namespace Engine {
	class Application {
	public:
		void Run();
		void BeginFrame();
		void EndFrame();
	private:
		void Initialize();
		std::optional<Window> m_Window;
		std::optional<Renderer2D> m_Renderer2D;
	};
}