cmake_minimum_required(VERSION 3.20)
project(engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

if(NOT MSVC)
  add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined)
  add_link_options(-fsanitize=address,undefined)
endif()

add_library(engine INTERFACE)

target_include_directories(engine INTERFACE src)

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>
  USES_TERMINAL)

function(add_task_test name)
  add_executable(${name} tests/${name}.cpp)
  target_link_libraries(${name} PRIVATE engine)
  add_dependencies(check ${name})
  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_task_test(test_vec2)
add_task_test(test_mat3)
add_task_test(test_rect)
add_task_test(test_fixed_time_step)
