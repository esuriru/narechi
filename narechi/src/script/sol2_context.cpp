#include "script/sol2_context.hpp"

#include "sol/sol.hpp"
#include "core/logger.hpp"
#include "script/lua_script.hpp"
#include "script/raw_component_view.hpp"
#include "glm/glm.hpp"

namespace narechi::script
{
    sol2_context::sol2_context()
    {
        init(true);
        NRC_CORE_DEBUG("sol2 initialized");
    }

    sol::state& sol2_context::get_lua_state()
    {
        return lua_state;
    }

    void sol2_context::init(bool open_libs)
    {
        if (open_libs)
        {
            lua_state.open_libraries(
                sol::lib::base, sol::lib::package, sol::lib::math);
        }

        init_glm();

        lua_state.new_usertype<raw_component_view>("raw_component_view",
            sol::no_constructor,
            "set_depth",
            &raw_component_view::set_depth,
            "get_float",
            sol::overload(&raw_component_view::get_float,
                &raw_component_view::get_float_l),
            "set_float",
            sol::overload(&raw_component_view::set_float,
                &raw_component_view::set_float_l),
            "get_vec2",
            sol::overload(
                &raw_component_view::get_vec2, &raw_component_view::get_vec2_l),
            "set_vec2",
            sol::overload(
                &raw_component_view::set_vec2, &raw_component_view::set_vec2_l),
            "get_str",
            &raw_component_view::get_str,
            "set_str",
            &raw_component_view::set_str);
    }

    void sol2_context::reload()
    {
        lua_state.globals().clear();
        init(true);
    }

    void sol2_context::init_glm()
    {
        auto vec2_multiply_overloads = sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2)
            {
                return v1 * v2;
            },
            [](const glm::vec2& v1, float value)
            {
                return v1 * value;
            },
            [](float value, const glm::vec2& v1)
            {
                return v1 * value;
            });

        auto vec2_divide_overloads = sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2)
            {
                return v1 / v2;
            },
            [](const glm::vec2& v1, float value)
            {
                return v1 / value;
            },
            [](float value, const glm::vec2& v1)
            {
                return v1 / value;
            });

        auto vec2_addition_overloads = sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2)
            {
                return v1 + v2;
            },
            [](const glm::vec2& v1, float value)
            {
                return v1 + value;
            },
            [](float value, const glm::vec2& v1)
            {
                return v1 + value;
            });

        auto vec2_subtraction_overloads = sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2)
            {
                return v1 - v2;
            },
            [](const glm::vec2& v1, float value)
            {
                return v1 - value;
            },
            [](float value, const glm::vec2& v1)
            {
                return v1 - value;
            });

        lua_state.new_usertype<glm::vec2>(
            "vec2",
            sol::call_constructor,
            sol::constructors<glm::vec2(float), glm::vec2(float, float)>(),
            "x",
            &glm::vec2::x,
            "y",
            &glm::vec2::y,
            sol::meta_function::multiplication,
            vec2_multiply_overloads,
            sol::meta_function::division,
            vec2_divide_overloads,
            sol::meta_function::addition,
            vec2_addition_overloads,
            sol::meta_function::subtraction,
            vec2_subtraction_overloads,
            "length",
            [](const glm::vec2& v)
            {
                return glm::length(v);
            },
            "normalize",
            [](const glm::vec2& v)
            {
                return glm::normalize(v);
            });
    }
}
