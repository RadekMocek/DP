use crate::MyApp;

impl MyApp {
    pub fn win_random_tests(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Testovací okno")
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                ui.label("a");
            });
    }
}
