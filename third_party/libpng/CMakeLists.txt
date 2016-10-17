cmake_minimum_required(VERSION 2.8)

project(libpng)

set(VERSION "1.6.25")

include_directories(${zlib_SOURCE_DIR})

set(LIBPNG_SRCS
  png.c
  pngerror.c
  pngget.c
  pngmem.c
  pngpread.c
  pngread.c
  pngrio.c
  pngrtran.c
  pngrutil.c
  pngset.c
  pngtrans.c
  pngwio.c
  pngwrite.c
  pngwtran.c
  pngwutil.c
)

add_library(libpng ${LIBPNG_SRCS})

