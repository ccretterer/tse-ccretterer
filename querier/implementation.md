# Querier

## Carly Retterer, CS50, May 2023

## Querier Implementation

The querier is implemented with `querier.c'. `This program reads and processes search queries from the user based on a provided indexer file and page directory. 'Querier.c' uses functions defined in the `index` module. The `index.c` module belongs to the common library. 

The 'querier.c' file also implements another struct, the twoCounters data structure to facilitate 'and' and 'or' operations when parsing the query. 

## Querier.c

The `querier.c` file uses the `index` and `pagedir` module within the common library. The functional logic to the querier function is broken down as follows:

1. Parse the command line, validate parameters, initialize other modules
2. Tokenize input into words array and convert to all lowercase
3. Parse query using BNF 
4. Score query and print out results in descending order

## Functions in Querier.c


`validateParameters()`: Validates the parameters passed to the main function by checking if the parameters are created by the indexer or crawler.
`readSearchInqueries()`: Reads search queries from the user and processes them.
`storeWords()`: Stores words from the given line in the given words array.
`print_clean_query()`: Prints the cleaned query.
`validate_query()`: Validates the query by checking if there are any syntax errors.
`parse_query_bnf()`: Parses the query based on Backus-Naur Form rules and processes it.
`process_and_or_sequences()`:Processes "and" and "or" sequences in the query.
`copy_counter()`: Copies the counter values from one counter to another.
`counters_intersect()`: Intersects two counters objects.
`counters_intersect_helper():`Helper function for counters_intersect.
`counters_union()`: Merges two counters objects.
`counters_union_helper()`: Helper function for counters_union.
`find_max_scoring_doc()`: Find the maximum scoring document in the counters object.
`find_max_helper()`: Helper function find_max_scoring_doc.
`print_doc_infor()`: Print the document information based on its ID and score 
`rank_and_print_results()`: Rank and print the results

Errors are all printed to stderr and exit with a non-zero exit code.

## Testing Plan

The querier can be tested using crawler-created directories. It can read, write, and check files. The querier also reads from an indexer file in able for the program to process the query. This functionality of query is tested and demonstrated in the unittest and system test - testing.sh.
