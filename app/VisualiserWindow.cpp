#include <QCloseEvent>
#include <QTimer>
#include "VisualiserWindow.h"
#include "Settings.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QSize VisualiserWindow::DEFAULT_SIZE = QSize(600, 400);
const QPoint VisualiserWindow::DEFAULT_POS = QPoint(650, 20);

/**
 * Create visualiser window
 */
VisualiserWindow::VisualiserWindow(std::shared_ptr<Core::Log> log)
    : QMainWindow(),
      log(log),
      canvas(log, this) {

    // Window configuration
    setWindowIconText(tr("Visualiser"));

    // Window geometry
    Settings settings;
    settings.beginGroup("VisualiserWindow");
    resize(settings.value("size", DEFAULT_SIZE).toSize());
    move(settings.value("pos", DEFAULT_POS).toPoint());

    // Show canvas
    canvas.show();

    // Render timeout
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(render()));
    timer->start(20);
}

VisualiserWindow::~VisualiserWindow() = default;

/**
 * Visualise
 */
void VisualiserWindow::render() {
    canvas.update();
}

/**
 * Add MIDI message to visualisation
 */
void VisualiserWindow::message(Core::Message &message) {
    canvas.addBlock(QPoint(0, message[1]));
}

/**
 * Save window settings on close
 */
void VisualiserWindow::closeEvent(QCloseEvent *event) {
    // Save window size and position
    Settings settings;
    settings.beginGroup("VisualiserWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    // Quit
    event->accept();
}
