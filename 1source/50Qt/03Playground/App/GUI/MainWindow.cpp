#include "Arrow.hpp"
#include "DiagramItem.hpp"
#include "DiagramScene.hpp"
#include "DiagramTextItem.hpp"
#include "MainWindow.hpp"

#include <QtWidgets>

constexpr int InsertTextButton = 10;

MainWindow::MainWindow()
{
    // In the constructor we call methods to create the widgets and layouts of the example before we create the diagram scene.
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    // We connect to the itemInserted() and textInserted() slots of the diagram scenes as we want to uncheck the buttons in the tool box when an item is inserted.
    // When an item is selected in the scene we receive the itemSelected() signal.
    // We use this to update the widgets that display font properties if the item selected is a DiagramTextItem.
    connect(scene, &DiagramScene::itemInserted, this, &MainWindow::itemInserted);
    connect(scene, &DiagramScene::textInserted, this, &MainWindow::textInserted);
    connect(scene, &DiagramScene::itemSelected, this, &MainWindow::itemSelected);
    // The toolbars must be created after the scene as they connect to its signals.
    createToolbars();

    // We then lay the widgets out in the window.
    auto* layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    auto* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}

// In this function we set the QBrush that is used to draw the background of the diagramscene.
// The background can be a grid of squares of blue, gray, or white tiles, or no grid at all. We have QPixmaps of the tiles from png files that we create the brush with.
// When one of the buttons in the background tabbed widget item is clicked we change the brush; we find out which button it is by checking its text.
void MainWindow::backgroundButtonGroupClicked(QAbstractButton* button) const
{
    for (const QList<QAbstractButton*> buttons = backgroundButtonGroup->buttons();
         const QAbstractButton* myButton : buttons) {
        if (myButton != button) {
            button->setChecked(false);
        }
    }
    if (const QString text = button->text(); text == tr("Blue Grid")) {
        scene->setBackgroundBrush(QPixmap(":Resources/images/background1.png"));
    }
    else if (text == tr("White Grid")) {
        scene->setBackgroundBrush(QPixmap(":Resources/images/background2.png"));
    }
    else if (text == tr("Gray Grid")) {
        scene->setBackgroundBrush(QPixmap(":Resources/images/background3.png"));
    }
    else {
        scene->setBackgroundBrush(QPixmap(":Resources/images/background4.png"));
    }

    scene->update();
    view->update();
}

// This slot is called when a button in buttonGroup is checked. When a button is checked the user can click on the graphics view and a DiagramItem of the selected type
// will be inserted into the DiagramScene. We must loop through the buttons in the group to uncheck other buttons as only one button is allowed to be checked at a time.
// QButtonGroup assigns an id to each button. We have set the id of each button to the diagram type,
// as given by DiagramItem::DiagramType that will be inserted into the scene when it is clicked.
// We can then use the button id when we set the diagram type with setItemType().
// In the case of text we assigned an id that has a value that is not in the DiagramType enum.
void MainWindow::buttonGroupClicked(QAbstractButton* button) const
{
    for (const QList<QAbstractButton*> buttons = buttonGroup->buttons(); const QAbstractButton* myButton : buttons) {
        if (myButton != button) {
            button->setChecked(false);
        }
    }
    if (const int id = buttonGroup->id(button); id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    }
    else {
        scene->setItemType(static_cast<DiagramItem::DiagramType>(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}

// This slot deletes the selected item, if any, from the scene. It deletes the arrows first in order to avoid to delete them twice.
// If the item to be deleted is a DiagramItem, we also need to delete arrows connected to it;
// we don't want arrows in the scene that aren't connected to items in both ends.
void MainWindow::deleteItem() const
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    for (QGraphicsItem* item : std::as_const(selectedItems)) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            const auto arrow = qgraphicsitem_cast<Arrow*>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    selectedItems = scene->selectedItems();
    for (QGraphicsItem* item : std::as_const(selectedItems)) {
        if (item->type() == DiagramItem::Type) {
            qgraphicsitem_cast<DiagramItem*>(item)->removeArrows();
        }
        scene->removeItem(item);
        delete item;
    }
}

// The pointerTypeGroup decides whether the scene is in ItemMove or InsertLine mode. This button group is exclusive, i.e., only one button is checked at any time.
// As with the buttonGroup above we have assigned an id to the buttons that matches values of the DiagramScene::Mode enum,
// so that we can use the id to set the correct mode.
void MainWindow::pointerGroupClicked() const
{
    scene->setMode(static_cast<DiagramScene::Mode>(pointerTypeGroup->checkedId()));
}

// Several items may collide, i.e., overlap, with each other in the scene.
// This slot is called when the user requests that an item should be placed on top of the items it collides with.
// QGrapicsItems have a z-value that decides the order in which items are stacked in the scene; you can think of it as the z-axis in a 3D coordinate system.
// When items collide the items with higher z-values will be drawn on top of items with lower values.
// When we bring an item to the front we can loop through the items it collides with and set a z-value that is higher than all of them.
void MainWindow::bringToFront() const
{
    if (scene->selectedItems().isEmpty()) {
        return;
    }

    QGraphicsItem* selectedItem = scene->selectedItems().first();
    const QList<QGraphicsItem*> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem* item : overlapItems) {
        if (item->zValue() >= zValue && item->type() == DiagramItem::Type) {
            zValue = item->zValue() + 0.1;
        }
    }
    selectedItem->setZValue(zValue);
}

// This slot works in the same way as bringToFront() described above, but sets a z-value that is lower than items the item that should be send to the back collides with.
void MainWindow::sendToBack() const
{
    if (scene->selectedItems().isEmpty()) {
        return;
    }

    QGraphicsItem* selectedItem = scene->selectedItems().first();
    const QList<QGraphicsItem*> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem* item : overlapItems) {
        if (item->zValue() <= zValue && item->type() == DiagramItem::Type) {
            zValue = item->zValue() - 0.1;
        }
    }
    selectedItem->setZValue(zValue);
}

