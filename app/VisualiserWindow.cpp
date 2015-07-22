#include <QCloseEvent>
#include <QTimer>
#include "VisualiserWindow.h"
#include "Settings.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QColor VisualiserWindow::DEFAULT_COLOUR = QColor(180, 207, 236);

const QSize VisualiserWindow::DEFAULT_SIZE = QSize(600, 400);
const QPoint VisualiserWindow::DEFAULT_POS = QPoint(650, 20);

const int32_t VisualiserWindow::BLOCK_WIDTH = 10;
const int32_t VisualiserWindow::BLOCK_HEIGHT = 10;

const float VisualiserWindow::BLOCKS_X = 1000.0;
const float VisualiserWindow::BLOCKS_Y = 128.0;

/**
 * Create visualiser window
 */
VisualiserWindow::VisualiserWindow(std::shared_ptr<Core::Log> log)
    : QMainWindow(),
      log(log),
      canvas(this) {

    // Window configuration
    setWindowIconText(tr("Visualiser"));

    // Window geometry
    Settings settings;
    settings.beginGroup("VisualiserWindow");
    resize(settings.value("size", DEFAULT_SIZE).toSize());
    move(settings.value("pos", DEFAULT_POS).toPoint());

    // Background brush
    backgroundBrush = QBrush(Qt::black);

    // Render timeout
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(render()));
    timer->start(20);
}

VisualiserWindow::~VisualiserWindow() = default;

/**
 * Visualise MIDI messages
 */
void VisualiserWindow::render() {

    // Get current window size
    QSize winSize = size();

    // Set canvas size
    canvas.setFixedSize(winSize);

    // Create painter
    painter.begin(&canvas);
    painter.setRenderHint(QPainter::Antialiasing);

    // Paint background
    painter.fillRect(0, 0, winSize.width(), winSize.height(), backgroundBrush);

    // Create block brush
    Settings settings;
    settings.beginGroup("Visualiser");
    QBrush blockBrush(settings.value("colour", VisualiserWindow::DEFAULT_COLOUR).value<QColor>());

    // Iterate over blocks
    QMutableVectorIterator<QPoint> it(blocks);
    while (it.hasNext()) {
        QPoint block = it.next();

        // Paint block
        painter.fillRect(
            ((block.x() / BLOCKS_X) * winSize.width()),
            ((block.y() / BLOCKS_Y) * winSize.height()),
            BLOCK_WIDTH,
            BLOCK_HEIGHT,
            blockBrush
        );

        // Move block right
        block.rx()++;

        if (block.x() < BLOCKS_X) {
            // Update block
            it.setValue(block);
        } else {
            // Remove when moved off-screen
            it.remove();
        }
    }

    // Update canvas
    painter.end();
    canvas.update();
}

/**
 * Add MIDI message to visualisation
 */
void VisualiserWindow::message(Core::Message &message) {
    blocks.push_back(QPoint(0, message[1]));
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
