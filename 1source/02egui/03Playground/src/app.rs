pub struct MyApp {
    pub do_show_win_input_tests: bool,
    pub do_show_win_input_problem: bool,
    pub do_show_win_canvas: bool,
    pub do_show_win_random_tests: bool,
    pub do_show_win_textedit: bool,
    pub do_show_win_textedit2: bool,
    pub test_text: String,
    pub test_text2: String,

    pub big_text: String,
    pub do_fill_big_text: bool,
    pub do_show_big_text: bool,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            do_show_win_input_tests: false,
            do_show_win_input_problem: false,
            do_show_win_canvas: false,
            do_show_win_random_tests: true,
            do_show_win_textedit: false,
            do_show_win_textedit2: false,
            test_text: String::from("aabbccddeeffgghhiijjkkllmmnnooqqpprrssttuuvvwwxxyyzz"),
            test_text2: String::from(
                "abcde ABCDE\nfghij FGHIJ fghij FGHIJ\nklmno KLMNO klmno KLMNO klmno KLMNO\npqrst PQRST pqrst PQRST pqrst PQRST pqrst PQRST\nuvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ uvwxyz UVWXYZ\něščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ ěščřžýáíé ĚŠČŘŽÝÁÍÉ\n☺ ☻ ♥ ♦ ♣ ♠\n😀\n0 1 2 3 4 5 6 7 8 9",
            ),

            big_text: String::with_capacity(2_000_000),
            do_fill_big_text: false,
            do_show_big_text: true,
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
    fn ui(&mut self, ui: &mut egui::Ui, _frame: &mut eframe::Frame) {
        // Put your widgets into a `SidePanel`, `TopBottomPanel`, `CentralPanel`, `Window` or `Area`.

        self.panel_top(ui);
        self.panel_bottom(ui);
        self.panel_central(ui);

        //self.win_textedit2(ui);
    }
}
