use crate::MyApp;

impl MyApp {
    pub(crate) fn modals(&mut self, ui: &mut egui::Ui) {
        if self.do_open_modal_about {
            let modal = egui::Modal::new(egui::Id::new("Modal about...")).show(ui.ctx(), |ui| {
                ui.heading("About...");
                ui.add_space(6.0);
                ui.hyperlink("https://github.com/RadekMocek/DP");
                ui.add_space(10.0);
                if ui.button("Close").clicked() {
                    ui.close();
                }
            });

            if modal.should_close() {
                self.do_open_modal_about = false;
            }
        }
    }
}
