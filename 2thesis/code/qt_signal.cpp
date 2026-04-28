class GUIScene : public QGraphicsScene {
    void NodeClicked(const std::string& id);
}
class GUIMainWindow : public QMainWindow {
    void OnNodeClick(const std::string& id);
}
GUIMainWindow::GUIMainWindow() {
    m_scene = new GUIScene(scene_font, this);
    connect(m_scene, &GUIScene::NodeClicked,
            this, &GUIMainWindow::OnNodeClick);
}