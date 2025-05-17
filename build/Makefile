.PHONY: demo clean

ROOT		=	..
DEVICES		=	../devices
CC			=	g++ -std=c++17 -O2 -Wall -Wextra
PY			=	python3
CPP_FILES	=	$(shell $(PY) cpp_file_list.py) ../demo.cpp
O_FILES		=	$(shell $(PY) object_file_list.py) demo.o

all: demo

$(O_FILES): $(CPP_FILES)
	$(CC) -c $(CPP_FILES)

demo: $(O_FILES)
	$(CC) -o pdp11 $(O_FILES)

clean:
	rm -f *.o pdp11