// This slot is called from the DiagramScene when an item has been added to the scene.
// We set the mode of the scene back to the mode before the item was inserted,
// which is ItemMove or InsertText depending on which button is checked in the pointerTypeGroup. We must also uncheck the button in the buttonGroup.
void MainWindow::itemInserted(const DiagramItem* item) const
{
    pointerTypeGroup->button(DiagramScene::MoveItem)->setChecked(true);
    scene->setMode(static_cast<DiagramScene::Mode>(pointerTypeGroup->checkedId()));
    buttonGroup->button(item->diagramType())->setChecked(false);
}

// We simply set the mode of the scene back to the mode it had before the text was inserted.
void MainWindow::textInserted(QGraphicsTextItem*) const
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(static_cast<DiagramScene::Mode>(pointerTypeGroup->checkedId()));
}

// When the user requests a font change, by using one of the widgets in the fontToolBar,
// we create a new QFont object and set its properties to match the state of the widgets. This is done in handleFontChange(), so we simply call that slot.
void MainWindow::currentFontChanged(const QFont&) const
{
    handleFontChange();
}

// When the user requests a font change, by using one of the widgets in the fontToolBar,
// we create a new QFont object and set its properties to match the state of the widgets. This is done in handleFontChange(), so we simply call that slot.
void MainWindow::fontSizeChanged(const QString&) const
{
    handleFontChange();
}

// The user can increase or decrease the scale, with the sceneScaleCombo, the scene is drawn in. It is not the scene itself that changes its scale, but only the view.
void MainWindow::sceneScaleChanged(const QString& scale) const
{
    const double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    const QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

// This slot is called when an item in the drop-down menu of the fontColorToolButton is pressed.
// We need to change the icon on the button to the color of the selected QAction.
// We keep a pointer to the selected action in textAction. It is in textButtonTriggered() we change the text color to the color of textAction, so we call that slot.
void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction*>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
        ":Resources/images/textpointer.png",
        qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

// This slot handles requests for changing the color of DiagramItems in the same manner as textColorChanged() does for DiagramTextItems.
void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction*>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
        ":Resources/images/floodfill.png",
        qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

// This slot handles requests for changing the color of Arrows in the same manner that textColorChanged() does it for DiagramTextItems.
void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction*>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":Resources/images/linecolor.png",
        qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

// textAction points to the QAction of the currently selected menu item in the fontColorToolButton's color drop-down menu.
// We have set the data of the action to the QColor the action represents, so we can simply fetch this when we set the color of text with setTextColor().
void MainWindow::textButtonTriggered() const
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

// fillAction points to the selected menu item in the drop-down menu of fillColorToolButton().
// We can therefore use the data of this action when we set the item color with setItemColor().
void MainWindow::fillButtonTriggered() const
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

// lineAction point to the selected item in the drop-down menu of lineColorToolButton. We use its data when we set the arrow color with setLineColor().
void MainWindow::lineButtonTriggered() const
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

// handleFontChange() is called when any of the widgets that show font properties changes. We create a new QFont object and set its properties based on the widgets.
// We then call the setFont() function of DiagramScene; it is the scene that set the font of the DiagramTextItems it manages.
void MainWindow::handleFontChange() const
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

// This slot is called when an item in the DiagramScene is selected. In the case of this example it is only text items that emit signals when they are selected,
// so we do not need to check what kind of graphics item is. We set the state of the widgets to match the properties of the font of the selected text item.
void MainWindow::itemSelected(QGraphicsItem* item) const
{
    if (const auto* textItem = qgraphicsitem_cast<DiagramTextItem*>(item); textItem != nullptr) {
        const QFont font = textItem->font();
        fontCombo->setCurrentFont(font);
        fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
        boldAction->setChecked(font.weight() == QFont::Bold);
        italicAction->setChecked(font.italic());
        underlineAction->setChecked(font.underline());
    }
}

// This slot displays an about box for the example when the user selects the about menu item from the help menu.
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows use of the graphics framework."));
}

