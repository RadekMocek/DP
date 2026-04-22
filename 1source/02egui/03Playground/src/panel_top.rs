use crate::MyApp;

impl MyApp {
    pub fn panel_top(&mut self, ui: &mut egui::Ui) {
        egui::Panel::top("top_panel").show_inside(ui, |ui| {
            // The top panel is often a good place for a menu bar:
            egui::MenuBar::new().ui(ui, |ui| {
                ui.menu_button("Menu", |ui| {
                    ui.checkbox(&mut self.do_show_win_input_tests, "Input tests");
                    ui.checkbox(&mut self.do_show_win_input_problem, "TextEdit memory usage");
                    ui.checkbox(&mut self.do_show_win_canvas, "Canvas");
                    ui.checkbox(&mut self.do_show_win_random_tests, "Testovací okno");
                    ui.checkbox(&mut self.do_show_win_textedit, "MultilineTextEdit");
                    ui.checkbox(&mut self.do_show_win_textedit2, "MultilineTextEdit2");
                });
            });
        });
    }
}
