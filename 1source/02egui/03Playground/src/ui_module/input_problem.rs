use crate::MyApp;
use num_format::Locale;
use num_format::ToFormattedString;

impl MyApp {
    pub fn win_input_problem(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("TextEdit memory usage")
            .collapsible(false)
            .open(&mut self.do_show_win_input_problem)
            .show(ui.ctx(), |ui| {
                ui.scope(|ui| {
                    ui.style_mut().text_styles.insert(
                        egui::TextStyle::Body,
                        egui::FontId::new(18.0, egui::FontFamily::Monospace),
                    );

                    //
                    ui.text_edit_singleline(&mut self.big_text);
                    //ui.add(egui::TextEdit::singleline(&mut self.big_text).clip_text(false));
                    //

                    let length = self.big_text.len();

                    if let Some(usage) = memory_stats::memory_stats() {
                        const MIBI: f32 = 1024.0 * 1024.0;
                        let usage = usage.physical_mem as f32 / MIBI;
                        ui.label(format!(
                            "Text size: {} chars",
                            length.to_formatted_string(&Locale::cs)
                        ));
                        ui.label(format!("Current memory usage: {usage:.1} MiB"));
                        //ui.label(format!("Usage per char: {} MiB", usage / length as f32));
                    }
                });

                ui.separator();
                ui.checkbox(&mut self.do_fill_big_text, "Keep adding characters");
                ui.spinner();

                if self.do_fill_big_text && self.big_text.len() < 10_000_000 {
                    self.big_text.push_str(&"A".repeat(10_000));
                }
            });
    }
}
