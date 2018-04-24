#!/bin/bash

## Managing default directories, args etc...

ORIGIN=$(pwd)

DEFAULT_CMAKE_BUILD_DIR="bin"
EXEC_NAME="cstrike64"

CMAKE_BUILD_DIR=${1}
OUTPUT_DIR=${2}

if [ -z "${CMAKE_BUILD_DIR}" ]; then
  CMAKE_BUILD_DIR=${DEFAULT_CMAKE_BUILD_DIR}
fi

## Making directories

mkdir -p ${CMAKE_BUILD_DIR}/{release,debug}

## BUILD

# Release
cd ${ORIGIN}/${CMAKE_BUILD_DIR}/release
cmake -DCMAKE_BUILD_TYPE=Release ${ORIGIN}
make
objdump -dC ${EXEC_NAME} > ${EXEC_NAME}.asm

# Debug
cd ${ORIGIN}/${CMAKE_BUILD_DIR}/debug
cmake -DCMAKE_BUILD_TYPE=Debug ${ORIGIN}
make
objdump -dC ${EXEC_NAME} > ${EXEC_NAME}.asm
