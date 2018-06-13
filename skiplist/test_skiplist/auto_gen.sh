#Gen dep

ROOT_PATH=${PWD%/*/*}

cd ${ROOT_PATH}/googletest
mkdir -p cmake-build-debug && cd cmake-build-debug

cmake ../ -DCMAKE_INSTALL_PREFIX=./usr/ && make && make install
