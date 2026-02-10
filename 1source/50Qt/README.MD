# Qt

* For a description of the different types of projects, see the parent directory README
* Projects that use _Qt_ via Qt Creator (not very portable):
  * `00HelloCounter_QtCreator`
* Projects that use _Qt_ "independently" (no need for Qt Creator, local installation of Qt is needed, layout is defined in code instead of an .ui file):
  * `01HelloCounter_Independent`
  * `02ConceptA`
  * `03Playground`

## Running Qt 6.10.0

### Windows 10 22H2 + Visual Studio 2022

#### 1. Set up Qt

* __1.1.__ Install Qt (<https://www.qt.io/>), choose custom installation:
  * The only component needed is _Qt_ → _Qt 6.10.0_ → _MSVC 2022 64-bit_
  * Additional components can be installed later via _Qt Maintenance Tool_
* __1.2.__ Create a new system environment variable called `QTDIR` with value: `<path_to_qt_installation>\6.10.0\msvc2022_64`
* __1.3.__ Add two new values to system environment variable PATH:
  * `%QTDIR%\bin`
  * `%QTDIR%\dir`

#### 2. Run the sample project

* __2.1.__ Run Visual Studio launcher
* __2.2.__ Select _Open a local folder_
* __2.3.__ Navigate to and select folder with the sample project (`<path_to_this_repository>\1source\50Qt\01HelloCounter_Independent`)
* __2.4.__ Wait until Ouput from CMake says `1> CMake generation finished.`
* __2.5.__ Select _Build_ → _Build All_ &ensp;(or press Ctrl + Shift + B)
* __2.6.__ Select _SampleProject.exe_ next to the green arrow &ensp;(or press F5)

To run this working VS project in CLion, a _Visual Studio toolchain_ must be set up. See [Tutorial: Configure CLion on Windows](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html).

### Linux Debian 13.1 KDE Plasma

* Install Qt (<https://www.qt.io/>)

```bash
sudo apt install libxcb-cursor0 libxcb-cursor-dev

cd "<path_to_this_repository>/1source/50Qt/01HelloCounter_Independent"

export QTDIR=<path_to_qt_installation>/6.10.0/gcc_64/  # Add this line to ~/.bashrc for auto export

cmake -S . -B build

cmake --build build

./build/QtProj
```

To make it work in CLion on Linux:

1. Open the folder with the project in CLion
2. Click on the CMake icon at the bottom left corner
3. Click on the cogwheel icon → _CMake settings_
4. In the _Cache variables_ section of the settings, change _Value_ of _Name_ `Qt6_DIR` to `<path_to_qt_installation>/6.10.0/gcc_64/lib/cmake/Qt6`
