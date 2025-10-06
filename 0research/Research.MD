# Rešerše

* Tabulka s IMGUI knihovnami je o [soubor vedle](./Links.MD#imgui) :)

## Poznámky

* <https://caseymuratori.com/blog_0001>
  * IMGUI je styl psaní kódu GUI aplikací
  * Casey Muratori s tím začal pracovat v roce 2002, myšlenku zveřejnil roku 2005
  * Snaha o ease-of-use, čitelnost, lepší uspořádání
  * RMGUI: Init (create id1, create id2, ... xaml/programově/...) → Update (???) → Callback (get id1, set id2, ...)
    * Potřeba globálních identifikátorů pro GUI prvky, přistpujeme k nim z různých míst (init, callback metoda)
  * IMGUI: Není nutný init, žádné callbacky, pouze hlavní smyčka (_main update path_)
    * Podobnost k immediate mode drawing
    * V hlavní smyčce si řešíme logiku „sami“
    * Tohle je celá myšlenka; implementováno to může být různě
    * Vhodné pro realtime aplikace, vhodné pro integraci s _unaware components_ (např. 3D aplikace)
    * Nevýhoda je složitá „reflexe“, např. když chceme vědět, jak je náš layout widgetů velký a nějak na to zareagovat – vždy budeme o&nbsp;jeden frame dozadu, nejdřív se to musí vykreslit
    * Další nevýhoda: pokud bychom nechtěli vše překreslovat každý snímek, ale aktualizovat jen to potřebné, kód by byl značně nabobtnal
    * Dále <https://archive.org/details/GDM_September_2005/page/n35/mode/2up> – _IMMEDIATE VS. RETAINED MODE_, Table 1, ...
    * _I began to realize that “retained” GUI code design has all the same drawbacks that typically cause us to avoid using retained-mode APIs in graphics. I experimented with having the GUI code operate in a more immediate fashion, like an immediate-mode graphics API, and found that everything was simpler, more powerful, and could span the gamut of both 2D and 3D interaction seamlessly._
* <https://solhsa.com/imgui/>
  * _There's a bit of global data that's shared by all of the widgets that enables them to work. There's no setup phase, but if a widget needs some data to show it's state (say, a scroll bar, text edit field, etc), the state data is owned by the host application and not the widget. This is surprisingly handy and performance-friendly, as there's no querying and message-sending involved. There's also no cleanup required, except for the data that you have allocated yourself. The widgets only exist when they're called, so you'll need to ask for them each frame you want to use them._
  * _Nothing is ever simply positive, and IMGUI does have its problems. The most obvious one is that it's just about as anti-OOP as you can get, so it may feel wrong for you. Other problems are related to the fact that the widgets don't really exist except when they are queried, and as such things like automatic layouts or keyboard focus get somewhat more difficult._
* <https://news.ycombinator.com/item?id=24318313>
  * _it's important to point out that "immediate mode" only applies to the API, not to the implementation_, více [zde](http://geoffprewett.com/blog/software/ImmediateModeGUIIsAMirage.html)
* <https://github.com/ocornut/imgui/wiki/About-the-IMGUI-paradigm>
  * _Nowadays I am starting to believe that the term has caused more harm than benefits, because it suggests there are two camps "IMGUI" vs "RMGUI". The reality is there is a continuum of possibilities over multiple unrelated axises. Many of them haven't been explored enough, as popular IMGUI libraries have been designed for certain needs and not others._
  * Viz _Modeless write-up_
* Knihy? Papers?
  * [Digital Image Processing: Practical Approach](https://link.springer.com/chapter/10.1007/978-3-319-96634-2_2) obsahuje nějaké imgui tutoriály
  * [Exploring the immediate mode GUI concept for graphical user interfaces in mixed reality applications](https://www.researchgate.net/publication/386416751_Exploring_the_immediate_mode_GUI_concept_for_graphical_user_interfaces_in_mixed_reality_applications)
  * [2025 paper, není anglicky](http://vestnik2079-5459.khpi.edu.ua/article/view/325758)

## Co mě zajímá u GUI knihoven

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

* "Async"

* Drag n Drop

* Klasické vrchní menu, alt zkratky

* Dock

* Lokalizace (vícejazyčná aplikace)

* Přepínaní themes (např. dark/light mode)
