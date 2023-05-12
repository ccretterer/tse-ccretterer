## CS50 Querier Design Spec

# User Interface

Per the requirements spec, the user interface is stdin. The user provides an indexer created file and a crawler created page directory. 
The output is the series of document containing words within the query and their respective scores. 

# Functional Decomposition

# Psuedocode

# Major data structures

The querier uses the `counters`, `twoCounters`, `max_data`, and `index` data structures within the code.

Description of the 'counters' and 'index' data structures can be found within the counters.h and index.h header files. Moreover, more description about how the 'index' module is implemented can be found in the implementation spec. 

`twoCounters` data structure allows for two counter_t* objects to be passed within one data structure. This data structure is used within the counters_union and counters_intersect functions. 

`max_data` is a custom data structure (not explicitly defined in the code you provided, but I'll assume it's a struct containing two integer fields: max_doc_id and max_score). It's used to hold the information of a document with the highest score in a set of documents (identified by their document IDs).



# Testing plan 

The querier has both unit testing and system testing. The unit test tests various functions within the 'querier.c' file. The system 
test tests the workability of taking input and providing the correct output. 




