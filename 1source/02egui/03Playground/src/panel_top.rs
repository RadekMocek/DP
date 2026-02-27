use crate::MyApp;

impl MyApp {
    pub fn panel_top(&mut self, ctx: &egui::Context) {
        egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
            // The top panel is often a good place for a menu bar:
            egui::MenuBar::new().ui(ui, |ui| {
                ui.menu_button("Menu", |ui| {
                    ui.checkbox(&mut self.do_show_win_input_tests, "Input tests");
                });
            });
        });
    }
}
