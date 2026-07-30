# ====== Define Sources ======
if(APPLE)
    file(GLOB_RECURSE PROGRESS_SOURCES "*.cpp" "*.mm" "*.h")
else()
    file(GLOB_RECURSE PROGRESS_SOURCES "*.cpp" "*.h" "*.hpp")
endif()

# ====== Add Library ======
add_library(PROGRESS_SRC STATIC ${PROGRESS_SOURCES})

# ====== Include Directories ======
target_include_directories(PROGRESS_SRC
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ====== Set Folder Properties for Visual Studio ======
set_target_properties(PROGRESS_SRC PROPERTIES FOLDER "src")