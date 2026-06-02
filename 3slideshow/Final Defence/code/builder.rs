egui::TextEdit::multiline(&mut source).desired_width(f32::INFINITY)
    .code_editor().layouter(&mut layouter).show(ui);