INCLUDE_DIR=/usr/local/systemc-2.3.3/include/
LIB_DIR=/usr/local/systemc-2.3.3/lib-linux64
SYSTEMC_LIB=libsystemc.a

all:
	g++ -I${INCLUDE_DIR} -L${LIB_DIR} -l:${SYSTEMC_LIB} hello.cpp -o Hello

run:
	./Hello

clean:
	rm Hello