
if(NOT "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitinfo.txt" IS_NEWER_THAN "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/AmineKhaldi/libsodium-cmake.git" "sodium-src"
    WORKING_DIRECTORY "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/AmineKhaldi/libsodium-cmake.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout f73a3fe1afdc4e37ac5fe0ddd401bf521f6bba65 --
  WORKING_DIRECTORY "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'f73a3fe1afdc4e37ac5fe0ddd401bf521f6bba65'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitinfo.txt"
    "/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/abdulhadihashim/Documents/bls-signatures-main/src/_deps/sodium-subbuild/sodium-populate-prefix/src/sodium-populate-stamp/sodium-populate-gitclone-lastrun.txt'")
endif()

