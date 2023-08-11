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
    //approx 2x increase

- a few thousand 3-compression candidates
