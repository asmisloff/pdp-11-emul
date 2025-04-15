.PHONY: all PdpWord Memory Loader Logger Command Machine

all: PdpWord Memory Loader Command Machine

PdpWord:
	./run_test.sh PdpWord

Memory:
	./run_test.sh Memory ../Memory.cpp

Loader:
	./run_test.sh Loader "../Loader.cpp ../Memory.cpp"

Logger:
	./run_test.sh Logger

Operand:
	./run_test.sh Operand "../Operand.cpp ../Machine.cpp../Loader.cpp ../Memory.cpp \
						   ../Command.cpp"

Command:
	./run_test.sh Command "../Command.cpp ../Machine.cpp ../Loader.cpp ../Memory.cpp \
						   ../Operand.cpp"

Machine:
	./run_test.sh Machine "../Command.cpp ../Machine.cpp ../Loader.cpp ../Memory.cpp \
						   ../Operand.cpp"