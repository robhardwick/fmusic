#include "Test.h"
#include "Song.h"

using namespace EvoMu::Core;

/**
 * Test the EvoMu::Core::Song class
 */
class TestSong: public EvoMuTest {
    Q_OBJECT

    private slots:
        void create();
        void empty();
        void constant();
};

/**
 * Test instantiation
 */
void TestSong::create() {
    Song s(l, "");
}

/**
 * Test empty song - always returns (0, 0, 0)
 */
void TestSong::empty() {
    Song s(l,
        "function f(t)\n"
        "  return 0, 0, 0\n"
        "end"
    );

    // Check no message was received
    std::vector<unsigned char> message(3);
    auto result = s.execute(0, message);
    QCOMPARE(result, false);
}

/**
 * Test constant song - always returns the same value
 */
void TestSong::constant() {
    Song s(l,
        "function f(t)\n"
        "  return 1, 1, 1\n"
        "end"
    );

    std::vector<unsigned char> message(3);

    // 0, 100, 200 ... 100000
    for (auto offset = 0; offset < 10000; offset += 100) {

        // Check execution success
        auto result = s.execute(offset, message);
        QCOMPARE(result, true);

        // Check message contents
        for (auto i = 0; i < 3; i++) {
            QCOMPARE(message[i], (unsigned char)1);
        }

    }
}

/**
 * Run tests
 */
QTEST_MAIN(TestSong)
#include "TestSong.moc"
