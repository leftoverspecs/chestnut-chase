configure_file(assets.h.in assets.h)
add_library(assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/assets.h")
target_include_directories(assets INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")

if(ASSETS_DIRECTORY MATCHES "^${CMAKE_INSTALL_PREFIX}")
    install(FILES blib.wav DESTINATION "${ASSETS_DIRECTORY}")
else()
    message(STATUS "Assets: In source, no install")
endif()
