# DP draft

## Implementace

### Implementace v Dear ImGui

#### Použité technologie a závislosti

* GLFW 3.3 vs. 3.4
* S Monospace fontem se lépe pracuje

#### Vykreslení diagramu

* Při posouvání canvasu měním vzhled kurzoru pomocí GLFW
* "Font size based zooming", MW scroll nad canvasem celočíselně přičítá/odečítá velikosti písma v canvasu, ze kterého se pak odvodí celkový _canvas zoom level_; protože neceločíselná velikost písma v Dear ImGui produkuje mírně rozmazaný text (i po updatu na 1.92.6)
* Také když MW měnil přímo float zoom_level, tak se poměr velikosti písma a obdélníku v node mírně měnil, (velikost vykreslovaného písma je zaručena asi jen do určité přesnosti, která je nižší než pro vykreslování obdélníku)

#### Export diagramu do formátu SVG

* Problémy: multiline text, rgba (webový prohlížeč to umí, ale můj Inkscape a qView ne, dělám SVG aby to vypadalo správně i v těchto programech)
* Používám mírně upravenou header only knihovnu simple-svg
* Po kliknutí na export se pro příští frame nastaví proměnná typu _is\_svg\_requested_ na true, a v tomto průchodu smyčkou se kromě vykreslování buduje i SVG dokument. Moje logika, která volá simple-svg, se chová jako stavový automat.
* Pro usnadnění před exportem resetuji canvas scrolling a zoom level.
* Pro správné pořadí vykreslování (tedy aby i v SVG fungovala Z souřadnice), řadím jednotlivé svg::Shapes do prioritní fronty. Jedná se o&nbsp;abstraktní classu, takže zabaleno do unique_ptr.
* Knihovnu jsem si upravil, aby podporovala průhlednost, není to ale ideální a podporuji pouze fill opacity. Stroke opacity už neumím, to by vyžadovalo větší zásah do knihovny, nebo možná lépe napsat si vlastní.
* Uživatelův diagram může klidně začínat až na souřadnicích 1000,1000; u SVG chci, aby SVG plátno obsahovalo diagram bez prázdného místa. Proto při přidávání tvarů počítám bounding box, který se pak použije k posunutí všech tvarů.
* SVG export má svůj modal, modaly v Dear ImGui jsou krapet zvláštní (z pohledu psaní jejich kódu)
* Možnost show in explorer → na Windows se mi podařilo udělat, že se neotevře explorer znovu, pokud již existuje instance exploreru s&nbsp;tímto adresářem, Zároveň je soubor v exploreru zvýrazněn. Na Linuxu je toto problémovější, tam pouze „hloupě“ otevírám explorer.

#### Další přidané funkce

* Dialogy save/open
  * Použita knihovna _Native File Dialog Extended_

* Dodatečné funkce
  * Ctrl+LMB na node pro skok na definici v texteditu
  * Toolbar s wysiwyg funkcemi:
    * Node color – color picker
    * Node shape – DropDownList
    * Tlačítka pro drag'n'drop node do canvasu
    * Slider pro změnu zoom level jako alternativa pro MW
    * Změna velikosti textu v textedit
    * Problematika kombinace přístupů, např. color picker musí vždy editovat TOML source, protože TOML source každý frame určuje vzhled vykresleného diagramu

* Dále umíme:
  * Ikonky – IconFontCppHeaders, přidán ikonkový font
  * Změna color theme v settings; U dark theme jsem vypnul průhlednost dodatečných oken → čitelnější.
  * Benchmark

* Dodatečné poznámky:
  * Nastavil jsem, aby přesouvání oken bylo možné pouze LMB tahem jejich headeru, nelze tedy tahat za tělo okna  
  * Dear ImGui slider neumí step size..., otrava.
  * U ComboBoxu paduju položky mezerama, aby se neměnila šířka comboboxu při změně položky.
  * Zkusil jsem neparsovat TOML každý frame, ale jen, když je potřeba; na výkonu se to nepodepsalo

