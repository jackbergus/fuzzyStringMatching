# fuzzyStringMatching

This library provides a support for performing fuzzy string matching in secondary memory.

## TODO

1) For the moment, the library uses the primary memory for performing a preliminar index of the structure, and then serialize the data in secondary memory. This approach might not work for big data. Therefore, at the moment I'm planning to allow the user to use temporary secondary memory data structures for keeping all the information that won't fit in RAM.
