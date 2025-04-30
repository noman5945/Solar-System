# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-src"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-build"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src"
  "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Solar System/Solar System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
