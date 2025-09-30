# Rešerše

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
    * Vhodné pro realtime aplikace, vhodné pro integraci s _unaware components_
    * Nevýhoda je složitá „reflexe“, např. když chceme vědět, jak je náš layout widgetů velký a nějak na to zareagovat– vždy budeme o jeden frame dozadu, nejdřív se to musí vykreslit
    * Další nevýhoda: pokud bychom nechtěli vše překreslovat každý snímek, ale aktualizovat jen to potřebné, kód by byl zančně složitější
    * TODO (dodatečné poznámky jsou ještě v blog postu, tohle je zatím jen ze samotného videa)
    * Dále <https://archive.org/details/GDM_September_2005/page/n35/mode/2up> – _IMMEDIATE VS. RETAINED MODE_, Table 1, ...
* <https://solhsa.com/imgui/>
  * _There's a bit of global data that's shared by all of the widgets that enables them to work. There's no setup phase, but if a widget needs some data to show it's state (say, a scroll bar, text edit field, etc), the state data is owned by the host application and not the widget. This is surprisingly handy and performance-friendly, as there's no querying and message-sending involved. There's also no cleanup required, except for the data that you have allocated yourself. The widgets only exist when they're called, so you'll need to ask for them each frame you want to use them._
  * _Nothing is ever simply positive, and IMGUI does have its problems. The most obvious one is that it's just about as anti-OOP as you can get, so it may feel wrong for you. Other problems are related to the fact that the widgets don't really exist except when they are queried, and as such things like automatic layouts or keyboard focus get somewhat more difficult._
* <https://news.ycombinator.com/item?id=24318313>
  * _it's important to point out that "immediate mode" only applies to the API, not to the implementation_, více [zde](http://geoffprewett.com/blog/software/ImmediateModeGUIIsAMirage.html)
* <https://github.com/ocornut/imgui/wiki/About-the-IMGUI-paradigm>
  * TODO
* Knihy? Papers?

## Co mě zajímá u GUI knihoven

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
