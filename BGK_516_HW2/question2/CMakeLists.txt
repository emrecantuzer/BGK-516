cmake_minimum_required(VERSION 3.29)
project(question2 C)

set(CMAKE_C_STANDARD 11)

set(GMP_DIR "C:/msys64/mingw64")
set(MPFR_DIR "C:/msys64/mingw64")

include_directories(${GMP_DIR}/include)  
include_directories(${MPFR_DIR}/include)  

link_directories(${GMP_DIR}/lib) 
link_directories(${MPFR_DIR}/lib) 

add_executable(question2 main.c)



target_link_libraries(question2 mpfr gmp)