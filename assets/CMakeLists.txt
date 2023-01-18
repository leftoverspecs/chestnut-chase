macro(convert_to_header INPUT NAME)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${INPUT}.h"
        COMMAND
            "${Python_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/hex_converter.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT}"
            "${NAME}"
            "${CMAKE_CURRENT_BINARY_DIR}/${INPUT}.h"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT}")
endmacro()

convert_to_header(blib.wav blib)
convert_to_header(test.txt test)

add_library(assets INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}/blib.wav.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test.txt.h"
)
target_include_directories(assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")
