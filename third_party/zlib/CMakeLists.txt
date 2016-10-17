cmake_minimum_required(VERSION 2.8)

project(zlib)

set(VERSION "1.2.8")

set(ZLIB_SRCS
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzread.c
    gzwrite.c
    inflate.c
    infback.c
    inftrees.c
    inffast.c
    trees.c
    uncompr.c
    zutil.c
)

add_library(zlib ${ZLIB_SRCS})

