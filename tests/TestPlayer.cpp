#include <QtTest/QtTest>
#include "Log.h"
#include "Player.h"

using namespace EvoMu::Core;

/**
 * Stub logging for tests
 */
class TestLog: public Log {
    void message(LogStatus status, const std::string &message) {
        // TODO
    };
};

/**
 * Test the EvoMu::Core::Player class
 */
class TestPlayer: public QObject {
    Q_OBJECT

    private slots:
        void create();
};

/**
 * Test instantiation
 */
void TestPlayer::create() {
    auto l = std::make_shared<TestLog>();
    Player p(l);

    QCOMPARE(p.isPlaying(), false);
    QCOMPARE(p.isPaused(), false);
}

/**
 * Run tests
 */
QTEST_MAIN(TestPlayer)
#include "TestPlayer.moc"
