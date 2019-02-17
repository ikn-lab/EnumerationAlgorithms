# README

The implementation of enumeration algorithm for subgraphs with bounded girth. 

* EBG: executable file


## Run
	make
	./EBG <input file> <girth>

	
## Input file format
	n m
	u_1 v_1
	...
	u_m v_m
n: the number of vertices, m: the number of edges. 

## Output file format
	run
	dentist solution
	density: the density of dentist subgraph
	u_1 v_1
	...
	u_k v_k
	elapsed time = execution time msec. 
	the number of solutions. 
	i the number of solutions with i edges. 

	

## Example of execution
	make
	./EBG sample_input01 5
