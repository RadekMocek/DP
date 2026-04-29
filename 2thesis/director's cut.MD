### Implementace v Dear ImGui

* GLFW 3.3.10 vs. 3.4.0
* S Monospace fontem se lépe pracuje
* Při posouvání canvasu měním vzhled kurzoru pomocí GLFW
* Nastavil jsem, aby přesouvání oken bylo možné pouze LMB tahem jejich headeru, nelze tedy tahat za tělo okna  
* Export diagramu do formátu SVG
  * Problémy: multiline text, rgba (webový prohlížeč to umí, ale můj Inkscape a qView ne, dělám SVG aby to vypadalo správně i v těchto programech)
  * Používám mírně upravenou header only knihovnu [_simple-svg_](https://github.com/adishavit/simple-svg)
  * Po kliknutí na export se pro příští frame nastaví proměnná typu _is\_svg\_requested_ na true, a v tomto průchodu smyčkou se kromě vykreslování buduje i SVG dokument. Moje logika, která volá simple-svg, se chová jako stavový automat.
  * Pro usnadnění před exportem resetuji canvas scrolling a zoom level.
  * Pro správné pořadí vykreslování (tedy aby i v SVG fungovala Z souřadnice), řadím jednotlivé svg::Shapes do prioritní fronty. Jedná se o&nbsp;abstraktní classu, takže zabaleno do unique_ptr.
  * Knihovnu jsem si upravil, aby podporovala průhlednost, není to ale ideální a podporuji pouze fill opacity. Stroke opacity už neumím, to by vyžadovalo větší zásah do knihovny, nebo možná lépe napsat si vlastní.
  * Uživatelův diagram může klidně začínat až na souřadnicích 1000,1000; u SVG chci, aby SVG plátno obsahovalo diagram bez prázdného místa. Proto při přidávání tvarů počítám bounding box, který se pak použije k posunutí všech tvarů.
  * SVG export má svůj modal, modaly v Dear ImGui jsou krapet zvláštní (z pohledu psaní jejich kódu)
  * Možnost show in explorer → na Windows se mi podařilo udělat, že se neotevře explorer znovu, pokud již existuje instance exploreru s&nbsp;tímto adresářem, Zároveň je soubor v exploreru zvýrazněn. Na Linuxu je toto problémovější, tam pouze „hloupě“ otevírám explorer.
* Jak se tedy píše „běžná“ aplikace v Dear ImGui?
  * MultiLineTextEdit je problematický widget, rozhodně od žádné existující IMGUI knihovny nemůžeme čekat widget s „VS Code user experience“, alespoň zatím ne.
  * Layoutování je problematičtější, není zde žádný responzivní grid/flexbox (neberu-li v potaz 3rd party doplňky, ale jen oficiální widgety out-of-the-box)
  * Odpadá synchronizace stavů mezi daty na straně aplikace a daty co si drží knihovna. Zde máme všechna důležitá data u sebe, a IMGUI knihovně říkáme, jak se má na základě těchto dat vykreslit GUI. Widgety mohou případně pomocí referencí naše hodnoty měnit.
  * Jedna velká smyčka:
    * Umožňuje snadno dělat UI, které se mění v čase
    * Máme kontrolu nad pořadím akcí
    * Někdy je ale potřeba se zamyslet, kam vlastně kus kódu do hlavní smyčky umístit (zde můžu zmínit mou implementaci dialogu varujícího před neuloženým souborem)
* __Viz [problems](https://github.com/RadekMocek/DiagramPche_DearImGui?tab=readme-ov-file#problems)__

### Implementace v egui

* Defaultní light theme mělo šedý text na bílém pozadí → změněno na černý text pro lepší čitelnost (pro dark mode byl font zase zesvětlen).
* Defaultní font podporuje řadu emoji, a jsou monochrome, takže je lze použít jako ikonky. Toto funguje, i když přepíši defaultní font na Inconsolata, který emoji nepodporuje (pracuje se s prioritou). Každopádně symboly nemají konzistentní vizuální identitu a neexistuje emoji např. pro elipsu, nebo odlišení _save_ od _save as_, prostě jen disketa. Takže může se hodit, ale na seriózní ikony raději použít alternativu.
* Ctrl+Z funguje i po zásahu do source stringu, stále to ale není ideální.
* V Cpp od TOML knihovny dostávám umístění v kódu jako row+char_in_row, což se hodí pro Error Highlight, zde dostávám char_total, což se hodí při toolbar canvas interaction.
* PROBLÉM: Obecně se knihovny liší ve výšce řádku textu (projevuje se u nodes s víceřádkovým textem), zde to ale navíc vypadá, že to není konzistentní při zoomování (tedy výška řádku se mění s velikostí vykreslovaného písma)
* __Viz [problems](https://github.com/RadekMocek/DiagramPche_egui?tab=readme-ov-file#problems)__

### Implementace v Qt

* Při psaní v textovém poli a stisku AltGr se občas vloží náhodný znak (alespoň na CZ klávesnici a Windows). Jedná se o zajímavý Qt problém, který se děje např. i v [TeXStudiu](https://github.com/texstudio-org/texstudio/issues/164).
* Hodně maker, které ve finále vedou na nic; velmi specifické použití nebo pro označení kusů kódu (signal, emit, slot)
* Automatic MOC for target při každé kompilaci; při přidání nového .cpp souboru občas nutno smazat celou build složku, jinak chyba
  * Auto MOC může dělat problémy při <kbd>F2</kbd> (snaží se přejmenovávat i ve vygenerovaných souborech)
  * Přidat parametr do signálu znamená aktualizovat signatury dvou funkcí; Ctrl+Click na funkci nejde k definici ale k MOC
* Nejen v IMGUI je potřeba dávat si pozor na pořadí operací: např. `m_source->clear();`, pak až `m_is_source_dirty = false;`
* __Viz [problems](https://github.com/RadekMocek/DiagramPche_Qt?tab=readme-ov-file#problems)__

### Benchmark

* Smyčka vs. QCoro
* Zkusil jsem v Dear ImGui neparsovat TOML každý frame, ale jen, když je potřeba; na výkonu se to nepodepsalo
* Syntax highlight také nemá patrný vliv na výkon
* QString neumí reserve, tak alespoň přidávám po "dávkách"
