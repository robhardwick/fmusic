#include <QtTest/QtTest>
#include "Test.h"
#include "Player.h"

using namespace EvoMu::Core;

/**
 * Test the EvoMu::Core::Player class
 */
class TestPlayer: public EvoMuTest {
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
