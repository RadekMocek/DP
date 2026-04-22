// Mějme aplikaci se členem `int m_number`,
// jehož hodnotu chceme měnit v GUI.

constexpr auto number_min = 0;  // Minimální hodnota člena
constexpr auto number_max = 10; // Maximální hodnota člena
// „Velikost kroku“, která se po stiknutí tlačítka +/- přičte/odečte
constexpr auto step_size = 2;

// --- Dear ImGui (C++) --- --- --- --- --- --- --- --- --- --- ---
ImGui::InputInt("##spinbox", &m_number, step_size);
m_number = std::clamp(m_number, number_min, number_max);

// --- egui (Rust)  --- --- --- --- --- --- --- --- --- --- --- ---
ui.horizontal(|ui| {
    ui.add(egui::DragValue::new(&mut m_number));
    if ui.button("-").clicked() {
        m_number -= step_size;
    }
    if ui.button("+").clicked() {
        m_number += step_size;
    }
    m_number += m_number % step_size;
    m_number = m_number.clamp(number_min, number_max);
});

// --- Qt (C++) --- --- --- --- --- --- --- --- --- --- --- --- ---
const QPointer spinbox = new QSpinBox();
spinbox->setMinimum(number_min);
spinbox->setMaximum(number_max);
spinbox->setSingleStep(step_size);
spinbox->setValue(m_number);

main_layout->addWidget(spinbox);
connect(spinbox, &QSpinBox::valueChanged, [this](int value) {
    m_number = value;
});

// Dear ImGui / egui:
// Změna hodnoty proměnné `m_number` jinde v kódu se
// automaticky projeví na hodnotě zobrazené v ovládacím prvku.

// Qt:
// Po změně hodnoty proměnné `m_number` jinde v kódu musíme také
// aktualizovat hodnotu drženou v ovládacím prvku `spinbox`.
