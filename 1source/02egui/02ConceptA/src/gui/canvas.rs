use crate::MyApp;

impl MyApp {
    pub fn gui_canvas(&mut self, ui: &mut egui::Ui) -> egui::Response {
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
        /*
        let pointer_pos_in_canvas;
        if let Some(pointer_pos) = response.interact_pointer_pos() {
            pointer_pos_in_canvas = pointer_pos - origin;
        }
        */

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
