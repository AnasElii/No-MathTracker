// task_manager.h
#pragma once

#include <string>
#include <format>
#include <stdexcept>
#include <ctime>
#include <optional>

namespace MTTracker
{

    struct CustomDate {
        int day;
        int month;
        int year;

        // Default constructor
        CustomDate() : day(1), month(1), year(2026) {}

        // Parameterized constructor
        CustomDate(int d, int m, int y) : day(d), month(m), year(y) {
            if (d < 1 || d > 31 || m < 1 || m > 12) {
                throw std::invalid_argument("Invalid date parameters provided.");
            }
        }

        // Factory to get the current date using <ctime>
        static CustomDate now() {
            std::time_t t = std::time(nullptr);
            std::tm timeinfo{}; // Allocate on the stack (zero overhead)

#if defined(_WIN32)
            // Windows thread-safe version
            localtime_s(&timeinfo, &t);
#else
            // POSIX (Linux/macOS) thread-safe version
            localtime_r(&t, &timeinfo);
#endif

            return CustomDate(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
        }

        // Output DD/MM/YYYY format
        std::string toString() const {
            return std::format("{:02d}/{:02d}/{:04d}", day, month, year);
        }
    };

    class MTTask
    {

    public:
        enum class TASK_STATUS {
            NOT_STARTED,
            IN_PROGRESS,
            COMPLETED,
            ON_HOLD
        };

        enum class MASTERY_LEVEL {
            NOVICE,
            DEVELOPMENT,
            PROFICIENT,
            MASTERED
        };

    public:
        MTTask() = default;

    public:
        float getProgressPercentage() const;
        int getRemainingDays() const;
        bool isOverBudget() const;

    public:
        void updateProgress(int completed);
        void markCompleted();

    private:
        std::string m_topic;
        TASK_STATUS m_status{ TASK_STATUS::NOT_STARTED };
        MASTERY_LEVEL m_masteryLevel{ MASTERY_LEVEL::NOVICE };

        CustomDate m_startDate{};
        CustomDate m_targetCompletionDate{};
        std::optional<CustomDate> m_actualCompletionDate{};
        
        int m_plannedDurationDays;
        std::string m_positionOrExercises;
        std::string m_notesAndReflections;
        int m_completedSteps;
        int m_totalSteps;
    };

} // namespace MTTracker