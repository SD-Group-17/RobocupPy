CC = g++
PYLIBPATH = $(shell python-config --exec-prefix)/lib
LIB = -L$(PYLIBPATH) $(shell python-config --libs) -lboost_python
OPTS = $(shell python-config --include) -O2

default: matrix.so
	@python ./script.py

matrix.so: matrix.o
	$(CC) $(LIB) -Wl,-rpath,$(PYLIBPATH) -shared $< -o $@

matrix.o: matrix.cpp Makefile
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -rf *.so *.o

.PHONY: default clean