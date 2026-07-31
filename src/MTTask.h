// task_manager.h
#pragma once

#include <string>
#include <format>
#include <stdexcept>
#include <ctime>
#include <optional>

namespace MTTracker
{
    // Need a conversion function that will take planned duration by days and start date and calculate
    // the target date or taking the target and output the planned duration by days
    struct Date
    {
        int day, month, year;

        // Default constructor
        Date() : day(1), month(1), year(2026) {}

        // Parameterized constructor
        Date(int d, int m, int y) : day(d), month(m), year(y)
        {
            if (d < 1 || d > 31 || m < 1 || m > 12)
            {
                throw std::invalid_argument("Invalid date parameters provided.");
            }
        }

        // Factory to get the current date using <ctime>
        static Date now()
        {
            std::time_t t = std::time(nullptr);
            if (t == -1)
                throw std::runtime_error("Failed to get system time");

            std::tm time_info{}; // Allocate on the stack (zero overhead)

#if defined(_WIN32)
            // Windows thread-safe version
            if (localtime_s(&time_info, &t) != 0)
                throw std::runtime_error("Failed to get local time");
#else
            // POSIX (Linux/macOS) thread-safe version
            if (localtime_r(&t, &time_info) == nullptr)
                throw std::runtime_error("Failed to get local time");
#endif

            return Date(time_info.tm_mday, time_info.tm_mon + 1, time_info.tm_year + 1900);
        }

        // Output DD/MM/YYYY format
        std::string toString() const
        {
            return std::format("{:02d}/{:02d}/{:04d}", day, month, year);
        }
    };

    class MTTask
    {

    public:
        enum class TASK_STATUS
        {
            NOT_STARTED,
            IN_PROGRESS,
            COMPLETED,
            ON_HOLD
        };

        enum class MASTERY_LEVEL
        {
            NOVICE,
            DEVELOPMENT,
            PROFICIENT,
            MASTERED
        };

    public:
        MTTask() = default;
        MTTask(std::string topic, Date target_completion_date, std::string position, std::string notes) :
            m_topic(std::move(topic)),
            m_target_completion_date(target_completion_date),
            m_position_or_exercises(std::move(position)), 
            m_notes_and_reflections(std::move(notes))
        {}

    public:
        int getRemainingDays() const;
        bool isOverBudget() const;

    public:
        void markCompleted() { m_status = TASK_STATUS::COMPLETED; }

    public:
        void set_topic(std::string topic) { m_topic = std::move(topic); }
        void set_status(TASK_STATUS status) { m_status = status; }
        void set_mastery(MASTERY_LEVEL level) { m_mastery_level = level; }
        void set_target_complete_date(Date date) { m_target_completion_date = std::move(date); }
        void set_planned_duration(int duration) { m_planned_duration = duration; }
        void set_position(std::string position) { m_position_or_exercises = std::move(position); }
        void set_note(std::string note) { m_notes_and_reflections = std::move(note); }
        
    public:
        std::string get_topic() const { return m_topic; }
        TASK_STATUS get_statu() const { return m_status; }
        MASTERY_LEVEL get_level() const { return m_mastery_level; }
        Date get_start_date() const { return m_start_date; }
        Date get_target_complete_date() const { return m_target_completion_date; }
        std::optional<Date> get_complete_date() const { return m_completion_date; }


    private:
        std::string m_topic;
        TASK_STATUS m_status{TASK_STATUS::NOT_STARTED};
        MASTERY_LEVEL m_mastery_level{MASTERY_LEVEL::NOVICE};

        Date m_start_date{};
        Date m_target_completion_date{};
        std::optional<Date> m_completion_date{};

        int m_planned_duration{0};
        std::string m_position_or_exercises;
        std::string m_notes_and_reflections;
    };

}