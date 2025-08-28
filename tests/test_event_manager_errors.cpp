#include <gtest/gtest.h>
#include "EventManager.h"
#include <fstream>
#include <cstdio>

TEST(EventManagerErrors, ThrowsIfFileNotFound) {
    EXPECT_THROW((EventManager("non_existent.txt")), std::runtime_error);
}

TEST(EventManagerErrors, ThrowsOnInvalidLine) {
    std::string filename = "invalid_events.txt";
    {
        std::ofstream file(filename);
        file << "InvalidLineWithoutDate\n";
    }

    EXPECT_THROW((EventManager(filename)), std::runtime_error);

    std::remove(filename.c_str());
}

TEST(EventManagerErrors, ThrowsOnInvalidDateFormat) {
    std::string filename = "bad_date_events.txt";
    {
        std::ofstream file(filename);
        file << "99.99.2025 Impossible date\n";
    }

    EXPECT_THROW((EventManager(filename)), std::runtime_error);

    std::remove(filename.c_str());
}
