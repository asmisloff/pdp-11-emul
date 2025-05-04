TESTS = PdpWord Memory Loader Logger Operand Command Machine Monitor
.PHONY: $(TESTS)
all: $(TESTS)

PY			= 	python3
CC 			= 	g++ -std=c++17 -g -Wall -Wextra
CPP_FILES	= 	$(shell $(PY) cpp_file_list.py)
O_FILES		=	$(shell $(PY) object_file_list.py)
RUN			= 	python3 run.py

LOG: PdpWord Loader
	echo $<

$(O_FILES): $(CPP_FILES)
	$(CC) -c $(CPP_FILES)

PdpWord: ../PdpWordTest.cpp ../../PdpTypes.h
	$(RUN) ../PdpWordTest.cpp

Memory: ../MemoryTest.cpp Memory.o
	$(RUN) $^

Loader: ../LoaderTest.cpp Loader.o Memory.o
	$(RUN) $^

Logger: ../LoggerTest.cpp
	$(RUN) $^

Operand: ../OperandTest.cpp $(O_FILES)
	$(RUN) $^

Command: ../CommandTest.cpp $(O_FILES)
	$(RUN) $^

Machine: ../MachineTest.cpp $(O_FILES)
	$(RUN) $^

Monitor: ../MonitorTest.cpp $(O_FILES)
	$(RUN) $^
