# DP draft

* Zeptat se:
  * Ukázková aplikace takhle OK?
  * Textová zpráva:
    * Rámcový obsah takhle OK?
    * Styl psaní: trpný rod / první osoba?
    * Počet stran 40–50?

* Poznámka: Používám zde nějaké dočasné termíny, které nejsou úplně korektní. Ta správná jména budu muset ještě domyslet:
  * Několikrát zde používám termíny wysiwyg a wysiwym, i když to asi není zcela přesné. Prozatím to ale poslouží pro odlišení funkcí programu (jak se program ovládá z pohledu koncového uživatele), kdy _wysiwym_ beru jako psaní textu, podle kterého se vykreslí diagram, a _wysiwyg_ jako jakékoliv jiné editování diagramu pomocí GUI prvků.
  * Dále procesu získání potřebných dat z TOML zdrojového kódu zatím říkám TOML parsing. Parsing se ale děje jen v prvním kroce a dělá jej knihovna toml++, já pak z již rozparsovaného TOMLu „jen“ získávám data a reaguji na jejich obsah.
  * TOML musí odpovídat mému schématu a pro náhodný TOML dokument se pravděpodobně nic nevykreslí. V XML světě se tomu říká schéma, jestli to je i zde v pořádku, jsem zatím nezkoumal.
  * Diagram může být leccos (alespoň [dle wiki](https://cs.wikipedia.org/wiki/Diagram)), chtělo by to být přesnější?
  * Node bude uzel/symbol, path bude čára/cesta?
* (LMB – left mouse button, MW – mousewheel)

## Rešerše

* Pro každou IMGUI knihovnu
  * Základní úvod
  * Pak se zaměřit na MultiLineTextEdit a kreslení grafických primitiv, protože to je hlavní část mé ukázkové aplikace
* Qt
  * Pár slov o Qt, protože je to jedna z použitých knihoven
  * Zmínit, že nebudu používat Qt creator... u všech knihoven definuji GUI v kódu. Kromě Qt Creator narážím na fórech i na lidi pracující v QML.

## Návrh

* Návrh aplikace:
  * Popis diagramu pomocí strukturovaného textu ve víceřádkovém textovém poli
  * Aplikace vykreslí diagram podle popisu – využití funkcí knihovny pro vykreslování 2D primitiv
  * => dvě hlavní části: textové pole a plátno (canvas)
  * Dodatečné přidané funkce by se měly zaměřovat na prohloubení poznání dané knihovny → použití různých ovládacích prvků → menu, button, radio, checkbox, DropDownList, ...
  * Přidávat funkce, které známe z „běžných“ aplikací → dialog pro uložení/otevření souboru, změna vzhledu light/dark mode, ...
  * Aplikace (krom toho, že se jedná o prostředek pro ukázky a porovnání knihoven) by se měla blížit k reálně použitelnému programu pro tvorbu diagramů, proto je na místě export do SVG
  * Měla by běžet na Windows a Linux

* Popis diagramu pomocí strukturovaného textu:
  * Inspirováno přístupem wysiwyM. Zde se ale nepopisuje, co má diagram znamenat, ale jak má přesně vypadat.
    * Grafických wysiwyG editorů je dost; wysiwyM je třeba graphwiz nebo mermaid, zde ale nemáme kontrolu nad přesným vzhledem (?)
    * => pokus o unikátní přístup
  * Zvolen byl TOML, síla na podobné úrovni jako JSON, ale je člověkem čitelnější a lépe se píše (např. klíče nemusí být stringy, tables to hodně usnadňují)
    * XML má výhodu snadné validace, případný převod na SVG; ale pro člověka méně přehledné a více psaní
    * YAML jsem uvažoval než jsem si uvědomil existenci TOMLu, příjemné na psaní; chybí tables, řízené whitespace znaky
    * Ideálnější by byl vlastní jazyk (domain specific language, ANTLR pro cpp, Pest pro rs)
      * Lepší hlášení chyb
      * Vlastní klíčová slova, místo `pivot="center"` by bylo `pivot=center`
      * Jazyk by nemusel být zas tak odlišný od TOML návrhu, např. místo `xy=[10,20]` by mohlo být `xy=10,20` (což TOML nedovoluje) atd.

* TOML schéma:
  * Dva základní prvky: node a path, každá instance odpovídá tabulce: `[[node]]` (později `[node."id"]`) a `[[path]]`, těm pak nastavujeme jednotlivé parametry
  * Požadavky na nodes:
    * Pozice node musí jít definovat jako relativní posun od jiné node. Pokud by program přijímal pouze absolutní souřadnice, velice by to zkomplikovalo případné úpravy již hotových diagramů. Takto se posunutím node posunou i všechny „na ní závislé“ nodes (potomci).
    * Nodes musí jít definovat v libovolném pořadí, tedy lze definovat potomka dříve než rodiče. To vyžaduje dodatečnou logiku, ale zpříjemní user experience.
    * Měla by jít definovat souřadnice Z, tedy zdali se nějaká node vykresluje před nebo za jinou node, nehledě na reference, pořadí definice ve zdrojovém kódu atd.
    * Hlásit chyby, nejen syntaktické, ale sémantické; neexistující rodič, kruhová reference, ...
  * Požadavky na paths:
    * Jakmile bude vyřešena problematika nodes (závislosti, umístění, vrstvy), pomocí bodů by měly jít definovat cesty, tedy pouze rovné čáry, žádné křivky.
    * Pro lepší UX mohou jednotlivé body cesty referovat kromě pivotů nodes také předchozí/startovní/koncový bod. Díky tomu by měly cesty být i „odolnější“ při editaci diagramu.
    * Oproti nodes mohou body cesty pro každou souřadnici referovat něco jiného (u nodes máme `xy=rodič+x,rodič+y`, u bodu máme `xy=rodič1+x,rodič+2`)
    * U cest cheme také možnost nastavit Z, tedy zdali se daná cesta vykreslí před/za danými nodes
  * TOML parser má za úkol z TOML dat vytvořit struktury, které si přebere knihovna a pomocí kterých bude vykreslovat, měl by být psán nezávisle na GUI knihovně

## Implementace

Ukázkové aplikace byly dělány v pořadí Dear ImGui→egui→Qt (se záchytnými body: vykreslování blokového diagramu → export do SVG → hotovo?), proto sekce Dear ImGui popisuje i řešení problematiky společné pro všechny knihovny (např. konkrétní řešení TOML parsing), a sekce zbylých dvou knihoven se již zabývají odlišnostmi od první implementace a specifickými problémy v daných knihovnách.

### Implementace v Dear ImGui

#### Dodatečné použité technologie a závislosti

* Založení projektu: vcpkg neobsahuje nejnovější verzi Dear ImGui 1.92, která se mi hodí, protože _Fonts may be rendered at any size. Glyphs are loaded and rasterized dynamically. No need to specify ranges, prebake etc._ Byly zváženy alternativní možnosti jako Conan, Build2, nebo CMake's FetchContent, nakonec mám zdrojové kódy všech závislostí u sebe.
* Backend OpenGL GLFW+Glad; GLFW – verze 3.4 problém se zátěží CPU na mém PC, proto používám 3.3.10.
  * Knihovna Dear ImGui neřeší vše, něco nechává na starost právě backendu (změna vzhledu kurzoru, app icon, callbacky), o nějaké typy kurzorů přicházím, protože nejedu GLFW 3.4
* Používám Freetype, kvalitnější vykreslování písma než stb?
* Font Incosolata pro všechny projekty stejný, monospace se hodí (snadno lze vypočítat šířku řetězce), permisivní licence písma

#### Struktura projektu

* Většina logiky v class App, ta je ve svém hpp souboru, pak hodně cpp souborů dodávajících implementace
  * Metody z App rozděleny do souborů podle toho čím se zabývají → může být přehlednější, ale při změně hpp dlouhá kompilace
* C++ umožňuje static proměnné uvnitř metody, vhodné pro lokální data (konkrétně v přístupu imgui, kdy funkce běží každý frame) → není nutné mít všechna data v class App (jen ta, ke kterým chceme přistupovat z více funkcí)
* Zvláštní třídy pro TOML parse (bude znovupoužit v Qt projektu, psán aby byl nezávislý na Dear ImGui) a pro SVG exporter

#### Tvorba uživatelského rozhraní

* Knihovna je stavový automat – logika se snadno rozděluje do více funkcí; když dám `PushStyleVar`, nesmím zapomenout na `PopStyleVar`
* Tzv. kurzor postupně vykresluje jednotlivé ovládací prvky a posouvá se
* Tvorba layoutu spočívá ve volání `GetCursorScreenPos`, `SetCursorScreenPos`, `SameLine`, `GetContentRegionAvail` a jednoduché matematiky
* Scrolling – i když si člověk vypne u hlavního okna scrollbary, pokud je umístěno něco „mimo viewport“, pak lze pomocí MW s celou app posunout – uvnitř hl. okna se vše posune a my doskrolujeme k out-of-bounds prvku. Toto je potřeba si hlídat, platí to např. i u moc dlouhého textu, který přeteče → horizontal scroll.
* Dear ImGui má flag ResizeX pro měnění poměru šířek mezi textedit a canvas (LMB drag). To ale není ideální: při změně velikosti okna se nezachovává poměr, interně totiž knihovna neřeší poměr, ale šířku texteditu v pixelech, kterou zachovává. Proto byl napsán vlastní _splitter_ pomocí invisible button.

#### Problematika popisu diagramu pomocí textu

* Každá node musí mít svou ID, pak lze `[node.rodič]↵xy=[x,y]` a `[node.potomek]↵xy=["rodič",x,y]`
* Co ale přesně znamenají souřadnice node, že se zde nachází její střed, nebo levý horní roh? Odkud probíhá posun od rodičovské node?
  * → Byl přidán pivot, každá node má vlastní pivot a referuje pivot případného rodiče
  * Díky tomu lze mít např. více dvě nodes vedle sebe s danou mezerou, „můj pivot je vlevo a posun od pravého pivota rodiče je x“, pak i se změnou šířky rodiče dojde k posunu a zachová se tedy velikost mezery
  * Každá node může mít tedy maximálně jednoho rodiče, později se ukázalo, že by bylo vhodnější referovat zvlášť na ose x a y (max 2 rodiče), je to vhodnější pro nodes v mřížce, ale není to zas tak zásadní.
* TOML parser nepředává knihovně finální souřadnice nodes, pouze kontroluje, zdali reference neukazují do prázdna a nemáme kruhovou referenci. Dále vrací pořadí, v jakém provést dodatečné zpracování. Proč? Node je obdélník (nebo jiný tvar) s textem, velikost obdélníku je implicitně určena jeho textem, tedy node s 20znakovým popiskem je širší než node s 10znakovým popiskem. Abychom zjistili šířku textu, musíme volat ImGui, a TOML parser by měl být nezávislý na ImGui... (ImGui musíme volat, protože se teoreticky mohou měnit fonty za běhu, řeší to za nás víceřádkový text apod.). Toto by šlo řešit různě, ale já se rozhodl, že TOML parser udělá, co je v jeho silách, a jakmile předá řízení ImGui, pak v tomto průchodu smyčkou už nepracuje. ImGui pak „zpracovává“ nodes tak, že pomocí textu a zoom level zjistí skutečnou vykreslovací velikost. Finální souřadnice ImGui dopočítá, protože již zná souřadnice případného rodiče, to protože od TOML parseru dostává pořadí, v jakém zpracovávat. Toto pořadí bere v ohled rodiče a potomky.
* Bylo implementováno iterativně, od vykreslení jednoho obdélníku po plnohodnotné blokové schéma.
* [App/Logic/TOML/Parser.cpp](https://github.com/RadekMocek/DiagramPche_DearImGui/blob/main/App/Logic/TOML/Parser.cpp), metoda Parse je okomentovaná
  * Jednotlivé zpracovávané Nodes mám nejprve v mapě (vhodné pro kontrolu referencí), pak jsem je přesouval pomocí std::move do prioritní fronty, ze které si to Dear ImGui popovalo.
  * Později jsem ponechal data v mapě a prioritní fronta obsahuje pouze pořadové číslo (podle něj řadíme) a klíč do mapy. Díky tomu data přežijí toto zpracování a lze použít později v toolbaru. Také díky tomu při TOML syntax error (což se děje běžně při psaní, než něco dopíšeme) nezmizí celý diagram a můžeme kreslit pomocí posledních validních dat.

#### Vykreslení diagramu

* Popsat jak funguje canvas, není to žadný speciální widget, kreslíme „do prázdna“, invisible button, RMB to move, ...
* "Font size based zooming", MW scroll nad canvasem celočíselně přičítá/odečítá velikosti písma v canvasu, ze kterého se pak odvodí celkový _canvas zoom level_; protože neceločíselná velikost písma v Dear ImGui produkuje mírně rozmazaný text (i po updatu na 1.92.6)
  * Také když MW měnil přímo float zoom_level, tak se poměr velikosti písma a obdélníku v node mírně měnil, (velikost vykreslovaného písma je zaručena asi jen do určité přesnosti, která je nižší než pro vykreslování obdélníku)
* Kreslení pomocí ImDrawList hned po tom, co si zpracuji informace od TOML parseru
* ImDrawList má funkce pro obdélník, elipsu, čáru; kosočtverec a šipku jsem si „doimplementoval“.
* ImDrawList umí přepínat vrstvy, takže lze snadno implementovat Z souřadnici

#### Víceřádkové textové pole

* Dear ImGui vanilla editor i později přidaný 3rd party widget mají problémy, viz [DP-dearimgui-readme](https://github.com/RadekMocek/DiagramPche_DearImGui?tab=readme-ov-file#problems), autor knihovny do budoucna plánuje rewrite, viz [10 years of Dear ImGui](https://github.com/ocornut/imgui/issues/7892), sekce _6.7. REWRITING INPUTTEXT (v2)_, něco z tohohle by šlo zmínit v rešerši
* Do vanilla widgetu bylo přidáno zvýrazňování chyb vykreslováním poloprůhledných červených obdélníků nad textem (tedy umíme jen jednu chybu naráz, tu první nahlášenou ☺); zde byl problém s horizontal scroll (obecně jeden z problémů tohoto widgetu), pro zjištění aktuální hodnoty horizontálního posunu musím šahat do imgui_internal.h, kde není zaručeno, že to bude v budoucnu fungovat
* Pak jsem přidal 3rd party editor, trochu si ho upravil, problémy také zmiňuji v readme
  * Tento editor má ještě další forky, které jsou možná lepší, ale originál je nejznámější a je featured přímo v Dear ImGui readme, takže na něj pravděpodobně nejvíc lidí narazí. Navíc dostal patch přímo od autora Dear ImGui, aby fungoval na nové verzi (jedná se o malou změnu, takže by asi nebyl problém upravit nějaký fork). Forky už jsem zkrátka netestoval.
  * Editor umí error highlight, ale jen celý řádek.

#### Export diagramu do formátu SVG

* Problémy: multiline text, rgba (webový prohlížeč to umí, ale můj inkscape a qView ne, dělám SVG aby to vypadalo správně i v těchto programech)
* Používám mírně upravenou header only knihovnu simple-svg
* Po kliknutí na export se pro příští frame nastaví proměnná typu _is\_svg\_requested_ na true, a v tomto průchodu smyčkou se kromě vykreslování buduje i SVG dokument. Moje logika, která volá simple-svg, se chová jako stavový automat.
* Pro usnadnění před exportem resetuji canvas scrolling a zoom level.
* Pro správné pořadí vykreslování (tedy aby i v SVG fungovala Z souřadnice), řadím jednotlivé svg::Shapes do prioritní fronty. Jedná se o absktraktní classu, takže zabaleno do unique_ptr.
* Knihovnu jsem si upravil, aby podporovala průhlednost, není to ale ideální a podporuji pouze fill opacity. Stroke opacity už neumím, to by vyžadovalo větší zásah do knihovny, nebo možná lépe napsat si vlastní.
* Uživatelův diagram může klidně začínat až na souřadnicích 1000,1000; u SVG chci, aby SVG plátno obsahovalo diagram bez prázdného místa. Proto při přidávání tvarů počítám bounding box, který se pak použije k posunutí všech tvarů.
* SVG export má svůj modal, modaly v Dear ImGui jsou krapet zvláštní (z pohledu psaní jejich kódu)
* Možnost show in explorer → na Windows se mi podařilo udělat, že se neotevře explorer znovu, pokud již existuje instance exploreru s tímto adresářem, Zároveň je soubor v exploreru zvýrazněn. Na Linuxu je toto problémovější, tam pouze „hloupě“ otevírám explorer.

#### …

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
  * Benchmark?

* Dodatečné poznámky:
  * Nastavil jsem, aby přesouvání oken bylo možné pouze LMB tahem jejich headeru, nelze tedy tahat za tělo okna  
  * Dear ImGui slider neumí step size..., otrava.
  * Má nějakou implicitní navigaci pomocí šipek, tabulátoru atd. Moc to nefunguje, nebo s tím neumím (?). Klávesové zkratky by to ještě chtělo prozkoumat.
  * U ComboBoxu paduju položky mezerama, aby se neměnila šířka comboboxu při změně položky.

* Jak se tedy píše „běžná“ aplikace v Dear ImGui?
  * Tohle bude oříšek napsat nějak objektivně..., nezabarveně; momentálně mě ještě čeká kus práce v Qt, takže tyto myšlenky budu ještě formovat.
  * Každopádně:
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
  * Cargo oproti CMake neumí kopírovat soubory do build složky
  * Vycházím z egui project template, která je od stejného autora, jako je samotná knihovna
    * Template už zde má připravenou struct App, glow renderer, ...
    * Dear ImGui je děláno primárně pro přidání debug okýnek do existující aplikace (zjednodušeně řečeno). Tady to spíše vypadá, že je prioritou tvorba samostatných „běžných, user-facing“ desktop/web aplikací. Běží na tom Rerun.io od stejného autora.
  * Moje struktura projektu asi není úplně Rust idiomatická, snažím se to mít stejné jako v Cpp projektu
  * Klíčové slovo static v Rustu nelze použít uvnitř funkce jako v C++, takže buď musí být všechny hodnoty součástí struct App, nebo musím přijít s modulárnějším přístupem.
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

### Implementace v Qt

* Prozatím jen nesetříděné poznámky:
  * Při psaní v textovém poli a stisku AltGr se občas vloží náhodný znak (alespoň na CZ klávesnici a Windows)
    * Jedná se o zajímavý Qt problém, který se děje např. i v [TeXStudiu](https://github.com/texstudio-org/texstudio/issues/164)
  * Dodatek k parsování/vykreslování:
    * Umí SVG export out-of-the-box
    * Umí vykreslit elipsu podle bounding rect, je potřeba nastavit painter pen a brush
    * Cesty definované pomocí kolekce bodů: kolekce musí obsahovat dvojice, které budou spojeny, tedy až na start a cíl jsou zde všechny body dvakrát

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
