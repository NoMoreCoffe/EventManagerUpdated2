#include <gtest/gtest.h>
#include "Event.h"
#include <chrono>

using namespace std::chrono;

TEST(EventTest, StoresDateAndDescription) {
    sys_days date = sys_days{year{2025}/month{8}/day{15}};
    Event e(date, "Project kickoff");

    EXPECT_EQ(e.getDate(), date);
    EXPECT_EQ(e.getDescription(), "Project kickoff");
}

TEST(EventTest, ComparisonByDate) {
    Event earlier(sys_days{year{2025}/month{8}/day{15}}, "Earlier");
    Event later(sys_days{year{2025}/month{8}/day{20}}, "Later");

    EXPECT_TRUE(earlier < later);
    EXPECT_FALSE(later < earlier);
    EXPECT_FALSE(earlier < earlier); // equal dates
}
