FROM mcr.microsoft.com/vscode/devcontainers/python:0-3.10-bullseye

ADD *.bash /root/

COPY systemc-2.3.3.tar.gz /usr/local/systemc-2.3.3.tar.gz
COPY systemc-ams-2.3.tar.gz /usr/local/systemc-ams-2.3.tar.gz

RUN /root/build_container.bash