use crate::MyApp;

impl MyApp {
    pub fn panel_bottom(&mut self, ctx: &egui::Context) {
        egui::TopBottomPanel::bottom("bottom_panel").show(ctx, |_ui| {
            //
        });
    }
}
