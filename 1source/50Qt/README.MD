# Qt

* For a description of the different types of projects, see the parent directory README
* `00HelloCounter_QtCreator` – project made in Qt Creator, so not very compatible
* `01HelloCounter_Independent` – this project doesn't need Qt Creator (and defines layout in code instead of an .ui file), local installation of Qt is needed

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

### Linux Debian 13.1 KDE Plasma

* Install Qt (<https://www.qt.io/>)

```bash
sudo apt install libxcb-cursor0 libxcb-cursor-dev

cd "<path_to_this_repository>/1source/50Qt/01HelloCounter_Independent"

export QTDIR=<path_to_qt_installation>/6.10.0/gcc_64/

cmake -S . -B build

cmake --build build

./build/QtProj
```
