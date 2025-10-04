# Running Dear ImGui with OpenGL3, GLFW, vcpkg

## Windows 10 22H2 + Visual Studio 2022

### Prerequisites

* [Visual Studio](https://visualstudio.microsoft.com/downloads/) with C++ development workload and [CMake component](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation)
* [Git](https://git-scm.com/downloads)

### 1. Set up vcpkg

* __1.1.__ Open PowerShell where you want the vcpkg to be installed and run these commands:

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

* __1.1.__ Create new user environment variable called `VCPKG_ROOT` and set it to vcpkg's root directory
* __1.2.__ Add `%VCPKG_ROOT%` to `Path`

### 2. Run the sample project

* __2.1.__ Run Visual Studio launcher
* __2.2.__ Select _Open a local folder_
* __2.3.__ Navigate to and select folder with the sample project (`...\1source\00DearImGui\00SampleProject`)
* __2.4.__ Wait until Ouput from CMake says `1> CMake generation finished.`
* __2.5.__ Select _Build_ → _Build All_ &ensp;(or press Ctrl + Shift + B)
* __2.6.__ Select _SampleProject.exe_ next to the green arrow &ensp;(or press F5)

## Linux Debian 13.1 KDE Plasma

```bash
# Install dependencies

sudo apt install curl cmake ninja-build

# Set up vcpkg

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh

# Navigate to sample project directory, build, run

cd "<path_to_this_repository>/1source/00DearImGui/00SampleProject"

export VCPKG_ROOT=<path_to_bootstrapped_vcpkg> && export PATH=$VCPKG_ROOT:$PATH

cmake --preset=vcpkg

cmake --build build

./build/SampleProject
```
