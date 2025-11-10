pub struct TemplateApp {
    counter: u8,
    show_popup_window: bool,
}

impl Default for TemplateApp {
    fn default() -> Self {
        Self {
            counter: 1,
            show_popup_window: false,
        }
    }
}

impl TemplateApp {
    /// Called once before the first frame.
    pub fn new(_cc: &eframe::CreationContext<'_>) -> Self {
        Default::default()
    }
}

impl eframe::App for TemplateApp {
    /// Called each time the UI needs repainting, which may be many times per second.
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        // Put your widgets into a `SidePanel`, `TopBottomPanel`, `CentralPanel`, `Window` or `Area`.
        // The top panel is often a good place for a menu bar:

        egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
            egui::MenuBar::new().ui(ui, |ui| {
                ui.menu_button("File", |ui| {
                    ui.checkbox(&mut self.show_popup_window, "Pop-up");

                    if ui.button("Quit").clicked() {
                        ctx.send_viewport_cmd(egui::ViewportCommand::Close);
                    }
                });
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            // The central panel the region left after adding TopPanel's and SidePanel's

            ui.horizontal(|ui| {
                //

                ui.add_enabled_ui(self.counter != 1, |ui| {
                    if ui.add_sized([40.0, 20.0], egui::Button::new("-")).clicked() {
                        self.counter -= 1;
                    }
                });

                ui.label(self.counter.to_string());

                ui.add_enabled_ui(self.counter != 5, |ui| {
                    if ui.add_sized([40.0, 20.0], egui::Button::new("+")).clicked() {
                        self.counter += 1;
                    }
                });

                //
            });

            if self.counter == 3 {
                ui.label("Hello!");
            }

            if self.show_popup_window {
                egui::Window::new("Pop-up Window")
                    .resizable(false)
                    .collapsible(false)
                    .anchor(egui::Align2::CENTER_CENTER, [0.0, 0.0])
                    .show(ctx, |ui| {
                        ui.label("Not much you can do here...");
                        if ui.button("Close").clicked() {
                            self.show_popup_window = false;
                        }
                    });
            }

            //
        });
    }
}
