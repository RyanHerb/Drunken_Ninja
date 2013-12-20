drunken-ninja
=============

## How to compile

In order to build the provided modules, you need to have qmake installed: `sudo apt-get install qtcreator`

To build and run the app:
```bash
cd source/app
qmake drunken-ninja.pro
make
cd bin/release
./drunken-ninja [arguments...]
```

To build and run the provided tests:
```bash
cd source/test
qmake drunken-ninja-test.pro
make
cd bin/release
./drunken-ninja-test
```

To build and run the provided benchmarks:
```bash
cd source/benchmark
qmake drunken-ninja-benchmark.pro
make
cd bin/release
./drunken-ninja-benchmark
```

## User Manual

The main drunken-ninja application provides two different modules:
* Graph generator
* Vertex cover solver

## Graph Generator

Usage:
* `drunken-ninja --generate graph [n] [p]`
* `drunken-ninja --generate tree [n]`
* `drunken-ninja --generate bipartitegraph [n] [p]`
* `drunken-ninja --generate smallcovergraph [n] [p] [k]`

The description of the parameters is as follows:
* `[n]` : number of nodes
* `[p]` : probability (between 0 and 100) of having an edge between two nodes
* `[k]` : cover size  

The generated graphs can be found in `source/out`.


## Vertex Cover Solver

Usage: `drunken-ninja [filename] -t [type] [algorithm]`

#### Type
The type of the input graph. Can be any of the following types:
* `graph`
* `tree`
* `bipartitegraph`
* `smallcovergraph`

#### Algorithm
The algorithm used to calculate a vertex cover. Can be any of the following types:
* `--getcover`
* `--getcover-greedy`
* `--getcover-dfs`
* `--getcover-minisat [k]` 
* `--getcover-k [k]` (supported for smallcovergraph type only)
* `--getcover-fpt [k]` (supported for smallcovergraph type only)