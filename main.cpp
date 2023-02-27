#include "widget.h"

#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto* MyWidget = new Widget;

    auto* comboBoxView = new QComboBox;
    comboBoxView->addItem("Ортогональная");
    comboBoxView->addItem("Перспективная");
    comboBoxView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* comboBoxRendering = new QComboBox;
    comboBoxRendering->addItem("Точки");
    comboBoxRendering->addItem("Треугольники");
    comboBoxRendering->addItem("Линии");
    comboBoxRendering->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* formLayout = new QFormLayout;
    formLayout->addRow(comboBoxView);
    formLayout->addRow(comboBoxRendering);

    auto* panel = new QWidget;
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    panel->setLayout(formLayout);

    auto* hlayout = new QHBoxLayout;
    hlayout->addWidget(MyWidget);
    hlayout->addWidget(panel);

    auto centralWidget = new QWidget;
    centralWidget->setLayout(hlayout);

    QMainWindow window;
    window.setCentralWidget(centralWidget);
    window.resize(1440,720);
    window.show();

    QObject::connect(comboBoxView, &QComboBox::currentTextChanged, MyWidget,[MyWidget,comboBoxView]()
    {
        MyWidget->setTypeOfView(comboBoxView->currentText());
    });
    QObject::connect(comboBoxRendering, &QComboBox::currentTextChanged, MyWidget,[MyWidget,comboBoxRendering]()
    {
        MyWidget->setTypeOfRendering(comboBoxRendering->currentText());
    });



    return a.exec();
}
