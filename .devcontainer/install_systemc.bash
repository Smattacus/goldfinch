#!/bin/bash
export SYSTEMC_VERSION=2.3.3
export SYSTEMC_AMS_VERSION=2.3
export CXX=g++
export SYSTEMC_HOME=/usr/local/systemc-$SYSTEMC_VERSION
export LD_LIBRARY_PATH=/usr/local/systemc-$SYSTEMC_VERSION/lib-linux64

cd /usr/local
cp /workspaces/goldfinch/systemc/systemc-${SYSTEMC_VERSION}.tar.gz .
cp /workspaces/goldfinch/systemc/systemc-ams-${SYSTEMC_AMS_VERSION}.tar.gz .

# Install systemc
tar -xzf systemc-${SYSTEMC_VERSION}.tar.gz

mkdir systemc-${SYSTEMC_VERSION}/objdir

cd systemc-${SYSTEMC_VERSION}/objdir
../configure --prefix=/usr/local/systemc-$SYSTEMC_VERSION
make
make install

# Install systemc-ams
cd /usr/local
tar -xzf systemc-ams-${SYSTEMC_AMS_VERSION}.tar.gz

mkdir systemc-ams-${SYSTEMC_AMS_VERSION}/objdir

cd systemc-ams-${SYSTEMC_AMS_VERSION}/objdir
../configure --prefix=/usr/local/systemc-ams-${SYSTEMC_AMS_VERSION}
make
make install