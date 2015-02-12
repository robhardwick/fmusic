#include <QtTest/QtTest>
#include "Log.h"
#include "Song.h"

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
 * Test the EvoMu::Core::Song class
 */
class TestSong: public QObject {
    Q_OBJECT

    private slots:
        void create();
};

/**
 * Test instantiation
 */
void TestSong::create() {
    auto l = std::make_shared<TestLog>();
    Song s(l, "function f(t)\nreturn 0, 0, 0\nend");
}

/**
 * Run tests
 */
QTEST_MAIN(TestSong)
#include "TestSong.moc"
