#!/bin/bash

DEFAULT_LIB_DIRECTORY_PATH="."
MONGOCXX_DRIVER_VERSION="r3.1.1"

libDir=${1:-$DEFAULT_LIB_DIRECTORY_PATH}

install_mongoc(){
   libmongoc="$libDir/mongo-c-driver-1.5.2"
   rm -rf "$libmongoc"
   wget wget https://github.com/mongodb/mongo-c-driver/releases/download/1.5.3/mongo-c-driver-1.5.3.tar.gz
   tar xzf mongo-c-driver-1.5.3.tar.gz
   rm mongo-c-driver-1.5.3.tar.gz
   (cd mongo-c-driver-1.5.3 && ./configure && make && sudo make install)
}

install_mongocxx(){
   libmongocxx="$libDir/mongo-cxx-driver"
   rm -rf "$libmongocxx"
   git clone https://github.com/mongodb/mongo-cxx-driver.git
   (cd mongo-cxx-driver && git checkout tags/$MONGOCXX_DRIVER_VERSION -b $MONGOCXX_DRIVER_VERSION)
   (cd mongo-cxx-driver/build && cmake -DCMAKE_BUILD_TYPE=Release -DLIBBSON_DIR=/usr/local -DLIBMONGOC_DIR=/usr/local ..)
   (cd mongo-cxx-driver/build && make -j 4)
   (cd mongo-cxx-driver/build && make install)
}

install_mongodb_cxx_driver() {
   install_mongoc
   install_mongocxx
}

mkdir -p "$libDir"
install_mongodb_cxx_driver