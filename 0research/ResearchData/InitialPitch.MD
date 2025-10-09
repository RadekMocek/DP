# Grafické uživatelské rozhraní v režimu okamžitého vykreslování

Grafické API mohou fungovat ve dvou režimech: immediate (_okamžitý_) a retained (_soběstačný_). Z pohledu abstrakce je soběstačný mód na vyšší úrovni, kdy knihovna spravuje objekty ve scéně a od aplikace přijímá příkazy typu _přidej objekt_, _odeber objekt_ apod. Příkaz typu _vybuduj scénu_ pak provede kompletní vykreslení. V&nbsp;okamžitém módu si informace o objektech ve scéně uchovává aplikace a knihovně posílá jednotlivé příkazy pro vykreslování. V současnosti na poli tvorby 3D aplikací dominuje okamžitý režim.

Podobně lze nahlížet na chod desktopových GUI aplikací. V soběstačném (_RMGUI_) režimu se knihovna stará o&nbsp;vykreslování ovládacích prvků. Události jsou řazeny do fronty a aplikace na ně reaguje pomocí callback metod. Pomyslná fronta událostí a update smyčka jsou před aplikačním kódem „skryty“. V okamžitém (_IMGUI_) režimu aplikace přímo reší vykreslování a reakce na události.

Pro vývoj GUI aplikací se běžně používá nějaká forma RMGUI (Qt, WPF, ...), nebo se nasazuje webová aplikace společně s chromiem pomocí Electronu. IMGUI je sice poměrně starý koncept (~2002), ale některé IMGUI knihovny jsou stále ve vývoji a některé programy toto paradigma úspěšně využívají. Objevují se diskuse o jeho ne/efektivitě a jiných ne/výhodách, nenašel jsem ale žádný „akademičtější deep dive“.

Proto mě napadá zvolit si nějaký IMGUI framework (Dear ImGui, Nuklear, libGDX, ...) a implementovat v něm ukázkovou aplikaci. Nebo to zkusit kompletně od základů pomocí Direct2D/OpenGL/OpenVG (?). Tuto aplikaci pak znovu implementovat v něčem tradičnějším a porovnat výsledky (HW vytížení, velikost binárky).

## Motivace

* <https://blog.johnnovak.net/2016/05/29/cross-platform-gui-toolkit-trainwreck-2016-edition/>
* <https://www.forrestthewoods.com/blog/proving-immediate-mode-guis-are-performant/> – porovnávat pouze IMGUI a Electron je extrémní, ale porovnání např. IMGUI, WPF, Qt, Electron ve více kategoriích by dávalo smysl

## Ukázková aplikace

Napadá mě jednoduchý editor stavových/class diagramů. Preferuji WYSIWYM před WYSIWYG. To je např. Mermaid, ten ale nedává žádnou kontrolu pro umístění jednotlivých uzlů apod. Běžně používám Draw.io, to je ale na mě někdy až zbytečně komplexní: když chci hnout s uzlem, tak se to s sebou snaží dynamicky vzít všechny přidružené hrany... to bych raději dělal ručně. Zkrátka by se mi líbilo něco víc _simple studid_. V jedné části obrazovky by byl kód ve stylu XML/JSON a v druhé výsledný diagram: obdélníčky s textem spojené šipkami :).

## Nástřel zadání

1. Rešerše IMGUI
2. Návrh ukázkové aplikace
3. Implementace ukázkové aplikace ve vybraných knihovnách
4. „Benchmark“
