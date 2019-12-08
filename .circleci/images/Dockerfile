FROM ubuntu:18.04 AS terminal
RUN apt-get update && apt-get install -y\    
    g++\
    git\
    doxygen

FROM ubuntu:18.04 AS tester
RUN apt-get update && apt-get install -y\
      g++\
      make\
      cmake\
      git

RUN git clone https://github.com/google/googletest.git
RUN mkdir -p /googletest/build
WORKDIR /googletest/build
RUN cmake .. && make && make install \
  && rm -rf /googletest

FROM ubuntu:18.04 AS checker
RUN apt-get update && apt-get install -y\
      g++\
      cppcheck\
      valgrind

FROM node:8.10.0 AS doxydeploy
RUN npm install -g --silent gh-pages@2.0.1   