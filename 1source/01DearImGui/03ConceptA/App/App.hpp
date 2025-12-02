#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

class App
{
public:
	App() = default;
	bool Init();
	void Run();

private:
	// = Members =
	GLFWwindow* window{};
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	const char* window_title = "Dear ImGui :: ConceptA";
	const bool is_dark_mode = false;

	// Fonts
	ImFont* font_default = nullptr;
	ImFont* font_inconsolata_14 = nullptr;
	ImFont* font_inconsolata_18 = nullptr;

	// User state
	ImVec2 m_fps_info_size;
	std::string m_source = "\"Hello\" 40 40\n\"Dear ImGui!\" 160 50";

	// = Functions =
	static void GLFWErrorCallback(int error, const char* description);
	void Start();
	void Update();

	// User functions
	void ModuleMain();
	void ModuleTextEditor();
	void ModuleCanvas();
};
