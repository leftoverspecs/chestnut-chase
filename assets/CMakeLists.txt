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
convert_to_header(font.png test_font)
convert_to_header(test.txt test)
convert_to_header(test_gradient.png test_gradient)
convert_to_header(test_sprite.png test_sprite)
convert_to_header(test_spritemap.png test_spritemap)
convert_to_header(sprite.vert sprite_vert)
convert_to_header(sprite.frag sprite_frag)

add_library(assets INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}/font.png.h"
    "${CMAKE_CURRENT_BINARY_DIR}/blib.wav.h"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.frag.h"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.vert.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test.txt.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test_gradient.png.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test_sprite.png.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test_spritemap.png.h"
)
target_include_directories(assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")
