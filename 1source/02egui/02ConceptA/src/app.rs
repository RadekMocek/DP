pub struct MyApp {
    do_open_modal_about: bool,
    code: String,
    zoom_level: f32,
    is_canvas_dragged: bool,
    scrolling: egui::Pos2,
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

    fn canvas_logic(&mut self, ui: &mut egui::Ui) -> egui::Response {
        const COLOR_BLACK: egui::Color32 = egui::Color32::BLACK;
        const BORDER_OFFSET_BASE: f32 = 10.0;

        let border_offset = BORDER_OFFSET_BASE * self.zoom_level;

        // Painter is our canvas
        let (response, painter) = ui.allocate_painter(ui.available_size(), egui::Sense::drag());

        // Origin ([0,0]) of the canvas in screen space coordinates, which painter uses
        let origin = egui::pos2(
            response.rect.min.x + self.scrolling.x,
            response.rect.min.y + self.scrolling.y,
        );

        // Handle mouse events
        let pointer_pos_in_canvas;
        if let Some(pointer_pos) = response.interact_pointer_pos() {
            pointer_pos_in_canvas = pointer_pos - origin;
        }

        // RMB to move canvas ("scrolling")
        if response.drag_started_by(egui::PointerButton::Secondary) {
            self.is_canvas_dragged = true;
        }
        if self.is_canvas_dragged {
            self.scrolling += response.drag_delta();
        }
        if response.drag_stopped_by(egui::PointerButton::Secondary) {
            self.is_canvas_dragged = false;
        }

        // LMB to move nodes
        if response.drag_started_by(egui::PointerButton::Primary) {
            //TODO
        }

        // Parse every line of the "code" in text editor
        for line in self.code.lines() {
            let parts: Vec<_> = line.split_whitespace().collect();

            // Hello 40 40
            // ^^^^^
            let Some(text) = parts.get(0) else {
                continue;
            };

            // Hello 40 40
            //       ^^
            let Some(x_cor_str) = parts.get(1) else {
                continue;
            };
            let x_cor = x_cor_str.parse::<i32>().unwrap_or(0);

            // Hello 40 40
            //          ^^
            let Some(y_cor_str) = parts.get(2) else {
                continue;
            };
            let y_cor = y_cor_str.parse::<i32>().unwrap_or(0);

            // Line data parsed ok

            let x_cor_scaled = x_cor as f32 * self.zoom_level;
            let y_cor_scaled = y_cor as f32 * self.zoom_level;

            // Lay out the text, ready it for painting
            // After this we can get the size of text, which will be painted
            let text_galley = painter.layout_no_wrap(
                String::from(*text),
                egui::FontId {
                    size: 18.0 * self.zoom_level,
                    family: egui::FontFamily::Proportional,
                },
                egui::Color32::PLACEHOLDER,
            );

            let text_galley_rect = text_galley.rect; // Remember text size so we can scale the bouding box properly
            let text_position = egui::pos2(origin.x + x_cor_scaled, origin.y + y_cor_scaled); // We'll set bounding box position by editing this one

            // Paint the prepared text
            painter.galley(text_position, text_galley, COLOR_BLACK);

            // Paint the bouding box
            painter.rect_stroke(
                egui::Rect {
                    min: egui::pos2(
                        text_position.x - border_offset,
                        text_position.y - border_offset,
                    ),
                    max: egui::pos2(
                        text_position.x + text_galley_rect.width() + border_offset,
                        text_position.y + text_galley_rect.height() + border_offset,
                    ),
                },
                2.0,
                egui::Stroke {
                    width: 2.0 * self.zoom_level,
                    color: COLOR_BLACK,
                },
                egui::StrokeKind::Inside,
            );
        }

        //
        response
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

        egui::TopBottomPanel::bottom("bottom_panel").show(ctx, |ui| {
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                ui.add(
                    egui::Slider::new(&mut self.zoom_level, 0.5..=2.0)
                        .suffix("x zoom")
                        .max_decimals(1),
                );
            })
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

                egui::Frame::canvas(&columns[1].style()).show(&mut columns[1], |ui| {
                    self.canvas_logic(ui);
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
