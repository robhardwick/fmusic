#include "Test.h"

/**
 * Dummy log implementation
 */
void TestLog::message(EvoMu::Core::LogStatus status, const std::string &message) {}

/**
 * Create shared Log object
 */
void EvoMuTest::initTestCase() {
    l = std::make_shared<TestLog>();
}
