project(pq-bot-unit-tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl/")
    set(OPENSSL_INCLUDE_DIRS "/usr/local/opt/openssl/include")  
elseif(UNIX)
    set(PLATFORM_SPECIFIC_LIBS pthread)
endif()

find_package(Boost 1.70 REQUIRED COMPONENTS unit_test_framework)

file(GLOB MY_CODE_SOURCES "./../pq-bot/src/Config.cpp" "./../pq-bot/src/TelegramBotAPI.cpp")
file(GLOB UNIT_TESTS "./*.cpp" "./pq-bot/*.hpp") 

include(CTest)

add_executable(${PROJECT_NAME} ${UNIT_TESTS} ${MY_CODE_SOURCES})

include_directories(
${PROJECT_NAME}
${Boost_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/../pq-bot/src
${CMAKE_CURRENT_SOURCE_DIR}/pq-bot/
)

target_link_libraries(
${PROJECT_NAME}
${Boost_LIBRARIES}
)

# mark test suites for execution
foreach(TEST_SUITE ${UNIT_TESTS}) # create an independent target for each test suite
  # get the test suite name from the *.cpp file
  execute_process(COMMAND bash -c "grep -E 'BOOST_AUTO_TEST_SUITE\\s*[(]' ${TEST_SUITE} | grep -vE '//.*BOOST_AUTO_TEST_SUITE\\s*[(]' | cut -d ')' -f 1 | cut -d '(' -f 2" OUTPUT_VARIABLE SUITE_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
  # ignore empty lines
  if (NOT "" STREQUAL "${SUITE_NAME}")
    # trim "_test" or "_tests" from the end of ${SUITE_NAME}
    execute_process(COMMAND bash -c "echo ${SUITE_NAME} | sed -e 's/s$//' | sed -e 's/_test$//'" OUTPUT_VARIABLE TRIMMED_SUITE_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
    add_test(NAME ${TRIMMED_SUITE_NAME}_unit_test COMMAND ${PROJECT_NAME} --run_test=${SUITE_NAME} --report_level=detailed --color_output --log_format=JUNIT --output_format=XML)
  endif()
endforeach(TEST_SUITE)