connect(m_scene, &Scene::EmptySpaceClicked, this, &MainWindow::OnEmptySpaceClick);
connect(m_scene, &Scene::NodeClicked, this, &MainWindow::OnNodeClick);
connect(m_scene, &Scene::NodeCtrlClicked, this, &MainWindow::OnNodeCtrlClick);
connect(m_scene, &Scene::NodeHoverEntered, this, &MainWindow::OnNodeHoverEnter);
connect(m_scene, &Scene::NodeHoverLeft, this, &MainWindow::OnNodeHoverLeave);
connect(m_scene, &Scene::GhostNodePlaced, this, &MainWindow::OnGhostNodePlace);