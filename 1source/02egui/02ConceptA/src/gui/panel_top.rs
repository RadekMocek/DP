use crate::MyApp;

impl MyApp {
    pub(crate) fn panel_top(&mut self, ctx: &egui::Context) {
        egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
            // The top panel is often a good place for a menu bar:
            egui::MenuBar::new().ui(ui, |ui| {
                ui.menu_button(egui::RichText::new("Help").size(14.0), |ui| {
                    if ui
                        .button(egui::RichText::new("About...").size(14.0))
                        .clicked()
                    {
                        self.do_open_modal_about = true;
                    }
                });
            });
        });
    }
}
