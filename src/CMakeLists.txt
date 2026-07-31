# ====== Define Sources ======
if(APPLE)
    file(GLOB_RECURSE TRACKER_SRC "*.cpp" "*.mm" "*.h")
else()
    file(GLOB_RECURSE TRACKER_SRC "*.cpp" "*.h" "*.hpp")
endif()

# ====== Add Library ======
add_library(MTTracker STATIC ${TRACKER_SRC})

# ====== Include Directories ======
target_include_directories(MTTracker
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ====== Set Folder Properties for Visual Studio ======
set_target_properties(MTTracker PROPERTIES FOLDER "src")