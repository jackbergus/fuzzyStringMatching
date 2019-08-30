# fuzzyStringMatching

This library provides a support for performing fuzzy string matching in secondary memory. If the data to be indexed increases the primary memory size, the current code provides some classes performing external merge sorts over variadic data via [varsorter](https://github.com/jackbergus/varsorter). 

## Primary Memory Loading and Indexing

If the datasets fits in primary memory, then use the `FuzzyMatchSerializer` 
class to temporairly store the data, and then serialize (Loading+Indexing) 
the data into secondary memory. New data is loaded into secondary memory
via the method `addGramsToMap`, and then serialized into secondary memory
via `serialize`, where to specify the specific folder where to serialize
the strings. The name of the folder must terminate with  `_csvDir`. 

Then, the class `FuzzyMatch` shall point to the folder containing the
 `_csvDir` ending folders containing the serialized datasets. Such folder
 might contain several others databases.
 
 
## Secondary Memory Loading and Indexing

If the datasets does not fit in primary memory, then use the 
`FuzzyMatchSerializerSEC` class, where you need to provide the  `_csvDir`
ending folder where to create the temporairly files in secondary memory,
and then sort them for then serializing the data. The `serialize`
method of this class only creates the files compliant with the 
`FuzzyMatch` class within the same folder. 


Therefore, both loading methods
create the files in the same formats for the fuzzyStringMatching.