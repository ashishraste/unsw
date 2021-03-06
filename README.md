### UNSW 

---

Programming task on file IO.


#### Folder Layout
1. `include` - directory for the header files.
2. `src` - directory for the source files.

#### Dependencies
1. Requires Boost library, version >= 1.54.

#### Building
1. From the parent directory (unsw/), do the following.

```
mkdir build; 
cd build;
cmake ../;
make;
``` 

2. Builds two binaries by name : `string_generator` and `string_processor`.


#### Running the binaries
1. For string_generator
```
./string_generator <min-length-of-string> <max-length-of-string> <file-size> <output-file-name>
```

Output : Writes random strings, given length constraints, to a file.


2. For string_processor

```
./string_processor <input-file-of-strings> <output-file> <time-delay> 
```

Output : Reads strings from a given file, sorts them and writes it to another file.

#### Thoughts
1. On string_generator <br/>
Running either or both of string-generation and file-writing, using multiple threads, could speed up the process. Would most likely spike RAM usage but could be faster, a tradeoff! <br/>
2. On string_processor <br/>
Used only a single thread to read (and write) from a file. Multiple threads weren't used because each of them, while reading, may haphazardly shift the input file's 'reader-head' when doing a read() system call. Hence using one thread, the whole file's content were taken into a buffer on which the processing was done. <br/>
The sorting method used in expensiveFunc() is not optimal, has a run-time performance of O(n^2). A trie based structure/mechanism would give an optimal performance. <br/>
3. Overall <br/>
Couldn't attempt the other two tasks, ran short of time. Enjoyed the exercise on file IO, thinking about whether or not threads should be used.

#### Improvements
- [x] For string_processor : Generic merge-sort routine to process strings (or any set of characters) read from a file.
- [x] Multi-threading for writing into a file. Result : no significant improvement over a single-threaded process. Same amount of time and CPU cycles are taken for writing a given chunk of strings to a file.

---
