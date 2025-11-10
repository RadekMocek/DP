# Nuklear

* Projects that use vcpkg to get GLFW, GLEW, stb and use CMake's FetchContent to get Nuklear (Nuklear's vcpkg repo has some issues):
  * `00SampleProject` – Empty Nuklear project;
  * `01HelloCounter` – HelloCounter (simple counter project for understanding the basic principles of the imgui paradigm)
* Projects that use CMake's FetchContent to get everything (Nuklear, GLFW, glad, stb):
  * `02HelloCounter_NoVcpkg` – HelloCounter

## Running Nuklear with GLFW, glad, FetchContent

Same steps as with [Dear ImGui](../01DearImGui/README.MD#running-dear-imgui-v1919-with-opengl3-glfw-glad).

## Running Nuklear with GLFW, GLEW, vcpkg

Same steps as with [Dear ImGui](../01DearImGui/README.MD#running-dear-imgui-v1919-with-opengl3-glfw-glew-vcpkg).
