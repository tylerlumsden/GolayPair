# TODO

- modularize file reading/writing (e.g. standardized functions defined to read a sequence from a file)
- fix canon_filter so that it removes repeat sequences afterwards
- implement configurable pipeline so that you an exclude certain steps
- running ./build/debug/main 26 -c 2 takes VERY long at the cache_filter step... should investigate why <--- THIS IS PRE_EXISTING PROBLEM!!!
- Figured out the reason for above! didn't realize that alternating negation is incompatible with compressed sequences! noted in PGP and pairwise balanced designs