use crate::MyApp;

impl MyApp {
    pub fn panel_central(&mut self, ctx: &egui::Context) {
        egui::CentralPanel::default().show(ctx, |mut ui| {
            
            self.win_input_test(&mut ui);

            self.win_canvas(&mut ui);

            self.win_textedit(&mut ui);

            self.win_textedit2(&mut ui);
        });
    }
}
