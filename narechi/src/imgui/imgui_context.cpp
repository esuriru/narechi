#include "imgui/imgui_context.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "core/app.hpp"

#include "core/logger.hpp"

namespace narechi
{
    imgui_context::imgui_context() : has_init(false) {}

    void imgui_context::init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        NRC_CORE_DEBUG("ImGui Context initialized");

        // TODO - Use DI
#if defined(NRC_RENDERER_API_OPENGL)
        ImGui_ImplGlfw_InitForOpenGL(
            reinterpret_cast<GLFWwindow*>(
                app::get().get_window().get_native_internal()),
            false);
        // TODO - Hardcoded, remove later
        ImGui_ImplOpenGL3_Init("#version 460");
#elif defined(NRC_RENDERER_API_VULKAN)
        // TODO - ImGui Vulkan init
#endif

        has_init = true;
    }

    void imgui_context::new_frame()
    {
        NRC_ASSERT(
            has_init, "imgui_context::new_frame() called before initializing");

        ImGui_ImplGlfw_NewFrame();
#if defined(NRC_RENDERER_API_OPENGL)
        ImGui_ImplOpenGL3_NewFrame();
#elif defined(NRC_RENDERER_API_VULKAN)
        // TDOO - ImGui Vulkan new frame
#endif
        ImGui::NewFrame();
    }

    void imgui_context::render()
    {
        NRC_ASSERT(
            has_init, "imgui_context::render() called before initializing");

        bool render_demo = true;
        //ImGui::Begin("test");
        ImGui::ShowDemoWindow(&render_demo);
        //ImGui::End();

        ImGui::Render();
#if defined(NRC_RENDERER_API_OPENGL)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif defined(NRC_RENDERER_API_VULKAN)
        // TDOO - ImGui Vulkan RenderDrawData
#endif
    }
}