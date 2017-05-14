#### UNSW 

---

Practical programming task on file IO.


#### Folder Layout
1. `include` - directory for the header files.
2. `src` - directory for the source files.

#### Depencendies
1. Requires Boost library, version >= 1.54.

#### Building
1. From the parent directory (unsw/), do the following.
<code>
mkdir build; cd build;
cmake ../;
make;
</code> <br/>

2. Builds two binaries by name : `string_generator` and `string_processor`.


#### Running the binaries
1. For string_generator <br/> 

`./string_generator <min-length-of-string> <max-length-of-string> <file-size> <output-file-name>`


2. For string_processor <br/>

`./string_processor <input-file-of-strings> <output-file> <time-delay> `

#### Thoughts
1. On string_generator <br/>
Running either or both of string-generation and file-writing, using multiple threads, could speed up the process. Would most likely spike RAM usage but could be faster, a tradeoff! <br/>
2. On string_processor <br/>
Used only a single thread to read (and write) from a file. Multiple threads weren't used because each of them, while reading, may haphazardly shift the input file's 'reader-head' when doing a read() system call. Hence using one thread, the whole file's content were taken into a buffer on which the processing was done. <br/>
The sorting method used in expensiveFunc() is not optimal, has a run-time performance of O(n^2). A trie based structure/mechanism would give an optimal performance. <br/>
3. Overall <br/>
Couldn't attempt the other two tasks, ran short of time. Enjoyed the exercise on file IO, thinking about whether or not threads should be used.

---
