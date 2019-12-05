FROM ubuntu:18.04 as base

RUN apt-get update && apt-get install -y\    
    g++\
    cmake\
    make\
    valgrind\
    git\
    ssh\
    tar\
    gzip\
    ca-certificates\
    cppcheck\
    doxygen
RUN git clone https://github.com/google/googletest.git
RUN mkdir -p /googletest/build
WORKDIR /googletest/build
RUN cmake .. && make && make install \
  && rm -rf /googletest