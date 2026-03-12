use crate::MyApp;
use egui::{pos2, vec2};

impl MyApp {
    pub fn win_canvas(&mut self, ui: &mut egui::Ui) {
        egui::Window::new("Canvas")
            .collapsible(false)
            .open(&mut self.do_show_win_canvas)
            .show(ui.ctx(), |ui| {
                let (response, painter) =
                    ui.allocate_painter(ui.available_size(), egui::Sense::drag());
                let response_rect = response.rect;
                let origin = response_rect.min.to_vec2();

                painter.rect_filled(
                    egui::Rect::from_min_max(pos2(0.0, 5.0) + origin, pos2(50.0, 55.0) + origin),
                    0,
                    egui::Color32::LIGHT_BLUE,
                );

                painter.circle(
                    pos2(85.0, 30.0) + origin,
                    25.0,
                    egui::Color32::LIGHT_RED,
                    egui::Stroke::new(1.0, egui::Color32::BLACK),
                );

                painter.add(egui::epaint::EllipseShape::filled(
                    pos2(180.0, 30.0) + origin,
                    vec2(60.0, 25.0),
                    egui::Color32::LIGHT_GREEN,
                ));

                painter.add(egui::epaint::EllipseShape::stroke(
                    pos2(180.0, 100.0) + origin,
                    vec2(60.0, 25.0),
                    egui::Stroke::new(1.0, egui::Color32::PURPLE),
                ));

                let shift = origin + vec2(50.0, 100.0);
                let top = pos2(0.0, -15.0) + shift;
                let right = pos2(30.0, 0.0) + shift;
                let bottom = pos2(0.0, 15.0) + shift;
                let left = pos2(-30.0, 0.0) + shift;

                painter.add(egui::epaint::PathShape::convex_polygon(
                    vec![top, right, bottom, left],
                    egui::Color32::DARK_RED,
                    egui::Stroke::new(1.0, egui::Color32::ORANGE),
                ));

                response
            });
    }
}
