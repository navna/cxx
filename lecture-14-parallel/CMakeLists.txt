add_executable("lecture-14-parallel-demo" "parallel-demo.cpp")
add_executable("lecture-14-parallel-multiply" "matrix.h" "multiply.h" "multiply-parallel-v1.h"   "parallel-multiply.cpp")
add_executable("lecture-14-parallel-queue" "queue.cpp")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries("lecture-14-parallel-demo" PRIVATE Threads::Threads)
target_link_libraries("lecture-14-parallel-multiply" PRIVATE Threads::Threads)
target_link_libraries("lecture-14-parallel-queue" PRIVATE Threads::Threads)
