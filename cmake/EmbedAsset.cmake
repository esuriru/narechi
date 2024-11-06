# TODO - Replace dashes with underscores?

function(embed_binary_to_byte_array target binary_file)
    get_filename_component(binary_file_name ${binary_file} NAME_WLE)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/${binary_file_name}.cpp)

    message(STATUS "Packing ${binary_file_name} as byte array")

    file(READ ${binary_file} file_data HEX)

    # Prepend with 0x
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1,"
        file_data ${file_data}
    )

    # Generate source file
    file(WRITE ${output_file}
        "
#include <cstdint>

namespace narechi::embed
{
    extern const uint8_t ${binary_file_name}[] = {${file_data}};
    extern const uint32_t ${binary_file_name}_length =
        sizeof(${binary_file_name}) / sizeof(uint8_t);
}
"
    )

    # Add to source files in target
    target_sources(${target} PRIVATE ${output_file})
endfunction()

function(embed_text_to_std_string target text_file)
    get_filename_component(text_file_name ${text_file} NAME_WLE)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/${text_file_name}.cpp)

    message(STATUS "Packing ${text_file_name} as `std::string`")

    file(READ ${text_file} file_data)

    # Replace single backslashes with double backslashes
    string(REPLACE "\n" "\\n" file_data "${file_data}")
    string(REPLACE "\"" "\\\"" file_data "${file_data}")

    # Generate source file
    file(WRITE ${output_file}
        "
#include <string>

namespace narechi::embed
{
    extern const std::string ${text_file_name} = \"${file_data}\";
}
"
    )

    # Add to source files in target
    target_sources(${target} PRIVATE ${output_file})
endfunction()