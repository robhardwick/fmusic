#ifndef FMUSIC_TESTS_TEST_H
#define FMUSIC_TESTS_TEST_H

#include <memory>
#include <QtTest/QtTest>
#include "Log.h"

/**
 * Stub logging for tests
 */
class TestLog: public fMusic::Core::Log {
    public:
        void message(fMusic::Core::LogStatus status, const std::string &message);
};

/**
 * Base test case
 */
class fMusicTest: public QObject {
    Q_OBJECT

    protected slots:
        void initTestCase();

    protected:
        std::shared_ptr<TestLog> l;
};

#endif
