pub struct MyApp {
    do_open_modal_about: bool,
    code: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            do_open_modal_about: false,
            code: String::from("\"Hello\" 40 40\n\"egui!\" 160 50"),
        }
    }
}

impl MyApp {
    /// Called once before the first frame.
    pub fn new(cc: &eframe::CreationContext<'_>) -> Self {
        cc.egui_ctx.set_visuals(egui::Visuals::light());
        crate::style::configure_text_styles(&cc.egui_ctx);
        Default::default()
    }
}

impl eframe::App for MyApp {
    /// Called each time the UI needs repainting, which may be many times per second.
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        // Put your widgets into a `SidePanel`, `TopBottomPanel`, `CentralPanel`, `Window` or `Area`.
        // The top panel is often a good place for a menu bar:

        egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
            egui::MenuBar::new().ui(ui, |ui| {
                ui.menu_button(egui::RichText::new("Help").size(14.0), |ui| {
                    if ui
                        .button(egui::RichText::new("About...").size(14.0))
                        .clicked()
                    {
                        self.do_open_modal_about = true;
                    }
                });
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
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
            });

            //

            if self.do_open_modal_about {
                let modal =
                    egui::Modal::new(egui::Id::new("Modal about...")).show(ui.ctx(), |ui| {
                        ui.heading("About...");
                        ui.add_space(6.0);
                        ui.hyperlink("https://github.com/RadekMocek/DP");
                        ui.add_space(10.0);
                        if ui.button("Close").clicked() {
                            ui.close();
                        }
                    });

                if modal.should_close() {
                    self.do_open_modal_about = false;
                }
            }
        });
    }
}
