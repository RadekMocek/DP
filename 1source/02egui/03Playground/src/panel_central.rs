use crate::MyApp;

impl MyApp {
    pub fn panel_central(&mut self, ui: &mut egui::Ui) {
        egui::CentralPanel::default().show_inside(ui, |mut ui| {
            self.win_input_test(&mut ui);

            self.win_input_problem(&mut ui);

            self.win_canvas(&mut ui);

            self.win_random_tests(&mut ui);

            self.win_textedit(&mut ui);

            self.win_textedit2(&mut ui);

            // --- --- --- --- --- --- --- --- --- --- --- --- --- ---

            if ui.button("Tlačítko").clicked() {
                println!("A");
            }
            if ui.button("Tlačítko").clicked() {
                println!("B");
            }

            ui.horizontal(|ui| {
                ui.label("1");
                ui.label("2");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    ui.label("3");
                    ui.label("4");
                });
            });
        });
    }
}
