#include "graphics/render2d.hpp"

#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include "graphics/vertex_array.hpp"
#include "graphics/render_command.hpp"

#include "core/core.hpp"
#include "graphics/shader.hpp"
#include "asset/embed.hpp"

NRC_DECL_EMBED_STD_STRING(texture_v);
NRC_DECL_EMBED_STD_STRING(texture_f);

namespace
{
    using narechi::sptr;
    using namespace narechi::graphics;

    sptr<narechi::graphics::shader> texture_shader;

    glm::mat4 view_matrix;
    glm::mat4 proj_matrix;

    sptr<vertex_array> quad_vertex_array;
    sptr<vertex_buffer> quad_vertex_buffer;
    sptr<index_buffer> quad_index_buffer;
}

namespace narechi::graphics::render2d
{
    void init()
    {
        using namespace embed;

        texture_shader
            = shader::create("texture", texture_v.c_str(), texture_f.c_str());

        // clang-format off
        std::vector<float> vertices = 
        {
            {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
            }
        };

        std::vector<uint32_t> indices = 
        {
            {
                0, 1, 2, 
                2, 3, 0
            }
        };
        // clang-format on

        quad_vertex_buffer = vertex_buffer::create(
            vertices.data(), vertices.size() * sizeof(float));
        quad_vertex_buffer->set_layout({
            { shader_data_type::float3, "vertex_pos" },
            { shader_data_type::float2, "vertex_uv" },
        });

        quad_index_buffer
            = index_buffer::create(indices.data(), indices.size());

        quad_vertex_array = vertex_array::create();
        quad_vertex_array->add_vertex_buffer(quad_vertex_buffer);
        quad_vertex_array->set_index_buffer(quad_index_buffer);
    }

    void set_view_matrix(const glm::mat4& mat)
    {
        view_matrix = mat;
    }

    void set_proj_matrix(const glm::mat4& mat)
    {
        proj_matrix = mat;
    }

    void submit_quad(const glm::vec2& world_pos, const glm::vec2& size,
        sptr<graphics::texture2d> texture)
    {
        texture_shader->bind();

        glm::mat4 model_matrix = glm::translate(glm::identity<glm::mat4>(),
                                     glm::vec3(world_pos, 0.0f))
            * glm::scale(glm::identity<glm::mat4>(), glm::vec3(size, 0.0f));

        glm::mat4 MVP = proj_matrix * view_matrix * model_matrix;

        texture_shader->set_mat4("MVP", MVP);

        if (texture)
        {
            texture->bind(1);
            texture_shader->set_int("tex", 1);
        }

        render_command::draw_indexed(quad_vertex_array);
    }
}