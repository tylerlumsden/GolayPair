# Ambrose code
    - important function: generate_equivalence_class
    -  generates equivalence classes on several equivalence relation functions, stores these classes in a hashmap.
    - This probably is an optimization by creating all equivalence classes beforehand, and then operating on one item in each equivalence class.
    ^ I should confirm this hypothesis

//generate from the row sums rather than generating and picking the right row sums
//implement PSD's to filter (fftw.org calculates this)
//ambrose uses this ^^

//look at ambrose's code for equivalence class checking (lex smallest)
// ambrose's code in general

# benchmarks
    - unoptimized: 27 hours for order 20 prog: 2500 time: 240 seconds
    - optimized w/ Row Sums: approx. 3x faster prog: 2500 time: 106 seconds pairs found: 1154
    - optimized w/ Power Representation 6 or 12: prog: 2500 time: 94 seconds (Found no pairs, which is probably why.)
    - optimized row sums eliminating sequences of A that satisfy neither Power Representation: prog: 2500 time: 36 seconds pairs found: 1154

    //ORDER 18 exhaustive w/o seq b starting at combination a time: 1628 seconds pairs found: 0
    //ORDER 18 exhaustive w/seq b starting at combination a time:776 seconds pairs found: 0
    //ORDER 18 exhaustive w/ prev. + DFT's time: 730 seconds pairs found: 0

    //ORDER 18 exhaustive w/ mangled DFT code: 254 seconds pairs found: 0
    ^ unsure why???? Maybe the a's previously had some slowdown

    //ORDER 18 exhaustive w/ DFT code filtering only a sequences time: 363 seconds, pairs found: 0

    //ORDER 18 exhaustive w/ DFT code filtering both a and b sequences time: 208 seconds, pairs found: 0

    problem: the dft filtering of both and b fails to find pairs at prog:2500 ORDER 20 unlike previous code. 
    The code still works for order 4.

    ^^problem solved, was using dftA for both plans by mistake.

    //ORDER 18 exhaustive w/ DFT code filtering both a and b sequences WORKING CODE time: 229 seconds, pairs found: 0
    //ORDER 18 exhaustive w/ DFT code filtering only a sequences WORKING CODE time: 535 seconds, pairs found: 0

    //ORDER 18 exhaustive w/ DFT code filtering only a and b sequences + row sums time: 105 seconds, pairs found: 0
    ---------->> plus with generating from row sums rather than just checking time: 14 seconds (huge!)





    //approx 2x increase

    //prog: 300 50 seconds

- a few thousand 3-compression candidates

//psd real part squared plus imaginary part squared of every entry (currently not using imaginary part)
//norm in ambrose's code was real part squared plus imaginary part squared

//psd's of every vector should be constant, do the check first
//consider the b's with the a's after an a is accepted (add the psd's together)

//save the psd's of a in the outer loop, add them together with the b and then check them.

- I should log the end progress and pairs found at the very end of the runtime. Or, I can log at some interval so that we can compare mid-progress later.

- Next step is equivalences
- cyclic shift, multiplication by -1, alternating multiplication by -1,
- decimation x(i) -> x(k * i mod n, k and n are coprime)

- figure out how to pick the smallest sequence, lex order to pick the smallest

try to make a table of these solutions by tuesday up to equivaleces:
- include the runtime of these
1,2,4,5,8,9,10

--> then

- ilias will provide the compressions and the uncompressions code
- given multiple compressions, remove the ones that are equivalent

- Next step is equivalences
- cyclic shift, multiplication by -1, alternating multiplication by -1,
- decimation x(i) -> x(k * i mod n, k and n are coprime)

- figure out how to pick the smallest sequence, lex order to pick the smallest

try to make a table of these solutions by tuesday up to equivalences:
-  include the runtime of these
1,2,4,5,8,9,10

--> then
- ilias will provide the compressions and the uncompressions code
- given multiple compressions, remove the ones that are equivalent