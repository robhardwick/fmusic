#include <QTimer>
#include <QPainter>
#include "VisualiserWindow.h"

using namespace EvoMu::App;

#define WIN_WIDTH 600
#define WIN_HEIGHT 400

#define BLOCK_WIDTH 10
#define BLOCK_HEIGHT 10

/**
 * Create visualiser window
 */
VisualiserWindow::VisualiserWindow(std::shared_ptr<Core::Log> log)
    : QMainWindow(),
      log(log),
      canvas(this) {

    // Window configuration
    setWindowIconText(tr("Visualiser"));
    setGeometry(650, 20, WIN_WIDTH, WIN_HEIGHT);

    // Canvas configuration
    canvas.setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    // Brushes
    backgroundBrush = QBrush(Qt::black);
    blockBrush = QBrush(QColor(180, 207, 236));

    // Render timeout
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(render()));
    timer->start(50);
}

VisualiserWindow::~VisualiserWindow() = default;

/**
 * Visualise MIDI messages
 */
void VisualiserWindow::render() {

    // Create painter
    QPainter painter;
    painter.begin(&canvas);
    painter.setRenderHint(QPainter::Antialiasing);

    // Paint background
    painter.fillRect(0, 0, WIN_WIDTH, WIN_HEIGHT, backgroundBrush);

    // Iterate over blocks
    QMutableVectorIterator<Block> it(blocks);
    while (it.hasNext()) {
        Block block = it.next();

        // Paint block
        painter.fillRect(block.x, block.y, BLOCK_WIDTH, BLOCK_HEIGHT, blockBrush);

        // Move block right
        block.x++;

        if (block.x + BLOCK_WIDTH < WIN_WIDTH) {
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
    blocks.push_back({
        .x = 0,
        .y = (int)((message[1] / 128.0) * WIN_HEIGHT)
    });
}
