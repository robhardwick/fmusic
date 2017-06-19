#include <QCloseEvent>
#include <QIntValidator>
#include <QGroupBox>
#include <QColorDialog>
#include "VisualiserCanvas.h"
#include "SettingsWindow.h"
#include "Settings.h"
#include "Player.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QSize SettingsWindow::DEFAULT_SIZE = QSize(300, 300);
const QPoint SettingsWindow::DEFAULT_POS = QPoint(100, 100);

/**
 * Create settings window
 */
SettingsWindow::SettingsWindow()
    : QMainWindow() {

    // Window configuration
    setWindowIconText(tr("Settings"));

    // Window geometry
    Settings settings;
    settings.beginGroup("SettingsWindow");
    move(settings.value("pos", DEFAULT_POS).toPoint());
    setFixedSize(DEFAULT_SIZE);

    // Setup player interval input
    settings.endGroup();
    settings.beginGroup("Player");
    intervalEdit.setValidator(new QIntValidator(10, 10000, this));
    intervalEdit.setText(settings.value("interval", fMusic::Core::Player::DEFAULT_INTERVAL).toString());
    connect(&intervalEdit, SIGNAL(textEdited(QString)), this, SLOT(updateInterval(QString)));
    playerFormLayout.addRow(tr("&Interval (ms):"), &intervalEdit);

    // Setup player group
    QGroupBox *playerGroup = new QGroupBox(tr("Player"));
    playerGroup->setLayout(&playerFormLayout);

    // Setup visualiser colour input
    settings.endGroup();
    settings.beginGroup("Visualiser");
    visualiserColourPalette.setColor(QPalette::Button, settings.value("colour", VisualiserCanvas::DEFAULT_COLOUR).value<QColor>());
    visualiserColourBtn.setPalette(visualiserColourPalette);
    visualiserColourBtn.setAutoFillBackground(true);
    visualiserColourBtn.setFlat(true);
    visualiserColourBtn.setFixedSize(QSize(15, 15));
    connect(&visualiserColourBtn, SIGNAL(clicked()), this, SLOT(updateColour()));
    visualiserFormLayout.addRow(tr("&Note Colour:"), &visualiserColourBtn);

    // Setup visualiser group
    QGroupBox *visualiserGroup = new QGroupBox(tr("Visualiser"));
    visualiserGroup->setLayout(&visualiserFormLayout);

    // Setup main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(playerGroup);
    mainLayout->addWidget(visualiserGroup);
    QWidget *config = new QWidget();
    config->setLayout(mainLayout);
    setCentralWidget(config);
}

/**
 * Update interval setting
 */
void SettingsWindow::updateInterval(const QString &text) {
    Settings settings;
    settings.beginGroup("Player");
    settings.setValue("interval", text.toInt());
    settings.endGroup();
}

/**
 * Update colour setting
 */
void SettingsWindow::updateColour() {
    Settings settings;
    settings.beginGroup("Visualiser");

    QColor colour = QColorDialog::getColor(settings.value("colour", VisualiserCanvas::DEFAULT_COLOUR).value<QColor>());
    if (!colour.isValid()) {
        return;
    }

    // Update button colour
    visualiserColourPalette.setColor(QPalette::Button, colour);
    visualiserColourBtn.setPalette(visualiserColourPalette);

    // Update settings
    settings.setValue("colour", colour);
    settings.endGroup();
}

/**
 * Save window settings on close
 */
void SettingsWindow::closeEvent(QCloseEvent *event) {
    // Save window size and position
    Settings settings;
    settings.beginGroup("SettingsWindow");
    settings.setValue("pos", pos());
    settings.endGroup();

    // Quit
    event->accept();
}
