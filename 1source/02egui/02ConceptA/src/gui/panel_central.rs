use crate::MyApp;

impl MyApp {
    pub(crate) fn panel_central(&mut self, ctx: &egui::Context) {
        egui::CentralPanel::default().show(ctx, |mut ui| {
            // The central panel the region left after adding TopPanel's and SidePanel's

            ui.columns(2, |columns| {
                egui::ScrollArea::vertical()
                    .id_salt("source")
                    .show(&mut columns[0], |ui| {
                        ui.add(
                            egui::TextEdit::multiline(&mut self.code)
                                .desired_width(f32::INFINITY)
                                .font(egui::TextStyle::Monospace),
                        );
                    });

                egui::Frame::canvas(&columns[1].style()).show(&mut columns[1], |ui| {
                    self.canvas_logic(ui);
                });
            });

            self.modals(&mut ui);
        });
    }
}
