const QPointer menu_bar = new QMenuBar(this);
setMenuBar(menu_bar);
const QPointer file = menu_bar->addMenu("File");
const QPointer exit_action = file->addAction(Icon(fa::exit), "Exit");
connect(exit_action, SIGNAL(triggered()), this, SLOT(close()));