FROM ubuntu:latest
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y gcc make git binutils libc6-dev gdb sudo
RUN apt install -y wget python3-pip
RUN adduser --disabled-password --gecos '' user
RUN echo 'user ALL=(root) NOPASSWD:ALL' > /etc/sudoers.d/user
USER user
RUN wget -P ~ https://git.io/.gdbinit
RUN pip3 install pygments

WORKDIR /home/user

