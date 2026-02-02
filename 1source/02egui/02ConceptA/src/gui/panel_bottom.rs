use crate::MyApp;

impl MyApp {
    pub(crate) fn panel_bottom(&mut self, ctx: &egui::Context) {
        egui::TopBottomPanel::bottom("bottom_panel").show(ctx, |ui| {
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                ui.add(
                    egui::Slider::new(&mut self.zoom_level, 0.5..=2.0)
                        .suffix("x zoom")
                        .max_decimals(1),
                );
            })
        });
    }
}
