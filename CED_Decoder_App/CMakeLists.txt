set(CED_APP_SOURCES
    #DecoderApp.h
    DecoderApp.cpp
)
add_library(CED_decoder_app ${CED_APP_SOURCES})
target_link_libraries(CED_decoder_app
	CED_decoder_lib    
)
target_include_directories(CED_decoder_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)