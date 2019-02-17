# README

The implementation of enumeration algorithm for subgraphs with bounded girth.   

Publication: Kazuhiro Kurita, Kunihiro Wasa, Alessio Conte, Takeaki Uno, and Hiroki Arimura, "Efficient Enumeration of Subgraphs and Induced Subgraphs with Bounded Girth," The 29th International Workshop on Combinatorial Algorithm (IWOCA 2018), National University of Singapore, Singapore, Jul. 16-19, 2018. 

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
