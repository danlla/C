# CMakeList.txt: проект CMake для C; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.11)

project ("C")

# Включение высокого уровня предупреждений
if(MSVC) # КомпиляC /W3
    if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/experimental:external /external:anglebrackets /external:W0)
 

elseif(CMAKE_COMPILER_IS_GNUCC) # Компилятор GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wconversion -Wextra -Wpedantic")
endif()


add_subdirectory(begin_bool_int)
add_subdirectory(if_case_for_while_recur)
add_subdirectory(arr_minmax_proc)
add_subdirectory(string_practice)
add_subdirectory(practice_6)
add_subdirectory(vector)
add_subdirectory(image)
add_subdirectory(practice_9_winapi)
