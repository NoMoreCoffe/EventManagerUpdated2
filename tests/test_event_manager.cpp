#include <gtest/gtest.h>
#include "EventManager.h"
#include <chrono>
#include <fstream>
#include <cstdio> // for std::remove

using namespace std::chrono;

class EventManagerTest : public ::testing::Test {
protected:
    std::string filename = "test_events.txt";
    std::string filename2 = "past_events.txt";

    void SetUp() override {
        std::ofstream file(filename);
        file << "15.08.2025 Project kickoff meeting\n";
        file << "20.08.2025 Doctor appointment\n";
        file << "01.09.2025 Start new course\n";

        std::ofstream file2(filename2);
        file2 << "10.08.2025 Test event shouldn't be Visible\n";
        file2 << "15.08.2025 Project kickoff meeting\n";
        file2 << "16.08.2025 Friend's birthday party\n";
        file2 << "25.08.2025 Submit final report\n";

    }

    void TearDown() override {
        std::remove(filename.c_str());
    }
};

TEST_F(EventManagerTest, LoadsEventsFromFile) {
    EventManager manager(filename);

    auto events = manager.getUpcomingEvents(sys_days{year{2025}/month{8}/day{10}});
    ASSERT_EQ(events.size(), 3);

    EXPECT_EQ(events[0].getDescription(), "Project kickoff meeting");
    EXPECT_EQ(events[1].getDescription(), "Doctor appointment");
    EXPECT_EQ(events[2].getDescription(), "Start new course");
}

TEST_F(EventManagerTest, FiltersUpcomingEvents) {
    EventManager manager(filename);

    auto events = manager.getUpcomingEvents(sys_days{year{2025}/month{8}/day{18}});
    ASSERT_EQ(events.size(), 2);

    EXPECT_EQ(events[0].getDescription(), "Doctor appointment");
    EXPECT_EQ(events[1].getDescription(), "Start new course");
}

TEST_F(EventManagerTest, LimitsNumberOfEvents) {
    EventManager manager(filename);

    auto events = manager.getUpcomingEvents(sys_days{year{2025}/month{8}/day{10}}, 2);
    ASSERT_EQ(events.size(), 2);
}

TEST_F(EventManagerTest, ReturnsEmptyIfNoUpcomingEvents) {
    EventManager manager(filename);

    auto events = manager.getUpcomingEvents(sys_days{year{2026}/month{1}/day{1}});
    EXPECT_TRUE(events.empty());
}

TEST_F(EventManagerTest, CorrectPastEventsQntyDisplay) {
    EventManager manager(filename2);
    auto events = manager.getPastEvents(sys_days{year{2025}/month{8}/day{25}});
    // проверить что размер событий 3
    // проверить что названия событий правильные
    // проверить что даты правильные
}