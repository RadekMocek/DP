use crate::MyApp;

impl MyApp {
    pub fn win_textedit2(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Textedit aaaah")
            .collapsible(false)
            .open(&mut self.do_show_win_textedit2)
            .show(ui.ctx(), |ui| {
                let font_size = 22.0;

                ui.scope(|ui| {
                    ui.style_mut().text_styles.insert(
                        egui::TextStyle::Monospace,
                        egui::FontId::new(font_size, egui::FontFamily::Monospace),
                    );

                    egui::ScrollArea::vertical()
                        .id_salt("source")
                        .show(ui, |ui| {
                            ui.add(
                                egui::TextEdit::multiline(&mut self.test_text2).code_editor(), //.desired_rows(2),
                            );
                        });
                });
            });
    }
}
