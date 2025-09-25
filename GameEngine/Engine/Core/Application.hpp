#pragma once
#include "Window.hpp"
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
	};
}