use crate::MyApp;

impl MyApp {
    pub fn input_test(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Input tests")
            .collapsible(false)
            .open(&mut self.do_show_win_input_tests)
            .show(ui.ctx(), |ui| {
                ui.text_edit_singleline(&mut self.test_text);

                ui.add(
                    egui::TextEdit::singleline(&mut self.test_text)
                        .horizontal_align(egui::Align::Max)
                        .cursor_at_end(true),
                );

                ui.add(
                    egui::TextEdit::singleline(&mut self.test_text)
                        .horizontal_align(egui::Align::Min)
                        .cursor_at_end(false),
                );

                let textedit = egui::TextEdit::singleline(&mut self.test_text);
                let output = textedit.show(ui);
            });
    }
}
