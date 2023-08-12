

# TODO:

- use do while to make code more compact  

- implement a log file of the console (python or shell script)

- exhaustive search on smallest cases (look at ambrose's code), very important that equivalent solutions are ignored
- implement raw equivalence check, to filter out equivalent sequences in results table (not optimizing speed yet)
- create a table of pairs up to equivalence

- clean up code, make it easier to add to

- fix up dft code
//psd's of every vector should be constant, do the check first
//consider the b's with the a's after an a is accepted (add the psd's together)

//save the psd's of a in the outer loop, add them together with the b and then check them.

problem: dft's are taking significantly longer than paf's. This should not be the case.

hypothesis: either the constant recreation of the dft plan, or reallocation of memory is likely causing unnecessary hitching.