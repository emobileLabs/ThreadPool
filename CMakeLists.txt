cmake_minimum_required(VERSION 2.8.9)
project (threadpool)

# provides install directory variables CMAKE_INSTALL_<dir>
include (GNUInstallDirs)

set(TARGET_THREADPOOL_APP threadpool_app)

include_directories(BEFORE
  ${threadpool_SOURCE_DIR}
)

set(THREADPOOL_APP_SOURCES
  ThreadPool.cpp
  TaskQueue.cpp
  TaskThread.cpp
  ThreadPoolMain.cpp
)

# Set global variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable (${TARGET_THREADPOOL_APP} ${THREADPOOL_APP_SOURCES})
target_link_libraries (${TARGET_THREADPOOL_APP}
  pthread
)
install ( TARGETS ${TARGET_THREADPOOL_APP}
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

