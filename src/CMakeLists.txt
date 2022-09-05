project(Client-server-app)
set(PROJECT_SERVER "Server")
set(PROJECT_CLIENT "Client")

# Настройка конана
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_SERVER} server.cpp)
add_executable(${PROJECT_CLIENT} client.cpp)

target_link_libraries(${PROJECT_SERVER} ${CONAN_LIBS})
target_link_libraries(${PROJECT_CLIENT} ${CONAN_LIBS})
