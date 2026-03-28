use crate::MyApp;

impl MyApp {
    pub fn win_input_problem(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("TextEdit memory usage")
            .collapsible(false)
            .open(&mut self.do_show_win_input_problem)
            .show(ui.ctx(), |ui| {
                ui.spinner();

                //
                ui.text_edit_singleline(&mut self.big_text);
                //ui.add(egui::TextEdit::singleline(&mut self.big_text).clip_text(false));
                //

                let length = self.big_text.len();

                if let Some(usage) = memory_stats::memory_stats() {
                    const MIBI: f32 = 1024.0 * 1024.0;
                    let usage = usage.physical_mem as f32 / MIBI;
                    ui.label(format!("Current physical memory usage: {usage} MiB"));
                    ui.label(format!("Text size: {length} chars"));
                    ui.label(format!("Usage per char: {} MiB", usage / length as f32));
                }

                ui.separator();
                ui.checkbox(&mut self.do_fill_big_text, "GO");

                if self.do_fill_big_text && length < 1_000_000 {
                    self.big_text.push_str(&"A".repeat(10_000));
                }
            });
    }
}
