use crate::MyApp;

impl MyApp {
    pub fn panel_central(&mut self, ctx: &egui::Context) {
        egui::CentralPanel::default().show(ctx, |mut ui| {
            
            self.input_test(&mut ui);

        });
    }
}
