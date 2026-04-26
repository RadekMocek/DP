GUIMainWindow::GUIMainWindow() {
   // ...
   m_source = new QPlainTextEdit();
   m_highlighter_light = new Highlighter(m_source->document());
   // ...
   QTimer::singleShot(0, this, [this] { setWindowModified(false); });
}