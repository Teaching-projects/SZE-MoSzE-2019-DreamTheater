FROM debian AS doxy
RUN apt-get update && apt-get install -y\
    git\
    doxygen\
    texlive\
    texlive-latex-extra\
    texlive-lang-european\
    texlive-lang-cyrillic\
    make\
    && apt-get autoclean

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
      git\
      cppcheck\
      valgrind
