# Knihovny

## IMGUI

Name|Lang|License|nStars|Active|Bindings/abstrakce|...
---|---|:-:|--:|:-:|---|---
[Dear ImGui](https://github.com/ocornut/imgui)|C++|MIT|68 500|✓|[mnoho](https://github.com/ocornut/imgui/wiki/Bindings#language-bindings)|[...](../1source/00DearImGui)
[egui](https://github.com/emilk/egui)|Rust|MIT or Apache-2.0|26 600|✓|[.NET](https://github.com/DouglasDwyer/Egui.NET)|[...](../1source/01egui)
[Clay](https://github.com/nicbarker/clay)|C|Zlib|15 500|✓|[více](https://github.com/nicbarker/clay/tree/main/bindings)|[...](../1source/02ClayMan)
[Nuklear](https://github.com/Immediate-Mode-UI/Nuklear)|C|MIT or Unlicense|10 400|5 months ago|[více](https://github.com/Immediate-Mode-UI/Nuklear?tab=readme-ov-file#bindings)|[...](../1source/03Nuklear)
[microui](https://github.com/rxi/microui)|C|MIT|5 000|last year|[Go](https://github.com/gabstv/microui-go)|[...](../1source/04microui)
[raygui](https://github.com/raysan5/raygui)|C|Zlib|4 300|✓|[C++](https://github.com/scastd/raygui-cpp), [Raku](https://github.com/vushu/raygui-raku)|[...](../1source/05raygui)
[Gio](https://github.com/gioui/gio)|Go|MIT or Unlicense|2 000|✓|—|[...](../1source/06Gio)
[koi](https://github.com/johnnovak/koi)|Nim|WTFPL|87|✓|—|&nbsp;

### Dear ImGui

* Široce používané – hry, nástroje
* Nespočet widgetů a funkcí
* Podporuje i build pro web✓ a android?
* [Interaktivní „manuál“](https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html)
* Výňatky z GitHubu:
  * Create content creation tools and visualization / debug tools (as opposed to UI for the average end-user)
  * It favors simplicity and productivity toward this goal and lacks certain features commonly found in more high-level libraries. Among other things, full internationalization (right-to-left text, bidirectional text, text shaping etc.) and accessibility features are not supported.
  * API tries to minimize superfluous state duplication, state synchronization, and state retention from the user's point of view. It lends itself to creating dynamic user interfaces.
  * Dear ImGui outputs vertex buffers and command lists that you can easily render in your application.
* Odvození:
  * [Hello ImGui](https://github.com/pthom/hello_imgui) a od něho odvozený [ImGui Bundle](https://github.com/pthom/imgui_bundle) včetně Python bindings

### egui

* Nespočet widgetů a funkcí (méně než Dear ImGui, ale stále dostačující)
* Podporuje i build pro web✓ a android?
* Accessibility via AccessKit

### Clay

* Jedná se „pouze“ o UI layout library: obsahuje prostředky hlavně pro pozicování, pak text, obrázek; a zbytek je v podstatě na programátorovi
* ~4KLOC header file with zero dependencies
* 20 000 FPS, ~6 MB memory usage
* Podporuje i build pro web

### Nuklear

* ~18KLOC header file with zero dependencies
* Hodně DIY
* __-__ Textbox umí pohybovat s kurzorem, ale neumí označovat text a neumí ctrl+v

### mikroui

* [Web demo](https://floooh.github.io/sokol-html5/sgl-microui-sapp.html), [Post a screenshot](https://github.com/rxi/microui/issues/35#issuecomment-662313343)
* Dostupné prvky: window, scrollable panel, button, slider, textbox, label, checkbox, wordwrapped text
* ~1KLOC, fixed-memory usage
* __-__ Textbox neumí pohybovat s kurzorem a označovat text
* __-__ Potřeba dopsat si vlastní renderer

### raygui

* ~5KLOC, header-only library with dependency on raylib
* Přes 20 dostupných prvků
* __-__ Textbox umí pohybovat s kurzorem, ale neumí označovat text a neumí ctrl+v

### Gio

* Podporuje i build pro web a android/ios
* __+__ „Plnohodnotný“ text input widget
* [Showcase](https://gioui.org/doc/showcase), vypadá použitelně

## Ostatní

### RMGUI

* [wxWidgets](https://wxwidgets.org/)
* [FLTK](https://github.com/fltk/fltk)
* Qt
* GTK
* [MFC](https://learn.microsoft.com/en-us/cpp/mfc/mfc-desktop-applications?view=msvc-170)
* .NET (official: WinForms, WPF, MAUI; 3rd party: Avalonia, Uno, ...)
* JavaFX, Swing
* pascal, Delphi, Lazarus
* Racket GUI
* [HikoGUI](https://hikogui.org/)
* [libgdx](https://github.com/libgdx/libgdx), zaměřeno na videohry, lze použít pouze UI modul, ukázka programu: <http://en.esotericsoftware.com/>

### Kuriozity

* [LIBTWO](https://github.com/hugoam/two/blob/master/docs/ui.md)
* [rui](https://github.com/audulus/rui)
* <https://publish.obsidian.md/xybre/permalink/60cc03b9-2e66-4a8a-a737-1e6e92105b53> zajímavý web
