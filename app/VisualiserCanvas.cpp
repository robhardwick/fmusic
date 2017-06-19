#include "VisualiserCanvas.h"
#include "Settings.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QColor VisualiserCanvas::DEFAULT_COLOUR = QColor(180, 207, 236);

const int32_t VisualiserCanvas::BLOCK_WIDTH = 10;
const int32_t VisualiserCanvas::BLOCK_HEIGHT = 10;

const float VisualiserCanvas::BLOCKS_X = 1000.0;
const float VisualiserCanvas::BLOCKS_Y = 128.0;

/**
 * Create visualiser window
 */
VisualiserCanvas::VisualiserCanvas(std::shared_ptr<Core::Log> log, QWidget *parent)
    : QOpenGLWidget(parent),
      log(log) {

    // Background brush
    backgroundBrush = QBrush(Qt::black);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
}

VisualiserCanvas::~VisualiserCanvas() = default;

/**
 * Visualise MIDI messages
 */
void VisualiserCanvas::paintEvent(QPaintEvent *e) {

    // Get parent window
    QWidget *win = parentWidget();
    if (!win) {
        return;
    }

    // Set canvas size
    QSize winSize = win->size();
    setFixedSize(winSize);

    // Create painter
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Paint background
    painter.fillRect(0, 0, winSize.width(), winSize.height(), backgroundBrush);

    // Create block brush
    Settings settings;
    settings.beginGroup("Visualiser");
    QBrush blockBrush(settings.value("colour", DEFAULT_COLOUR).value<QColor>());

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
}

/**
 * Add block to visualisation
 */
void VisualiserCanvas::addBlock(QPoint block) {
    blocks.push_back(block);
}
