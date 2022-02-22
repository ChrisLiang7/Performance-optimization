# Cache Optimization

## Purpose
To optimize data cache accesses for the matrix multiply application.

## Name
* Zhisong Liang
* (No partner)

## Status of my lab
* Complete

### To build:
```shell
make clean; make
```

### To run:
```shell
make perf
```

### To compare result:
a python script is provided to compare the results
```shell
make compare
```

### To test original code and optimization code:
* modified file matmul.cpp
* comment and comment out the code snippet on matmul and Allocate2ndMatrix functions. 


