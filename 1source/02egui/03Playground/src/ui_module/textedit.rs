//*
use crate::MyApp;
use egui_extras::syntax_highlighting::CodeTheme;

impl MyApp {
    pub fn win_textedit(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Textedit layouter & font size")
            .collapsible(false)
            .open(&mut self.do_show_win_textedit)
            .show(ui.ctx(), |ui| {
                //
                // My answer to https://github.com/emilk/egui/discussions/4935
                //

                let font_size = 22.0;
                let mut text = "0ABCD\n1DEFG\n2HIJK\n4MNOP\n5QRST\n6UVWX\n7YZŽ";

                ui.scope(|ui| {
                    // In this UI scope we overwrite the font size
                    ui.style_mut().text_styles.insert(
                        egui::TextStyle::Monospace,
                        egui::FontId::new(font_size, egui::FontFamily::Monospace),
                    );

                    // Set up the layouter
                    let mut layouter =
                        |ui: &egui::Ui, buf: &dyn egui::TextBuffer, wrap_width: f32| {
                            let mut layout_job = egui_extras::syntax_highlighting::highlight(
                                ui.ctx(),
                                ui.style(),
                                &CodeTheme::dark(0.0), // This number doesn't seem to change anything (?)
                                buf.as_str(),
                                "xml",
                            );
                            layout_job.wrap.max_width = wrap_width;
                            ui.fonts_mut(|f| f.layout_job(layout_job))
                        };

                    // Add the textedit widget with the layouter
                    ui.add(egui::TextEdit::multiline(&mut text).layouter(&mut layouter));
                });
            });
    }
}
//*/
