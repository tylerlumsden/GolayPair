# TODO

- modularize file reading/writing (e.g. standardized functions defined to read a sequence from a file)
- fix canon_filter so that it removes repeat sequences afterwards
- implement configurable pipeline so that you an exclude certain steps
- change fourier.cpp to use the new decomps or remove entirely
- refactor fourier and dftfilter to work on PSD's, not DFT's. Either have the caller handle PSD logic or nest function call with PSD calculation
- parallelize generation pipeline
- implement dynamic PAF_CONSTANT so we can generate both periodic Golay pairs and Legendre pairs
- add descriptive logging