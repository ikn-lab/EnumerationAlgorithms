# Implementation 
- *c4*
  - Output: All induced matchings
  - Complexity: amortized constant time for graphs without cycles with the length four and O(n + m) space. For general graphs, this implementation achieves amortized O(Δ^2) time. 
  - Publication: Kazuhiro Kurita, Kunihiro Wasa, Takeaki Uno, and Hiroki Arimura, "Efficient Enumeration of Induced Matchings in a Graph without Cycles with Length Four," IEICE Transactions on Fundamentals of Electronics, Communications and Computer Sciences, Vol.E101.A, No.9, pp.1383-1391, 2018.
- *c4initArray*, *c4fast*, *c4ptr*, and, *c4slow*
	- The time and space complexity is same as c4.
	- **Note**: *c4fast* has bugs. 
- *d2*
  - Output: All induced matchings
  - Complexity: amortized O(Δ^2) time and O(n + m) space. 
- *naive*
  - Output: All induced matchings
  - Complexity: O(2^m) total time and O(n + m) space. 
- *onm*
  - Output: All induced matchings
  - Complexity: O(nm) total time and O(n + m) space. 