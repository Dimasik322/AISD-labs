cmake_minimum_required(VERSION 3.11)

project(graph CXX)

set(CMAKE_CXX_STANDARD 23)

# ����������� ��������� ��� ����������� Visual Studio
if(MSVC)
    # ���������� ����������� �������� ��� ������������ ���������
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # �������� ������� ������� ��������������
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# ��������� ����������
add_library(graph SHARED "include/graph/graph.h" "src/graph.cc" "include/graph/graph.h")
target_include_directories(graph PUBLIC "include")

# ���������� googletest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ��������� �����
add_executable(tests "tests/tests.cc" "include/graph/graph.h")
target_link_libraries(tests graph GTest::gtest_main)

# �� � ��� ������� ���� �������� ����
add_executable(app "app/app.cc" "include/graph/graph.h")
target_link_libraries(app graph GTest::gtest_main)