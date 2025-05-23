# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-src")
  file(MAKE_DIRECTORY "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-src")
endif()
file(MAKE_DIRECTORY
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-build"
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix"
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src"
  "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "G:/Solar System/Solar-System/out/build/x64-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
