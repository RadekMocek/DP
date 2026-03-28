use crate::MyApp;

impl MyApp {
    pub fn panel_bottom(&mut self, ui: &mut egui::Ui) {
        egui::Panel::bottom("bottom_panel").show_inside(ui, |_ui| {
            //
        });
    }
}
