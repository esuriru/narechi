#include "imgui/imgui_context.hpp"

#include "backends/imgui_impl_glfw.h"

#ifdef NRC_RENDERER_API_OPENGL
    #include "backends/imgui_impl_opengl3.h"
#endif

#include "imgui.h"

#include "core/app.hpp"

#include "core/logger.hpp"

namespace narechi
{
    imgui_context::imgui_context()
        : has_init(false)
    {
    }

    void imgui_context::init()
    {
        NRC_ASSERT(!has_init, "imgui_context is already initialized");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.FontGlobalScale = 2.0f;

        NRC_CORE_DEBUG("ImGui Context initialized");

#if defined(NRC_RENDERER_API_OPENGL)
        ImGui_ImplGlfw_InitForOpenGL(
            reinterpret_cast<GLFWwindow*>(
                app::get().get_window().get_native_internal()),
            true);
        // TODO - Hardcoded, remove later
        ImGui_ImplOpenGL3_Init("#version 460");
#elif defined(NRC_RENDERER_API_VULKAN)
        // TODO - ImGui Vulkan init
#endif
        ImGui::GetStyle().ScaleAllSizes(3.0f);

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
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    }

    void imgui_context::render()
    {
        NRC_ASSERT(
            has_init, "imgui_context::render() called before initializing");

        ImGui::Render();
#if defined(NRC_RENDERER_API_OPENGL)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif defined(NRC_RENDERER_API_VULKAN)
        // TDOO - ImGui Vulkan RenderDrawData
#endif
    }
}