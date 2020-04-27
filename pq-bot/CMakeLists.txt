project(pq-bot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)
set(BOOST_LOG_DYN_LINK ON)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl/")
    set(OPENSSL_INCLUDE_DIRS "/usr/local/opt/openssl/include")  
elseif(UNIX)
    set(PLATFORM_SPECIFIC_LIBS pthread)
endif()

find_package(Boost 1.70 REQUIRED COMPONENTS log log_setup)
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx libpq) 

file(GLOB SOURCE_CODE "./src/*.cpp")
add_executable(pq-bot ${SOURCE_CODE})

target_link_directories(
pq-bot PUBLIC ${PQXX_STATIC_LIBRARY_DIRS}
)

include_directories(
pq-bot
${Boost_INCLUDE_DIRS}
${OPENSSL_INCLUDE_DIRS}
${PQXX_STATIC_INCLUDE_DIRS}
)

target_link_libraries(
pq-bot 
PUBLIC ${Boost_LIBRARIES} Boost::log_setup Boost::log
PUBLIC ${OPENSSL_LIBRARIES}
PUBLIC ${PQXX_STATIC_LIBRARIES}
pthread
)
