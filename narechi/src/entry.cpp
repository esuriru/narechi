#include <iostream>

#include "core/core.hpp"
#include "core/logger.hpp"
#include "core/assert.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
    NRC_CORE_LOG(glm::to_string(glm::vec3(8, 4, 2)));
}
