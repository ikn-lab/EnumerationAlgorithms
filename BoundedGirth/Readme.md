# Implemetations 
n: the number of vertices, m: the number of edges. 

- *OSedge*: 
	- Outputs: All subgraphs with girth k. 
	- Complexity: amortized O(Poly(n)) time and O(Poly(n)) space. 
- *edge*: 
	- Outputs: All subgraphs with girth k. 
	- Complexity: amortized O(n) time and O(n^3) space. 
- *induced*:  
	- Outputs: All induced subgraphs with girth k. 
	- Complexity: amortized O(n) time and O(n^3) space. 
- *inducedSlow*:  
	- Outputs: All induced subgraphs with girth k. 
	- Complexity: amortized O(n) time and O(n^3) space. 
	- **Note**: The time and space complexity is same as *induced*. However, this implementation has large constant factor than *induced*. 
- *naive_edge*: 
	- Outputs: All subgraphs with girth k
	- Complexity: O(2^m m) total time and O(n + m) space. 
- *naive_induced*: 
	- Outputs: All induced subgraphs with girth k
	- Complexity: O(2^n m) total time and O(n + m) space. 
