include(${NRC_SOURCE_DIR}/cmake/EmbedAsset.cmake)

set(skip_target_sources ON)

message(STATUS "Embedding narechi-player: ${NRC_PLAYER_BINARY}")
embed_chunk_binary_to_byte_array(narechi-launcher 
    "${NRC_PLAYER_BINARY}" 
    "${NRC_PLAYER_CHUNK_COUNT}"
    "${NRC_LAUNCHER_BIN_DIR}" 
    narechi_player_output_files)

unset(skip_target_sources)