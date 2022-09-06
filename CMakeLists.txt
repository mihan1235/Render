cmake_minimum_required(VERSION 3.18)

project(RENDER)
include(CMakePrintHelpers)

# add_library(Dll1Regex SHARED "Dll1Regex/dll1regex.cpp" "Dll1Regex/dll1regex.h")

file(GLOB render_srcs Render/*.cpp)
file(GLOB render_header_files Render/*.h Render/*.hpp) 

add_executable(render ${render_srcs} ${render_header_files})

# file(GLOB bullet_libs "/usr/lib/x86_64-linux-gnu/libBullet*.so" "/usr/lib/x86_64-linux-gnu/libBullet*.so*")
# link_directories("/usr/lib/x86_64-linux-gnu/")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/bullet/")
find_package(Bullet REQUIRED)
include_directories(${Bullet_INCLUDE_DIRS})
link_directories(${Bullet_LIBRARY_DIRS})
add_definitions(${Bullet_DEFINITIONS})

include_directories(Render "/usr/include/bullet" ${GLEW_INCLUDE_DIRS})

find_package(GLEW REQUIRED)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})


include_directories("/usr/include/glm")

list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/glfw3/")
find_package(glfw3 REQUIRED)
# include_directories(${GLFW_INCLUDE_DIRS})
# link_directories(${GLFW_LIBRARY_DIRS})
# add_definitions(${GLFW_DEFINITIONS})

include_directories("/usr/include/")
file(GLOB freeimage_libs "/usr/lib/x86_64-linux-gnu/libfreeimage*.a" 
    "/usr/lib/x86_64-linux-gnu/libfreeimage*.so")
link_directories("/usr/lib/x86_64-linux-gnu/")

list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/assimp-5.0/")
find_package(assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
add_definitions(${ASSIMP_DEFINITIONS})


cmake_print_variables(${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES} ${BULLET_LIBRARIES} ${ASSIMP_LIBRARIES} ${freeimage_libs} glfw)
    
target_link_libraries(render #${bullet_libs}
 ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} glfw ${BULLET_LIBRARIES} ${ASSIMP_LIBRARIES} ${freeimage_libs})


# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__linux__")

