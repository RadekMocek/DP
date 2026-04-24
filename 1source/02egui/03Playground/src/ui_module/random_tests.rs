use crate::MyApp;

const CODE: &str = r#"_ = ui.button("Tlačítko");
_ = ui.button("Tlačítko");

ui.horizontal(|ui| {
  ui.label("1");
  ui.label("2");
  ui.with_layout(egui::Layout::right_to_left,
                 |ui| {
    ui.label("3");
    ui.label("4");
  });
});"#;

impl MyApp {
    pub fn win_random_tests(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Rozložení")
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                if ui.button("Tlačítko").clicked() {
                    println!("A");
                }
                if ui.button("Tlačítko").clicked() {
                    println!("B");
                }

                ui.horizontal(|ui| {
                    ui.label("1");
                    ui.label("2");
                    ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                        ui.label("3");
                        ui.label("4");
                    });
                });
            });

        /*
        let theme =  egui_extras::syntax_highlighting::CodeTheme {
            dark_mode: false,  // PRIVATE TAKŽE NELZE
            formats: ...
        };
        */

        let mut theme =
            egui_extras::syntax_highlighting::CodeTheme::from_memory(ui.ctx(), ui.style());

        egui::Window::new("Zdrojový kód rozložení")
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                let language = "rs";
                egui_extras::syntax_highlighting::code_view_ui(ui, &theme, CODE, language);
            });

        egui::Window::new("Barevné schéma")
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                theme.ui(ui);
                theme.store_in_memory(ui.ctx());
            });

        egui::Window::new("Okno")
            .id(egui::Id::new("OKNO1"))
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                ui.label("a");
            });

        egui::Window::new("Okno")
            .id(egui::Id::new("OKNO2"))
            .collapsible(false)
            .open(&mut self.do_show_win_random_tests)
            .show(ui.ctx(), |ui| {
                ui.label("b");
            });
    }
}
