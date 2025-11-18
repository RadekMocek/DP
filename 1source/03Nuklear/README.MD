# Nuklear

* For a description of the different types of projects, see the parent directory README
* Projects that use vcpkg to get _GLFW_, _GLEW_, _stb_ and use CMake's FetchContent to get _Nuklear_ (Nuklear's vcpkg repo has some issues):
  * `00SampleProject`
  * `01HelloCounter`
* Projects that use CMake's FetchContent to get everything (_Nuklear_, _GLFW_, _glad_, _stb_):
  * `02HelloCounter_NoVcpkg`

## Running Nuklear with GLFW, glad, FetchContent

Same steps as with [Dear ImGui](../01DearImGui/README.MD#running-dear-imgui-v1919-with-opengl3-glfw-glad).

## Running Nuklear with GLFW, GLEW, vcpkg

Same steps as with [Dear ImGui](../01DearImGui/README.MD#running-dear-imgui-v1919-with-opengl3-glfw-glew-vcpkg).
