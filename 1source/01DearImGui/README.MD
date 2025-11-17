# Dear ImGui

* Projects that use vcpkg to get _Dear ImGui_, _GLFW_, _GLEW_, _FreeType_:
  * `00SampleProject` – Empty Dear ImGui project
  * `01HelloCounter` – HelloCounter (simple counter project for understanding the basic principles of the IMGUI paradigm)
* Projects that use CMake's FetchContent to get _Dear ImGui_, _GLFW_, _glad_:
  * `02HelloCounter_NoVcpkg` – HelloCounter

&nbsp;

* [Running Dear ImGui with FetchContent](#running-dear-imgui-v1919-with-opengl3-glfw-glad)
  * [Windows 10 22H2 + Visual Studio 2022](#windows-10-22h2--visual-studio-2022)
  * [Linux Debian 13.1 KDE Plasma](#linux-debian-131-kde-plasma)
* [Running Dear ImGui with vcpkg](#running-dear-imgui-v1919-with-opengl3-glfw-glew-vcpkg)
  * [Windows 10 22H2 + Visual Studio 2022](#windows-10-22h2--visual-studio-2022-via-vcpkg)
  * [Linux Debian 13.1 KDE Plasma](#linux-debian-131-kde-plasma-via-vcpkg)
* [Resources](#resources)

## Running Dear ImGui [v1.91.9] with OpenGL3, GLFW, glad

### Windows 10 22H2 + Visual Studio 2022

* __1.__ Make sure you have [Visual Studio](https://visualstudio.microsoft.com/downloads/) with C++ development workload and [CMake component](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation) installed
* __2.__ Run Visual Studio launcher
* __3.__ Select _Open a local folder_
* __4.__ Navigate to and select folder with the sample project (`<path_to_this_repository>\1source\01DearImGui\02HelloCounter_NoVcpkg`)
* __5.__ Wait until Ouput from CMake says `1> CMake generation finished.`
* __6.__ Select _Build_ → _Build All_ &ensp;(or press Ctrl + Shift + B)
* __7.__ Select _ImGuiApp.exe_ next to the green arrow &ensp;(or press F5)

### Linux Debian 13.1 KDE Plasma

```bash
cd "<path_to_this_repository>/1source/50Qt/02HelloCounter_NoVcpkg"

cmake -S . -B build

cmake --build build

./build/ImGuiApp
```

OpenGL version is set to 3.3 Core, this can be changed in the code on these lines:

* `CMakeLists.txt`:
  * `set(IGG_GLAD_GL_CORE ON CACHE BOOL "" FORCE)`
  * `set(IGG_GLAD_GL_VERSION "3.3" CACHE STRING "" FORCE)`
* `App/AppBoilerplate.cpp`:
  * `const char* glsl_version = "#version 330";`
  * `glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);`
  * `glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);`
  * Comment out other two `glfwWindowHint` lines if your OpenGL version does not support it

## Running Dear ImGui [v1.91.9] with OpenGL3, GLFW, GLEW, vcpkg

### Windows 10 22H2 + Visual Studio 2022 (via vcpkg)

#### Prerequisites

* [Visual Studio](https://visualstudio.microsoft.com/downloads/) with C++ development workload and [CMake component](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation)
* [Git](https://git-scm.com/downloads)

#### 1. Set up vcpkg

* __1.1.__ Open PowerShell where you want the vcpkg to be installed and run these commands:

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

* __1.1.__ Create new user environment variable called `VCPKG_ROOT` and set it to vcpkg's root directory
* __1.2.__ Add `%VCPKG_ROOT%` to `Path`

#### 2. Run the sample project

* __2.1.__ Run Visual Studio launcher
* __2.2.__ Select _Open a local folder_
* __2.3.__ Navigate to and select folder with the sample project (`<path_to_this_repository>\1source\01DearImGui\00SampleProject`)
* __2.4.__ Wait until Ouput from CMake says `1> CMake generation finished.`
* __2.5.__ Select _Build_ → _Build All_ &ensp;(or press Ctrl + Shift + B)
* __2.6.__ Select _SampleProject.exe_ next to the green arrow &ensp;(or press F5)

### Linux Debian 13.1 KDE Plasma (via vcpkg)

```bash
# Install dependencies

sudo apt install curl cmake ninja-build

# Set up vcpkg

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh

# Navigate to sample project directory, build, run

cd "<path_to_this_repository>/1source/01DearImGui/00SampleProject"

export VCPKG_ROOT=<path_to_bootstrapped_vcpkg> && export PATH=$VCPKG_ROOT:$PATH

cmake --preset=vcpkg

cmake --build build

./build/SampleProject
```

## Resources

* [Getting started](https://github.com/ocornut/imgui/wiki/Getting-Started)
* [wiki](https://github.com/ocornut/imgui/wiki)
* [FAQ](https://github.com/ocornut/imgui/blob/master/docs/FAQ.md)
* [Interactive "manual"](https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html)
* [Useful Extensions](https://github.com/ocornut/imgui/wiki/Useful-Extensions)
* [Using fonts](https://github.com/ocornut/imgui/blob/master/docs/FONTS.md)
