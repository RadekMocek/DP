use crate::MyApp;

impl MyApp {
    pub fn win_textedit2(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Textedit scroll & jump?")
            .collapsible(false)
            .open(&mut self.do_show_win_textedit)
            .show(ui.ctx(), |ui| {
                let font_size = 22.0;
                let mut text = "0ABCD\n1DEFG\n2HIJK\n4MNOP\n5QRST\n6UVWX\n7YZŽ";

                ui.scope(|ui| {
                    ui.style_mut().text_styles.insert(
                        egui::TextStyle::Monospace,
                        egui::FontId::new(font_size, egui::FontFamily::Monospace),
                    );

                    egui::ScrollArea::vertical()
                        .id_salt("source")
                        .show(ui, |ui| {
                            ui.add(
                                egui::TextEdit::multiline(&mut text)
                                    .code_editor()
                                    //.desired_rows(2),
                            );
                        });

                    let _ = ui.button("???");
                });
            });
    }
}
