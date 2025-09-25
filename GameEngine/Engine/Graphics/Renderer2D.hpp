#pragma once

namespace Engine {
	class Renderer2D {
	public:
		void Initialize();
		void BeginFrame();
		void EndFrame();
	private:
		void Shutdown();
	};
}