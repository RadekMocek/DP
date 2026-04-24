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
        });
    }
}
