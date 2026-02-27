pub struct MyApp {
    pub do_show_win_input_tests: bool,
    pub test_text: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            do_show_win_input_tests: true,
            test_text: String::from("aabbccddeeffgghhiijjkkllmmnnooqqpprrssttuuvvwwxxyyzz"),
        }
    }
}

impl MyApp {
    /// Called once before the first frame.
    pub fn new(cc: &eframe::CreationContext<'_>) -> Self {
        cc.egui_ctx.set_visuals(egui::Visuals::light());
        crate::style::configure_styles(&cc.egui_ctx);
        Default::default()
    }
}

impl eframe::App for MyApp {
    /// Called each time the UI needs repainting, which may be many times per second.
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        // Put your widgets into a `SidePanel`, `TopBottomPanel`, `CentralPanel`, `Window` or `Area`.
        self.panel_top(&ctx);
        self.panel_bottom(&ctx);
        self.panel_central(&ctx);
    }
}
