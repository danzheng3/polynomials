CC=g++
C_FLAGS=-g -Wall -std=c++17

SRC_FILES=$(filter-out $(wildcard main.cpp),$(wildcard *.cpp))
APP=chess

custom_tests:
	$(CC) $(C_FLAGS) $(SRC_FILES) main.cpp -o $(APP)

valgrind:
	valgrind --leak-check=full ./$(APP) $(TEST)