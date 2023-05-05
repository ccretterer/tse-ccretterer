#!bin/bash
#
# testing.sh - testing file to test indexer.c
#
# usage: testing.sh
#
# 

make all

echo "Test 1: Incorrect Parameters\n"
./indexer 
./indexer Dartmouth
./indextest
./indexer hey there how are you
./indexer ../testCase filename
./indexer ../nonExistant hi 
./indexer ./letters ./nonExistentFile
./indexer ./letters ../readOnlyFile
./indexer ../readOnlyDir failedTest

echo "Test 2: Using crawler created directory"
./indexer ./letters outputLetters
./indexer ./toscrape outputToScrape

echo "Test 3: Using Indextest"
./indextest ./outputLetters indexTestOutputLetters

echo "Test 4: Valgrind"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indexer ./letters outputLetters
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indexer ./toscrape outputToScrape
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indextest ./outputLetters indexTestOutputLetters


