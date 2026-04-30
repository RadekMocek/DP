// --- Dear ImGui --- --- --- --- --- --- --- --- --- --- --- --- ---
if (ImGui::BeginTabBar("PreferencesTabBar")) {
    // ... (Zde se nachází definice ostatních záložek nastavení) ...
    if (ImGui::BeginTabItem("View")) {
        ImGui::Checkbox("Toolbar", &m_do_show_toolbar);
        ImGui::Checkbox("Canvas grid", &m_do_show_grid);
        ImGui::Checkbox("Secondary canvas toolbar", &m_do_show_sct);
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
// Změna stavu zaškrtávacího pole se v aplikaci projeví okamžitě.

// --- Qt --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
const QPointer layout = new QVBoxLayout();
const QPointer tabs = new QTabWidget();

// ... (Zde se nachází definice ostatních záložek nastavení) ...

const QPointer layout_view_wrapper = new QWidget();
const QPointer layout_view = new QVBoxLayout(layout_view_wrapper);

m_view_toolbar = new QCheckBox("Toolbar");
m_view_toolbar->setChecked(m_state.do_show_toolbar);
layout_view->addWidget(m_view_toolbar);

m_view_canvas_grid = new QCheckBox("Canvas grid");
m_view_canvas_grid->setChecked(m_state.do_show_canvas_grid);
layout_view->addWidget(m_view_canvas_grid);

m_view_secondary_toolbar = new QCheckBox("Secondary canvas toolbar");
m_view_secondary_toolbar->setChecked(m_state.do_show_sct);
layout_view->addWidget(m_view_secondary_toolbar);

tabs->addTab(layout_view_wrapper, "View");
layout->addWidget(tabs);

// Okno s nastavením obsahuje tlačítko, které aplikuje všechny změny.
// Implementovat chování podobné IMGUI by kód dále zkomplikovalo.
const QPointer button_apply = new QPushButton("Apply all settings");
layout->addWidget(button_apply);
connect(button_apply, &QPushButton::clicked, [this] { ... });

setLayout(layout);