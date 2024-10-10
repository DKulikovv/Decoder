set(CHARDET_APP_SOURCES
    testapp.cpp
)
add_library(Chardet_decoder_app ${CHARDET_APP_SOURCES})
target_link_libraries(Chardet_decoder_app
	Chardet_decoder_lib    
)
target_include_directories(Chardet_decoder_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)