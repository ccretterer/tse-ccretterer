#!bin/bash
#
# testing.sh - testing file to test querier .c
#
# usage: testing.sh
#
# 

make all

echo "Test 1: Incorrect Parameters\n"
./querier 
./querier Dartmouth
./querier hey there how are you
./querier ../testCase filename
./querier ../nonExistant hi 
./querier ./letters ./nonExistentFile
./querier ./letters ../readOnlyFile
./querier ../readOnlyDir failedTest

echo "Test 2: Using crawler created directory"
./querier ./letters outputLetters
./querier ./toscrape outputToScrape

echo "Test 3: Using fuzz query"
./fuzzquery ./letters 27 | ./querier


echo "Test 4: Valgrind"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./querier ./letters outputLetters
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./querier ./toscrape outputToScrape


