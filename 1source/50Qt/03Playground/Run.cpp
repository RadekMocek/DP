#include <QApplication>
#include <QStyleFactory>
#include <QStyleHints>

#include "App/GUI/MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    if (QStyleFactory::keys().contains("Fusion")) {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
    }
    else {
        qWarning() << "Fusion style not supported. Falling back to default style.";
    }

    // Default to light mode
    QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);

    MainWindow window;
    window.show();

    return QApplication::exec();
}
