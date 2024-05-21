# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MVC_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MVC_autogen.dir\\ParseCache.txt"
  "MVC_autogen"
  )
endif()
