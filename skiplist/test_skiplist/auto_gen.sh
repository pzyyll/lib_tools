#!/usr/bin/env sh
# source this-script

PHY_PWD="$(pwd -P)"
export ROOT_PATH="${PHY_PWD%/*/*}"

cd ${ROOT_PATH}/googletest
mkdir -p cmake-build-debug && cd cmake-build-debug

cmake ../ -DCMAKE_INSTALL_PREFIX=./usr/ -DCMAKE_INSTALL_LIBDIR=lib && make && make install

cd ${PHY_PWD}
