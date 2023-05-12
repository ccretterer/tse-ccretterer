/**************** generateQuery ****************/
/* generate one random query and print to stdout.
 * pull random words from the wordlist and from the dictionary.
 */
static void
generateQuery(const wordlist_t* wordlist, const wordlist_t* dictionary)
{
  // some parameters that affect query generation
  const int maxWords = 6;            // generate 1..maxWords
  const float orProbability = 0.3;   // P(OR between two words)
  const float andProbability = 0.2;  // P(AND between two words)
  const float dictProbability = 0.2; // P(draw from dict instead of wordlist)

  int qwords = rand() % maxWords + 1; // number of words in query
  for (int qw = 0; qw < qwords; qw++) {
    // draw a word either dictionary or wordlist
    if ((rand() % 100) < (dictProbability * 100)) {
      printf("%s ", dictionary->words[rand() % dictionary->nWords]);
    } else {
      printf("%s ", wordlist->words[rand() % wordlist->nWords]);
    }

    // last word?
    if (qw < qwords-1) {
      // which operator to print?
      int op = rand() % 100;
      if (op < (andProbability * 100)) {
        printf("AND ");
      }
      else if (op < (andProbability * 100 + orProbability * 100)) {
        printf("OR ");
      }
    }
  }
  printf("\n");
}