# TODO - Replace dashes with underscores?

function(embed_chunk_binary_to_byte_array target binary_file chunk_count
         output_dir output_files
)
    get_filename_component(binary_file_name ${binary_file} NAME_WLE)
    string(REPLACE "-" "_" binary_file_name "${binary_file_name}")
    message(STATUS "Packing ${binary_file_name} as chunks of byte arrays")

    set(chunk_id 0)
    set(file_index 0)

    file(READ "${binary_file}" file_data HEX)

    # Prepend with 0x
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," file_data ${file_data})
    string(LENGTH ${file_data} file_length)
    math(EXPR chunk_size "${file_length} / ${chunk_count}")

    while(${chunk_id} LESS ${chunk_count})
        math(EXPR file_length_left "${file_length} - ${file_index}")

        message(STATUS "Creating chunk ${chunk_id}")

        if(${file_length_left} LESS ${chunk_size})
            string(SUBSTRING ${file_data} ${file_index} -1 chunk_data)
            # Exit the loop
            set(file_index ${file_length})
        else()
            string(SUBSTRING ${file_data} ${file_index} ${chunk_size}
                             chunk_data
            )
            math(EXPR file_index "${file_index} + ${chunk_size}")
        endif()

        if(${chunk_count} STREQUAL "1")
            message(
                STATUS
                    "Since there is one chunk, only one non-numbered output file will be made"
            )
            set(output_file "${output_dir}/${binary_file_name}.cpp")
            # Generate source file
            file(
                WRITE ${output_file}
                "
#include <cstdint>

namespace narechi::embed
{
    extern const uint8_t ${binary_file_name}[] = {${chunk_data}};
    extern const uint32_t ${binary_file_name}_length =
        sizeof(${binary_file_name}) / sizeof(uint8_t);
}
"
            )
        else()
            set(output_file "${output_dir}/${binary_file_name}${chunk_id}.cpp")
            # Generate source file
            file(
                WRITE ${output_file}
                "
#include <cstdint>

namespace narechi::embed
{
    extern const uint8_t ${binary_file_name}${chunk_id}[] = {${chunk_data}};
    extern const uint32_t ${binary_file_name}${chunk_id}_length =
        sizeof(${binary_file_name}${chunk_id}) / sizeof(uint8_t);
}
"
            )
        endif()

        list(APPEND output_files ${output_file})
        math(EXPR chunk_id "${chunk_id} + 1")
    endwhile()
endfunction()

function(embed_binary_to_byte_array_output target binary_file output_file)
    get_filename_component(binary_file_name ${binary_file} NAME_WLE)
    message(STATUS "Packing ${binary_file_name} as byte array")

    file(READ "${binary_file}" file_data HEX)

    if(NOT DEFINED skip_file_hash_cache)
        get_filename_component(output_file_dir ${output_file} DIRECTORY)
        set(output_cache_file
            "${output_file_dir}/${binary_file_name}_cache.txt"
        )
        file(SHA256 ${binary_file} output_file_hash)
        if(EXISTS ${output_cache_file})
            file(READ ${output_cache_file} file_cache)
            if(${file_cache} STREQUAL ${output_file_hash})
                message(
                    STATUS
                        "File has not been changed, not rewriting embed source file"
                )

                # Add to source files in target
                if(NOT DEFINED skip_target_sources)
                    target_sources(${target} PRIVATE ${output_file})
                endif()

                return()
            else()
                message(
                    STATUS
                        "File hash is different from current file, rewriting embed source file"
                )
                file(WRITE ${output_cache_file} ${output_file_hash})
            endif()
        else()
            message(
                STATUS
                    "No file cache found, generating new file hash: ${output_cache_file}"
            )
            file(WRITE ${output_cache_file} ${output_file_hash})
        endif()
    endif()

    # Prepend with 0x
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," file_data ${file_data})

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
")

    # Add to source files in target
    if(NOT DEFINED skip_target_sources)
        target_sources(${target} PRIVATE ${output_file})
    endif()
endfunction()

function(embed_binary_to_byte_array target binary_file)
    get_filename_component(binary_file_name ${binary_file} NAME_WLE)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/${binary_file_name}.cpp)

    embed_binary_to_byte_array_output(${target} ${binary_file} ${output_file})
endfunction()

function(embed_text_to_std_string target text_file)
    get_filename_component(text_file_name ${text_file} NAME_WLE)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/${text_file_name}.cpp)

    message(STATUS "Packing ${text_file_name} as `std::string`")

    file(READ ${text_file} file_data)

    if(NOT DEFINED skip_file_hash_cache)
        get_filename_component(output_file_dir ${output_file} DIRECTORY)
        set(output_cache_file "${output_file_dir}/${text_file_name}_cache.txt")
        file(SHA256 ${text_file} output_file_hash)
        if(EXISTS ${output_cache_file})
            file(READ ${output_cache_file} file_cache)
            if(${file_cache} STREQUAL ${output_file_hash})
                message(
                    STATUS
                        "File has not been changed, not rewriting embed source file"
                )

                # Add to source files in target
                if(NOT DEFINED skip_target_sources)
                    target_sources(${target} PRIVATE ${output_file})
                endif()

                return()
            else()
                message(
                    STATUS
                        "File hash is different from current file, rewriting embed source file"
                )
                file(WRITE ${output_cache_file} ${output_file_hash})
            endif()
        else()
            message(
                STATUS
                    "No file cache found, generating new file hash: ${output_cache_file}"
            )
            file(WRITE ${output_cache_file} ${output_file_hash})
        endif()
    endif()

    # Replace single backslashes with double backslashes
    string(REPLACE "\n" "\\n" file_data "${file_data}")
    string(REPLACE "\"" "\\\"" file_data "${file_data}")

    # Generate source file
    file(
        WRITE ${output_file}
        "
#include <string>

namespace narechi::embed
{
    extern const std::string ${text_file_name} = \"${file_data}\";
}
"
    )

    # Add to source files in target
    if(NOT DEFINED skip_target_sources)
        target_sources(${target} PRIVATE ${output_file})
    endif()
endfunction()
