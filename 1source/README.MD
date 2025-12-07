\#|"Paradigm"|Name/link|Lang|License|nStars <sup>\*</sup>|Created|Bindings/abstractions
:--|---|---|---|:--|--:|:-:|---
01|_immediate_|[__Dear ImGui__](https://github.com/ocornut/imgui)|C++|[MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)|69 315|2014|[_many_](https://github.com/ocornut/imgui/wiki/Bindings#language-bindings)
02|_immediate_|[__egui__](https://github.com/emilk/egui)|Rust|[MIT](https://github.com/emilk/egui/blob/main/LICENSE-MIT) or Apache-2.0|27 111|2018|[.NET](https://github.com/DouglasDwyer/Egui.NET)
03|_immediate_|[__Nuklear__](https://github.com/Immediate-Mode-UI/Nuklear)|C|[MIT](https://github.com/Immediate-Mode-UI/Nuklear/blob/master/LICENSE) or Unlicense|10 554|2015|[_few_](https://github.com/Immediate-Mode-UI/Nuklear?tab=readme-ov-file#bindings)
04|_immediate_|[__microui__](https://github.com/rxi/microui)|C|[MIT](https://github.com/rxi/microui/blob/master/LICENSE)|5 140|2018|[Go](https://github.com/gabstv/microui-go), [Python](https://github.com/shakfu/pymui)
05|_immediate_|[__raygui__](https://github.com/raysan5/raygui)|C|[Zlib](https://github.com/raysan5/raygui/blob/master/LICENSE)|4 437|2014|[C++](https://github.com/scastd/raygui-cpp), [Raku](https://github.com/vushu/raygui-raku)
06|_immediate_|[__Gio__](https://github.com/gioui/gio)|Go|[MIT](https://github.com/gioui/gio/blob/main/LICENSE) or Unlicense|2 059|2019|—
😬|_immediate_|[__dvui__](https://github.com/david-vanderson/dvui)|Zig|[MIT](https://github.com/david-vanderson/dvui/blob/main/LICENSE)|993|2022|—
&nbsp; | | | | | | | &nbsp;
50|_retained_|[__Qt__](https://www.qt.io/product/framework)|C++|GPL, [LGPL](https://doc.qt.io/qt-6/lgpl.html) or commercial|—|1995|[_many_](https://wiki.qt.io/Language_Bindings)
51|_retained_|[__Avalonia__](https://github.com/AvaloniaUI/Avalonia)|C\#|[MIT](https://github.com/AvaloniaUI/Avalonia/blob/master/licence.md)|29 284|2013|(_any .NET language_)

<sup>\*</sup> GitHub repository stars on 2025-11-12

<br>

Project type|Description
---|---
`SampleProject`|Empty project for a given library ready for tinkering.
`Playground`|Project for testing given library features as part of the research.
`HelloCounter`|Simple project for understanding the basic principles of the IMGUI paradigm. Contains label that shows counter value. The counter can count from 1 to 5 by pushing buttons `+` and `-`. "Hello" label is displayed when counter==3. Buttons are disabled appropriately. Also contains menu bar with option to show pop-up window. [Screenshot](../2thesis/img/imgui_qt_win10_plasma.png).
`ConceptA`|The final example app for this project should be a WYSIWYM diagram editor, where half of the window is a text editor and the other half shows the resulting diagram. This project, `ConceptA`, attempts to make a simple "sketch" in this direction so that the properties of individual libraries that will be useful in the final application, such as multi-line text fields or 2D primitive rendering, can be tested.

<br>

Other dependencies:

* [GLFW](https://www.glfw.org/) ([zlib](https://www.glfw.org/license))
* [GLEW](https://glew.sourceforge.net/) ([Modified BSD](https://github.com/nigels-com/glew/blob/master/LICENSE.txt))
* [FreeType](https://gitlab.freedesktop.org/freetype/freetype) ([Custom](https://gitlab.freedesktop.org/freetype/freetype/-/blob/master/docs/FTL.TXT))
* [imgui-glfw-glad-glm](https://github.com/cmmw/imgui-glfw-glad-glm) ([MIT](https://github.com/cmmw/imgui-glfw-glad-glm/blob/master/LICENSE.md))
* [glad](https://github.com/Dav1dde/glad) ([MIT](https://github.com/Dav1dde/glad/blob/glad2/LICENSE))
* [stb](https://github.com/nothings/stb) ([MIT](https://github.com/nothings/stb/blob/master/LICENSE))
* [SDL2](https://github.com/libsdl-org/SDL) ([zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt))
* [raylib](https://github.com/raysan5/raylib) ([zlib](https://github.com/raysan5/raylib/blob/master/LICENSE))