* Jak se tedy píše „běžná“ aplikace v Dear ImGui?
  * MultiLineTextEdit je problematický widget, rozhodně od žádné existující IMGUI knihovny nemůžeme čekat widget s "VS Code user experience", alespoň zatím ne.
  * Layoutování je problematičtější, není zde žádný responzivní grid/flexbox (neberu-li v potaz 3rd party doplňky, ale jen oficiální widgety out-of-the-box)
  * Odpadá synchronizace stavů mezi daty na straně aplikace a daty co si drží knihovna. Zde máme všechna důležitá data u sebe, a IMGUI knihovně říkáme, jak se má na základě těchto dat vykreslit GUI. Widgety mohou případně pomocí referencí naše hodnoty měnit.
  * Jedna velká smyčka:
    * Umožňuje snadno dělat UI, které se mění v čase
    * Máme kontrolu nad pořadím akcí
    * Někdy je ale potřeba se zamyslet, kam vlastně kus kódu do hlavní smyčky umístit (zde můžu zmínit mou implementaci dialogu varujícího před neuloženým souborem; taky problematika kombinace wysiwy\[GM\] (kdy parsovat/vykreslit textedit/vykreslit diagram/...; něco je vždy o "snímek pozadu", vadí to?))

### Implementace v egui

* Prozatím jen nesetříděné poznámky:
  * Oproti no dependency Dear ImGui má egui určitě nějaké závislosti
  * TOMLEDIT místo TOML, kvůli source position
  * Cargo oproti CMake neumí kopírovat soubory do build složky
  * Vycházím z egui project template, která je od stejného autora, jako je samotná knihovna
    * Template už zde má připravenou struct App, glow renderer, ...
    * Dear ImGui je děláno primárně pro přidání debug okýnek do existující aplikace (zjednodušeně řečeno). Tady to spíše vypadá, že je prioritou tvorba samostatných „běžných, user-facing“ desktop/web aplikací. Běží na tom Rerun.io od stejného autora.
  * Moje struktura projektu asi není úplně Rust idiomatická, snažím se to mít stejné jako v Cpp projektu
  * Klíčové slovo static v Rustu nelze použít uvnitř funkce jako v C++, takže buď musí být všechny hodnoty součástí struct App, nebo musím přijít s modulárnějším přístupem.
  * Umí `ui.with_layout(egui::Layout::right_to_left ... {})`
  * Defaultní light theme mělo šedý text na bílém pozadí → změněno na černý text pro lepší čitelnost (pro dark mode byl font zase zesvětlen).
  * Podporuje přes 30 druhů kurzoru (GLFW 3.3.10 umí 10), všechny ale asi fungují jen na webu? Alespoň na Windows je grabbing stejný jako move (čtyřsměrná šipka namísto ruky).
  * Defaultní font podporuje řadu emoji, a to monochrome, takže lze použít jako ikonky. Toto funguje, i když přepíši defaultní font na Inconsolata, který emoji nepodporuje (pracuje se s prioritou). Každopádně symboly nemají konzistentní vizuální identitu a neexistuje emoji např. pro elipsu, nebo odlišení _save_ od _save as_, prostě jen disketa. Takže může se hodit, ale na seriózní ikony raději použít alternativu.
  * Vypadá to, že abych zprovoznil horizontal scroll u default text editoru, [musím použít syntax highlighting](https://github.com/emilk/egui/discussions/4871); a u něj nelze z kódu nastavit barevné schéma, takže opět máme světlé barvy na světlém pozadí, -_-
  * Nemá připraveno funkci tlačítka click and hold? Např. změna velikosti fontu text editoru, že bych držel + a ono to postupně přičítalo.
  * Error highlight na texteditoru nemusí řešit scroll, je to celé uvnitř scrollarea.
  * 3rd party text editor neumí error highlight, ale umí našeptávat ♥.
  * Barevné prostory: rgba_premul vs. rgba_unmul vs. srgba.
  * Ctrl+Z funguje i po zásahu do source stringu ("toolbar canvas interaction").
  * V Cpp od TOML knihovny dostávám umístění v kódu jako row+char_in_row, což se hodí pro Error Highlight, zde dostávám char_total, což se hodí při toolbar canvas interaction.
  * Egui painter neumí přepínat Z, pouze malířův algoritmus → implementována prioritní fronta draw commands.
  * PROBLÉM: Obecně se knihovny liší ve výšce řádku textu (projevuje se u nodes s víceřádkovým textem), zde to ale navíc vypadá, že to není konzistentní při zoomování (tedy výška řádku se mění s velikostí vykreslovaného písma?)
* __Viz [problems](https://github.com/RadekMocek/DiagramPche_egui?tab=readme-ov-file#problems)__

### Implementace v Qt

* Prozatím jen nesetříděné poznámky:
  * Používám QGraphicsView+QGraphicsScene; view řeší scrolling, přidává scrollbary; později změněno
    * Teoreticky bych mohl místo QGraphicsScene použít custom widget s paint event a všechno si kreslit na něj; tohle je ale častější způsob
  * Při psaní v textovém poli a stisku AltGr se občas vloží náhodný znak (alespoň na CZ klávesnici a Windows)
    * Jedná se o zajímavý Qt problém, který se děje např. i v [TeXStudiu](https://github.com/texstudio-org/texstudio/issues/164)
  * Složitější rozchodit lokálně, Qt je velká knihovna
  * Automatic MOC for target při každé kompilaci; při přidání nového .cpp souboru občas nutno smazat celou build složku, jinak chyba
    * Auto MOC může dělat problémy při <kbd>F2</kbd> (snaží se přejmenovávat i ve vygenerovaných souborech)
  * Hodně maker, které ve finále vedou na nic; velmi specifické použití nebo pro označení kusů kódu (signal, emit, slot)
  * PROBLÉM: když draguju button, přestanou se "hlásit" některé věci: QGraphicsView underMouse() vrací vždy false; mouseMoveEvent se nespouští;
    * Dragndrop nové node do scény je dobrý příklad toho, kdy Qt začíná být opruz → zdůvodnit
  * Společná nastavení v Preferences window, např. source font size → pro aplikování změn je pro mě nejjednodušší editovat hodnotu již existujícího widgetu, který má pak callback, jež opravdu změní velikost písma
  * Přidat parametr do signálu znamená aktualizovat signatury dvou funkcí; Ctrl+Click na funkci nejde k definici ale k MOC
  * __<https://www.qtcentre.org/threads/27134-QTextEdit-s-textChanged()-signal>__
  * Také je potřeba dávat si pozor na pořadí operací, např. `m_source->clear();`, pak až `m_is_source_dirty = false;`
  * Dodatek k parsování/vykreslování:
    * Umí SVG export out-of-the-box
    * Umí vykreslit elipsu podle bounding rect, je potřeba nastavit painter pen a brush
    * Cesty definované pomocí kolekce bodů: kolekce musí obsahovat dvojice, které budou spojeny, tedy až na start a cíl jsou zde všechny body dvakrát
* __Viz [problems](https://github.com/RadekMocek/DiagramPche_Qt?tab=readme-ov-file#problems)__

## Porovnání výsledků

...

## Jak by tato práce mohla pokračovat

* Co se týče diagram editoru:
  * Kombinovat wysiwy\[GM\] je v praxi problematické, raději se soustředit na jedno z nich, v tomto případě spíš _text→diagram_
  * => Návrh vlastního jazyka
* Co se týče porovnání knihoven:
  * Porovnat pomocné programy pro návrh GUI (Qt Creator, [ImRAD](https://github.com/tpecholt/imrad))
  * Export do WebAssembly (EMSCRIPTEN apod.)
  * Možnosti přístupnosti jako screen reader
  * Lokalizace
