#!/usr/bin/env sh
# source this-script

SCRIPT_PATH=$(cd $(dirname $(readlink -f "${BASH_SOURCE[0]}")) && pwd)
export ROOT_PATH="${SCRIPT_PATH%/*/*}"

cd ${ROOT_PATH}/googletest
mkdir -p cmake-build-debug && cd cmake-build-debug

cmake ../ -DCMAKE_INSTALL_PREFIX=./usr/ -DCMAKE_INSTALL_LIBDIR=lib && make && make install

cd ${PHY_PWD}
