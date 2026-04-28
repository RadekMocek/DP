GUIMainWindow::GUIMainWindow() {
   // ...
   m_source = new QPlainTextEdit(); // Víceřádkové textové pole
   m_highlighter_light = new Highlighter(); // „Zvýrazňovač“
   m_highlighter_light->setDocument(m_source->document());
   // ...
   QTimer::singleShot(0, this, [this] { setWindowModified(false); });
}