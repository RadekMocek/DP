pub fn configure_styles(ctx: &egui::Context) {
    ctx.all_styles_mut(|style| {
        style.visuals.override_text_color = Some(egui::Color32::BLACK);
    });
}
