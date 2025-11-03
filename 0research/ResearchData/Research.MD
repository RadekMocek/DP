# Rešerše

* Konkrétní poznámky k samotným IMGUI knihovnám jsou o [soubor vedle](./Libraries.MD)

## Poznámky

* <https://caseymuratori.com/blog_0001>
  * IMGUI je styl psaní kódu GUI aplikací
  * Casey Muratori s tím začal pracovat v roce 2002, myšlenku zveřejnil v roce 2005 formou _public videa_ (_private mailing list_ již _in the fall of 2002_)
  * Snaha o ease-of-use, čitelnost, lepší uspořádání
  * RMGUI: Init (create id1, create id2, ... xaml/programově/...) → Update (???) → Callback (get id1, set id2, ...)
    * Potřeba globálních identifikátorů pro GUI prvky, přistupujeme k nim z různých míst (init, callback metoda)
  * IMGUI: Není nutný init, žádné callbacky, pouze hlavní smyčka (_main update path_)
    * Podobnost k immediate mode drawing
    * V hlavní smyčce si řešíme logiku „sami“
    * Tohle je celá myšlenka; implementováno to může být různě
    * Vhodné pro realtime aplikace, vhodné pro integraci s _unaware components_ (např. 3D aplikace)
    * Nevýhoda je složitá „reflexe“, např. když chceme vědět, jak je náš layout widgetů velký a nějak na to zareagovat – vždy budeme o&nbsp;jeden frame dozadu, nejdřív se to musí vykreslit (např. window autosize)
    * Další nevýhoda: pokud bychom nechtěli vše překreslovat každý snímek, ale aktualizovat jen to potřebné, kód by byl značně nabobtnal
    * Dále <https://archive.org/details/GDM_September_2005/page/n35/mode/2up> – _IMMEDIATE VS. RETAINED MODE_, Table 1, ...
    * _I began to realize that “retained” GUI code design has all the same drawbacks that typically cause us to avoid using retained-mode APIs in graphics. I experimented with having the GUI code operate in a more immediate fashion, like an immediate-mode graphics API, and found that everything was simpler, more powerful, and could span the gamut of both 2D and 3D interaction seamlessly._
* [IMGUI tutorial by Jari Komppa](http://iki.fi/sol/imgui/)
  * _There's a bit of global data that's shared by all of the widgets that enables them to work. There's no setup phase, but if a widget needs some data to show it's state (say, a scroll bar, text edit field, etc), the state data is owned by the host application and not the widget. This is surprisingly handy and performance-friendly, as there's no querying and message-sending involved. There's also no cleanup required, except for the data that you have allocated yourself. The widgets only exist when they're called, so you'll need to ask for them each frame you want to use them._
  * _Nothing is ever simply positive, and IMGUI does have its problems. The most obvious one is that it's just about as anti-OOP as you can get, so it may feel wrong for you. Other problems are related to the fact that the widgets don't really exist except when they are queried, and as such things like automatic layouts or keyboard focus get somewhat more difficult._
* <https://news.ycombinator.com/item?id=24318313>
  * _it's important to point out that "immediate mode" only applies to the API, not to the implementation_, více [zde](http://geoffprewett.com/blog/software/ImmediateModeGUIIsAMirage.html)
* <https://github.com/ocornut/imgui/wiki/About-the-IMGUI-paradigm>
  * _Nowadays I am starting to believe that the term has caused more harm than benefits, because it suggests there are two camps "IMGUI" vs "RMGUI". The reality is there is a continuum of possibilities over multiple unrelated axises. Many of them haven't been explored enough, as popular IMGUI libraries have been designed for certain needs and not others._
  * Viz _Modeless write-up_
* [Introducing Clay - High Performance UI Layout in C | YouTube](https://youtu.be/DYWTw19_8r4)
  * V IMGUI rešíme jak má UI vypadat právě teď, podle aktuálního stavu; v RMGUI řešíme přechod z předchozího stavu do aktuálního
* Knihy? Papers?
  * [Digital Image Processing: Practical Approach](https://link.springer.com/chapter/10.1007/978-3-319-96634-2_2) obsahuje nějaké imgui snippety
  * [Exploring the immediate mode GUI concept for graphical user interfaces in mixed reality applications](https://www.researchgate.net/publication/386416751_Exploring_the_immediate_mode_GUI_concept_for_graphical_user_interfaces_in_mixed_reality_applications)
  * [2025 paper, není anglicky](http://vestnik2079-5459.khpi.edu.ua/article/view/325758)

## Reference

* <https://caseymuratori.com/blog_0001> – prvotní definice IMGUI
* [What are the algorithms and the data structures for GUIs and input management? - Theoretical Computer Science Stack Exchange](https://cstheory.stackexchange.com/questions/20369)
* [IMGUI on C2 WIKI](https://wiki.c2.com/?ImmediateModeGui)
* [CppCon 2016: Nicolas Guillemot "Dear imgui", YouTube, 4 minuty, pěkný slide pros & cons](https://youtu.be/LSRJ1jZq90k)
* [Immediate Mode GUI Is a Mirage](http://geoffprewett.com/blog/software/ImmediateModeGUIIsAMirage.html)
* [Immediate Mode GUIs](https://news.wolfgame.com/post/116650847232/immediate-mode-guis)
* [Johannes Norneby's take on IMGUI](https://www.johno.se/book/imgui.html)
* [__Statefulness in GUIs__](https://samsartor.com/guis-1/)
* [egui readme take on imgui](https://github.com/emilk/egui?tab=readme-ov-file#why-immediate-mode)
* [GIO snippet](https://eliasnaur.com/blog/immediate-mode-gui-programming)

## Co by mě mohlo zajímat u GUI knihoven

* Udělal v tom někdo něco používaného?

* Multiplatformnost

* Vypadá to na všech platformách stejně?

* Jak moc můžu ovlivnit, jak to vypadá?

* Dialogy typu otevřít soubor – systémové nebo vlastní?

* Velikost binárky

* Náročnost na HW při běhu

* Multi-monitor support

* Více oken

* DPI scaling

* Responsive UI?

* Fonty

* Dostupné widgety

* Tvorba custom widgetů

* "Async"

* Drag n Drop

* Klasické vrchní menu, alt zkratky

* Dock

* Lokalizace (vícejazyčná aplikace)

* UTF-8, více fontů

* Přepínaní themes (např. dark/light mode)

* Accesibility
  * _AT-SPI 2_ ?
  * _libatk_ ?
