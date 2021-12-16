FROM ubuntu:18.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    git \
    valgrind \
    clang \
    make \
    vim

RUN mkdir /project

WORKDIR /project

COPY . /project

CMD    make fclean