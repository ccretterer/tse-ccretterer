#!/bin/bash


# Test 1: Erroneous Arguments 

# No Arguments
echo "\nNo Arguments passed.\n"
./crawler

# Random Words
echo "\nRandom Words.\n"
./crawler hey there 

# Correct seed url but other wrong parameters 
echo "\nCorrect seed url but other wrong parameters.\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/ NULL 0

# Correct Seed URL and Page Directory, Wrong Depth
echo "\nCorrect Seed URL and Page Directory, Wrong Depth\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/ ./testing -4

# Wrong Seed URL, correct other parameters
echo "\nWrong Seed URL, correct other parameters\n"
./crawler http://www.cs.dartmouth.edu/ ./testing 1

# Test 2: Valgrind 
# Add your valgrind test here
echo "\nValgrind Test\n"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./crawler http://cs50tse.cs.dartmouth.edu/toscrape/ ./testing 1

# Test 3: Runs over all Three Websites  
# Add your tests for three websites with different depths here
echo "\nTesting Letters website\n"
# Add commands for testing Letters website with depths 0, 1, 2, and 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ./letters 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ./letters 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ./letters 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ./letters 10

echo "\nTesting toscrape website\n"
# Add commands for testing toscrape website with depths 0, 1, 2, and 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ./toscrape 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ./toscrape 1
#./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ./toscrape 2
#./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ./toscrape 3

echo "\nTesting Wikipedia website\n"
# Add commands for testing Wikipedia website with depths 0, 1, and 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ./wiki 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ./wiki 1
#./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ./wiki 2




