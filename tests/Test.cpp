#include "Test.h"

/**
 * Dummy log implementation
 */
void TestLog::message(fMusic::Core::LogStatus status, const std::string &message) {}

/**
 * Create shared Log object
 */
void fMusicTest::initTestCase() {
    l = std::make_shared<TestLog>();
}
