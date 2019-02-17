# Implemetations 
n: the number of vertices, m: the number of edges. 

- $\texttt{OSedge}$: 
	- Outputs: All subgraphs with girth $k$. 
	- Complexity: amortized $O(\text{Poly}(n))$ time and $O(\text{Poly}(n))$ space. 
- $\texttt{edge}$: 
	- Outputs: All subgraphs with girth $k$. 
	- Complexity: amortized $O(n)$ time and $O(n^3)$ space. 
- $\texttt{induced}$: 
	- Outputs: All induced subgraphs with girth $k$. 
	- Complexity: amortized $O(n)$ time and $O(n^3)$ space. 
- $\texttt{inducedSlow}$: 
	- Outputs: All induced subgraphs with girth $k$. 
	- Complexity: amortized $O(n)$ time and $O(n^3)$ space. 
	- $\textbf{Note}$: The time and space complexity is same as $\texttt{induced}$. However, this implementation has large constant factor than $\texttt{induced}$. 
- $\texttt{naive_edge}$: 
	- Outputs: All subgraphs with girth $k$
	- Complexity: $O(2^m m)$ total time and $O(n + m)$ space. 
- $\texttt{naive_induced}$: 
	- Outputs: All induced subgraphs with girth $k$
	- Complexity: $O(2^n m)$ total time and $O(n + m)$ space. 
