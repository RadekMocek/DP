#pragma once

#include "DiagramItem.hpp"

#include <QMainWindow>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

// MainWindow creates the widgets and displays them in a QMainWindow. It also manages the interaction between the widgets and the graphics scene, view and items.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void backgroundButtonGroupClicked(QAbstractButton* button) const;
    void buttonGroupClicked(QAbstractButton* button) const;
    void deleteItem() const;
    void pointerGroupClicked() const;
    void bringToFront() const;
    void sendToBack() const;
    void itemInserted(const DiagramItem* item) const;
    void textInserted(QGraphicsTextItem* item) const;
    void currentFontChanged(const QFont& font) const;
    void fontSizeChanged(const QString& size) const;
    void sceneScaleChanged(const QString& scale) const;
    void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    void textButtonTriggered() const;
    void fillButtonTriggered() const;
    void lineButtonTriggered() const;
    void handleFontChange() const;
    void itemSelected(QGraphicsItem* item) const;
    void about();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    QWidget* createBackgroundCellWidget(const QString& text, const QString& image) const;
    QWidget* createCellWidget(const QString& text, DiagramItem::DiagramType type) const;

    template <typename PointerToMemberFunction>
    QMenu* createColorMenu(const PointerToMemberFunction& slot, QColor defaultColor);
    static QIcon createColorToolButtonIcon(const QString& imageFile, QColor color);
    static QIcon createColorIcon(QColor color);

    DiagramScene* scene;
    QGraphicsView* view;

    QAction* exitAction;
    QAction* addAction;
    QAction* deleteAction;

    QAction* toFrontAction;
    QAction* sendBackAction;
    QAction* aboutAction;

    QMenu* fileMenu;
    QMenu* itemMenu{};
    QMenu* aboutMenu;

    QToolBar* textToolBar;
    QToolBar* editToolBar;
    QToolBar* colorToolBar;
    QToolBar* pointerToolbar;

    QComboBox* sceneScaleCombo;
    QComboBox* itemColorCombo;
    QComboBox* textColorCombo;
    QComboBox* fontSizeCombo;
    QFontComboBox* fontCombo;

    QToolBox* toolBox;
    QButtonGroup* buttonGroup;
    QButtonGroup* pointerTypeGroup;
    QButtonGroup* backgroundButtonGroup;
    QToolButton* fontColorToolButton;
    QToolButton* fillColorToolButton;
    QToolButton* lineColorToolButton;
    QAction* boldAction;
    QAction* underlineAction;
    QAction* italicAction;
    QAction* textAction;
    QAction* fillAction;
    QAction* lineAction;
};
