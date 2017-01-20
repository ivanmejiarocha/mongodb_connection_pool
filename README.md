# mongodb_connection_pool
Sample code that shows how to use mongodb's connection pool class

# How to build


1. Install git, CMake, boost, openssl on your system, if you are using macOS this can be acomplished easily with the following command:

        $ brew install cmake git openssl boost
  
2. Clone the repository.

3. Go to the directory mongodb_connetion_pool/libs and execute the script: ./build_dependencies.sh build mongodb C++ Driver for you.

4. Go to the directory mongodb_connectin_pool and type the following commands:

        $ mkdir build
        $ cd build
        $ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

5. Finally type the command:

        $ make -j 8
