.PHONY: all PdpWord Memory Loader Logger Command

all: PdpWord Memory Loader

PdpWord:
	./run_test.sh PdpWord

Memory:
	./run_test.sh Memory ../Memory.cpp

Loader:
	./run_test.sh Loader "../Loader.cpp ../Memory.cpp"

Logger:
	./run_test.sh Logger "../Logger.cpp"

Command:
	./run_test.sh Command "../Command.cpp"