if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/chardet.h")
    message(FATAL_ERROR "\nCould not find source code.  Make sure you are running this script from the root of the distribution tree.")
endif()

file(GLOB CHARDET_LIBRARY_SOURCES
	"src/*.cpp"
	"tables/*.cpp"
)

add_library(Chardet_decoder_lib ${CHARDET_LIBRARY_SOURCES})

target_include_directories(Chardet_decoder_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)