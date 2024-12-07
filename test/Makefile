.PHONY: all
	all: PdpWord Memory Loader

.PHONY: PdpWord
PdpWord:
	./run_test.sh PdpWord

.PHONY: Memory
Memory:
	./run_test.sh Memory ../Memory.cpp

.PHONY: Loader
Loader:
	./run_test.sh Loader "../Loader.cpp ../Memory.cpp"