// egui (Rust)
egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
   egui::MenuBar::new().ui(ui, |ui| {
      ui.menu_button("File", |ui| {
         if ui.button(concatcp!(ICON_EXIT, " Exit")).clicked() {
            ctx.send_viewport_cmd(egui::ViewportCommand::Close);
         }
      });                    
   });
});

// Dear ImGui (C++)
if (ImGui::BeginMainMenuBar()) {
   if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem(ICON_EXIT" Exit")) {
         glfwSetWindowShouldClose(m_window, GLFW_TRUE);
      }
      ImGui::EndMenu();
   }
   ImGui::EndMainMenuBar();
}