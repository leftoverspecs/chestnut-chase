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
convert_to_header(destination.vert destination_vert)
convert_to_header(destination.frag destination_frag)
convert_to_header(font.png test_font)
convert_to_header(logo.png logo)
convert_to_header(test.txt test)
convert_to_header(test_gradient.png test_gradient)
convert_to_header(test_music.mp3 test_music)
convert_to_header(test_particle.png test_particle)
convert_to_header(test_sprite.png test_sprite)
convert_to_header(test_spritemap.png test_spritemap)
convert_to_header(sprite.vert sprite_vert)
convert_to_header(sprite.frag sprite_frag)

convert_to_header(player2.png player2)
convert_to_header(leaves.png leaves)
convert_to_header(treelayer1.png treelayer1)
convert_to_header(treelayer2.png treelayer2)
convert_to_header(treelayer3.png treelayer3)

add_library(test_assets INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/destination.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/destination.frag.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/destination.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/destination.vert.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/font.png"
    "${CMAKE_CURRENT_BINARY_DIR}/font.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/blib.wav"
    "${CMAKE_CURRENT_BINARY_DIR}/blib.wav.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/logo.png"
    "${CMAKE_CURRENT_BINARY_DIR}/logo.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.frag.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.vert.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/test.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/test.txt.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_gradient.png"
    "${CMAKE_CURRENT_BINARY_DIR}/test_gradient.png.h"
    "${CMAKE_CURRENT_BINARY_DIR}/test_music.mp3"
    "${CMAKE_CURRENT_BINARY_DIR}/test_music.mp3.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_particle.png"
    "${CMAKE_CURRENT_BINARY_DIR}/test_particle.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_sprite.png"
    "${CMAKE_CURRENT_BINARY_DIR}/test_sprite.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_spritemap.png"
    "${CMAKE_CURRENT_BINARY_DIR}/test_spritemap.png.h"
)
target_include_directories(test_assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")

add_library(assets INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/destination.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/destination.frag.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/destination.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/destination.vert.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/font.png"
    "${CMAKE_CURRENT_BINARY_DIR}/font.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/logo.png"
    "${CMAKE_CURRENT_BINARY_DIR}/logo.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/player2.png"
    "${CMAKE_CURRENT_BINARY_DIR}/player2.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.frag.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/sprite.vert.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/leaves.png"
    "${CMAKE_CURRENT_BINARY_DIR}/leaves.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/treelayer1.png"
    "${CMAKE_CURRENT_BINARY_DIR}/treelayer1.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/treelayer2.png"
    "${CMAKE_CURRENT_BINARY_DIR}/treelayer2.png.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/treelayer3.png"
    "${CMAKE_CURRENT_BINARY_DIR}/treelayer3.png.h"
)
target_include_directories(assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")