// The createToolBox() function creates and lays out the widgets of the toolBox QToolBox.
void MainWindow::createToolBox()
{
    // This part of the function sets up the tabbed widget item that contains the flowchart shapes.
    // An exclusive QButtonGroup always keeps one button checked; we want the group to allow all buttons to be unchecked.
    // We still use a button group since we can associate user data, which we use to store the diagram type, with each button.
    // The createCellWidget() function sets up the buttons in the tabbed widget item and is examined later.
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    connect(buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);

    auto* layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step), 0, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);

    // The buttons of the background tabbed widget item is set up in the same way
    auto* textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":Resources/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    auto* textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    auto* textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    auto* itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::backgroundButtonGroupClicked);

    auto* backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":Resources/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":Resources/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":Resources/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":Resources/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    auto* backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);

    // We set the preferred size of the toolbox as its maximum. This way, more space is given to the graphics view.
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":Resources/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, &QAction::triggered, this, &MainWindow::bringToFront);

    sendBackAction = new QAction(QIcon(":Resources/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, &QAction::triggered, this, &MainWindow::sendToBack);

    deleteAction = new QAction(QIcon(":Resources/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    const QPixmap pixmap(":Resources/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, &QAction::triggered, this, &MainWindow::handleFontChange);

    italicAction = new QAction(QIcon(":Resources/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, &QAction::triggered, this, &MainWindow::handleFontChange);

    underlineAction = new QAction(QIcon(":Resources/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, &QAction::triggered, this, &MainWindow::handleFontChange);

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

// The createToolbars() function sets up the examples tool bars.
void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, &QFontComboBox::currentFontChanged, this, &MainWindow::currentFontChanged);

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2) {
        fontSizeCombo->addItem(QString().setNum(i));
    }

    const auto* validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::fontSizeChanged);

    // The three QToolButtons in the colorToolBar, the fontColorToolButton, fillColorToolButton, and lineColorToolButton, are interesting
    // as we create icons for them by drawing on a QPixmap with a QPainter. We set the menu of the tool button with setMenu().
    // We need the fillAction QAction object to always be pointing to the selected action of the menu.
    // The menu is created with the createColorMenu() function and, as we shall see later, contains one menu item for each color that the items can have.
    // When the user presses the button, which trigger the clicked() signal, we can set the color of the selected item to the color of fillAction.
    // It is with createColorToolButtonIcon() we create the icon for the button.
    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(&MainWindow::textColorChanged, Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":Resources/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, &QAbstractButton::clicked, this, &MainWindow::textButtonTriggered);

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(&MainWindow::itemColorChanged, Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(":Resources/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, &QAbstractButton::clicked, this, &MainWindow::fillButtonTriggered);

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(&MainWindow::lineColorChanged, Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(":Resources/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, &QAbstractButton::clicked, this, &MainWindow::lineButtonTriggered);

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    auto* pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":Resources/images/pointer.png"));
    auto* linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":Resources/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, DiagramScene::MoveItem);
    pointerTypeGroup->addButton(linePointerButton, DiagramScene::InsertLine);
    connect(pointerTypeGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::pointerGroupClicked);

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &MainWindow::sceneScaleChanged);

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
}

// This function creates QWidgets containing a tool button and a label.
// The widgets created with this function are used for the background tabbed widget item in the tool box.
QWidget* MainWindow::createBackgroundCellWidget(const QString& text, const QString& image) const
{
    auto* button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    auto* layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    auto* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

// This function returns a QWidget containing a QToolButton with an image of one of the DiagramItems, i.e., flowchart shapes.
// The image is created by the DiagramItem through the image() function. The QButtonGroup class lets us attach an id (int) with each button;
// we store the diagram's type, i.e., the DiagramItem::DiagramType enum. We use the stored diagram type when we create new diagram items for the scene.
// The widgets created with this function is used in the tool box.
QWidget* MainWindow::createCellWidget(const QString& text, const DiagramItem::DiagramType type) const
{
    const DiagramItem item(type, itemMenu);
    const QIcon icon(item.image());

    auto* button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, type);

    auto* layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    auto* widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

// This function creates a color menu that is used as the drop-down menu for the tool buttons in the colorToolBar.
// We create an action for each color that we add to the menu. We fetch the actions data when we set the color of items, lines, and text.
template <typename PointerToMemberFunction>
QMenu* MainWindow::createColorMenu(const PointerToMemberFunction& slot, const QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue") << tr("yellow");

    auto* colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        auto action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, &QAction::triggered, this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor) {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

// This function is used to create the QIcon of the fillColorToolButton, fontColorToolButton, and lineColorToolButton.
// The imageFile string is either the text, flood-fill, or line symbol that is used for the buttons. Beneath the image we draw a filled rectangle using color.
QIcon MainWindow::createColorToolButtonIcon(const QString& imageFile, const QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    const QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    constexpr QRect target(4, 0, 42, 43);
    constexpr QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

// This function creates an icon with a filled rectangle in the color of color.
// It is used for creating icons for the color menus in the fillColorToolButton, fontColorToolButton, and lineColorToolButton.
QIcon MainWindow::createColorIcon(const QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
