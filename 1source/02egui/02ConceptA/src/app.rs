pub struct MyApp {
    pub do_open_modal_about: bool,
    pub code: String,
    pub zoom_level: f32,
    pub is_canvas_dragged: bool,
    pub scrolling: egui::Pos2,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            do_open_modal_about: false,
            code: String::from("Hello 40 40\negui! 130 55"),
            zoom_level: 1.0,
            is_canvas_dragged: false,
            scrolling: egui::pos2(0.0, 0.0),
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
        self.panel_top(&ctx);
        self.panel_bottom(&ctx);
        self.panel_central(&ctx);
    }
}
