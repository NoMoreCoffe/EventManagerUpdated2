#include "EventManager.h"
#include <iostream>
#include <chrono>
#include <format>

int main() {
    try {
        EventManager manager("events.txt");

        auto today = std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now()
        );

        auto past = manager.getPastEvents(today);

        if (past.empty()) {
            std::cout << "No past events." << std::endl;
            std::cout << std::endl;
        }
        else {
            std::cout << "Last #3 Events : \n";
            for (const auto& e : past) {
                auto ymd = std::chrono::year_month_day(e.getDate());
                std::cout
                    << std::format("{:02}.{:02}.{:04} ",
                        unsigned(ymd.day()),
                        unsigned(ymd.month()),
                        int(ymd.year()))
                    << e.getDescription() << "\n";
            }
            std::cout << std::endl;
        }


        auto upcoming = manager.getUpcomingEvents(today);

        if (upcoming.empty()) {
            std::cout << "No upcoming events." << std::endl;
        }
        else {
            std::cout << "Upcomiung Events : \n";
            for (const auto& e : upcoming) {
                auto ymd = std::chrono::year_month_day(e.getDate());
                std::cout
                    << std::format("{:02}.{:02}.{:04} ",
                        unsigned(ymd.day()),
                        unsigned(ymd.month()),
                        int(ymd.year()))
                    << e.getDescription() << "\n";
            }
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
