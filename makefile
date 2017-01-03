all:
	g++ -std=c++0x -pthread main.cpp Bisem.cpp -o fcmain

debug:
	g++ -std=c++0x -g node.cpp Word_BST.cpp main.cpp -o indexer_debug
