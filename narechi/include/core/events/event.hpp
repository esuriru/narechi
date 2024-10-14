#pragma once

#include <string>
#include <functional>

namespace narechi
{
    enum class event_type
    {
        none,
        window_close,
        window_resize,
        window_focus,
        window_lost_focus,
        window_moved
    };

    enum event_category
    {
        none = 0,
        application_event_category = 1 << 0,
        input_event_category = 1 << 1,
    };

#define NRC_EVENT_TYPE(type)                      \
public:                                           \
    static event_type get_static_type()           \
    {                                             \
        return event_type::type;                  \
    }                                             \
                                                  \
    virtual event_type get_type() const override  \
    {                                             \
        return get_static_type();                 \
    }                                             \
                                                  \
    virtual const char* get_name() const override \
    {                                             \
        return #type;                             \
    }

#define NRC_EVENT_CATEGORY(category)                \
public:                                             \
    virtual int get_category_flags() const override \
    {                                               \
        return category;                            \
    }

    // Internal events that are generated from callbacks
    // from the context provider
    class event
    {
    public:
        bool handled = false;

        virtual ~event() = default;

        virtual int get_category_flags() const = 0;
        virtual event_type get_type() const = 0;
        virtual const char* get_name() const = 0;

        virtual std::string to_string() const
        {
            return get_name();
        }

        bool in_category(event_category category) const
        {
            return get_category_flags() & category;
        }
    };

    using event_callback_fn = std::function<void(event&)>;

    class event_handler final
    {
    public:
        event_handler(event& event) : event(event) {}

        template<typename T, typename F>
        bool handle(const F& callback)
        {
            if (T::get_static_type() == event.get_type())
            {
                event.handled |= callback(static_cast<T&>(event));
                return true;
            }
            return false;
        }

    private:
        event& event;
    };
}