if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/compact_enc_det/compact_enc_det.h")
    message(FATAL_ERROR "\nCould not find source code.  Make sure you are running this script from the root of the distribution tree.")
endif()

set(CED_LIBRARY_SOURCES
    compact_enc_det/compact_enc_det.cc
    compact_enc_det/compact_enc_det_hint_code.cc
    util/encodings/encodings.cc
    util/languages/languages.cc
)
add_library(CED_decoder_lib ${CED_LIBRARY_SOURCES})

target_include_directories(CED_decoder_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)