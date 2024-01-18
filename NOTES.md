Candidate Compressions A
    10,000 Candidates -> 2138s

Candidate Compressions B
    10,000 Candidates -> 320s

    Regenerate Classes of 2112 candidates (a)
    --> 23.14s

    Generate the first time (a)
    --> 125s

https://link.springer.com/article/10.1007/s10801-021-01084-0
^^ 
great resource, contains table of pgp up to length 40 up to equivalence

//11553

- https://archive.org/details/introductiontoko00limi_695
explains why probability is not the right concept to characterize the randomness of a sequence
first chapter


- changed the way the equivalence classes are checked for a sequence already found
- touch on previous slowdown during runtime, whereas now there is a speedup
- order 32 now takes the same time as order 26
- order 34 will probably take the time estimated previously for order 32
- found neat resource with a table of pbp up to length 40 
https://link.springer.com/article/10.1007/s10801-021-01084-0
- touch on compression generation results
- touch on how using equivalences on pairs will now probably result in speedup due to the significant matching time
- ask about the procedure for decompressing sequences ?? if we use one ??
- ask for title of project


//current match_pairs doesnt work because it skips over doubled pairs (assumes that every psd in a single file is unique)


order 32
row sums -> 0,8

0 -> 16 +, 16 - 

==> p(32!/16! * 16!) = number of sequences to search thru

18100000 <-- all candidates were enumerated at this count
601080390 <-- total count of all sequences

order 34 
row sums -> 2, 8

2 =>

18 +, 16 -

==> p(34! / 18! * 16!) = 2203961430 10 digits vs 17179869184 11 digits



order 26 rowsums 4,6

4 => 15 +, 11 -

= 7726160 sequences



2^40 13 digits

row sums -> 4, 8

18, 22 ==> 12 digits


interesting phenomenon where all candidates found have the first element as -1.
Perhaps no new candidates will be found in the latter half of sequences?

--?..? => -+?..? - +++..+


-- cannot construct a seq with only one -, 
--- cannot construct a seq with only 2 -.
---- cannot construct a seq with only 3 -.
.......
.......

October 2 ----------

nia     (ssh -Y ikotsire@niagara.computecanada.ca)
ced     (ssh -Y ikotsire@cedar.computecanada.ca)
bel     (ssh -Y ikotsire@beluga.calculcanada.ca)
scp $1 ikotsire@niagara.computecanada.ca:$1
bash cuw pg.tar
where cuw is an 1-line bash script
aa
https://docs.alliancecan.ca/wiki/Niagara
https://docs.alliancecan.ca/wiki/Running_jobs

MAKE SURE TO RECOMPILE ON THE CLUSTER

Order 34 seems to generate all candidates after 526s of computation

order 40 ->
rowsums 4,8

4 implies 22 +, 18 -

==> p(40, 22 * 18) = 12 digits

8 implies 16 -, 24 +

=> 11 digits

October 7
----------------

order 16 equivalence filter --> 30s
order 20 equivalence filter --> 725s
order 26 equivalence filter --> 6282s

touch on how sharcnet runs 2x slower
talk about the equivalence filter problem


equivalence operations will be tricky for the uncompression code, look at each operation individually (lots of unnecessary equivalences)

shift by a multiple of N compression for equivalent un-compressions

look into orderly generation kochen specker paper

concatenate a and b ==> most of the shifts a will be irrelevant because most shifts will make a larger a
if a shift of a is equal to itself ==> low bits become relevant (relatively unlikely)

^^ considered equivalence class will become much smaller


psd's of the compressions being integer values at n / 3

Questions:
How is concatenating any different from considering the sequences separately?
Why wouldn't considering the higher bits and then the lower bits create an incomplete class (incomplete in the sense of sequences we require)?

October 9:
    Look into MPI approach with shared memory
    fix the equivalence filter: try to apply shifts to only one sequence to remove the double for loop




-+----+++-+++-+---+-

9 +, 11 -

rowsum -2


---+-++-+++-++++-+++

12 +, 8 -

rowsums 4

October 11
---------------

worry: The files that the processes return should be disjoint; I don't think they are?
nah they are disjoint actually

ORDER 50 
==> rowsum 0, 10

0 ==> 25 +, 25 - 

10 ==> 30 +, 20 -

October 16
------------
try to recreate the results of the order 72 uncompression but with orderly generation

October 27
--------------
ORDER 90 3-compressions

--> 2^60 total sequences

--> alphabet of {-3, -1, 1, 3}

====> 127 ways to partition these into a sum of 6
====> 122 ways to partition these into a sum of 12

n = 12:
 3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+-3+-3+-3+-3+-3+-3+-3+-3+-3+-3+-3+-3+-3

 17 3's 13 -3's

 ==> 119,759,850 sequences (9 digits)
12 seconds for next_permutation to finish

with O3 -- 0s (assume it's ~1s)


one other possible partition(out of ~120)

13 1's, 10 -1's, 4 3's, 3 -3's

==> 30! / (13! * 10! * 4! * 3!)
= 8.15x10^13 (14 digits)
extrapolating from previous data, ~14 days for next_permutation to finish

==> assuming the 120 partitions are equal in size, 5 years to permute through every possible 3-compression of a's

with a parallel factor of 1000, perhaps roughly 2 days.

^^ divide all of that information roughly by 10 (maybe more), due to the O3 optimization

32, 16+, 16- ==> 29s
34, 18+, 16- ==> 103s

compile with -O3

32, 16+, 16- ==> 2s
34, 18+, 16- ==> 11s


(interesting tidbit), arrays permuted 2x~ faster than vectors 

suggestion:
separate the search into these 120~ base sequences\


order 50 should easily be doable without orderly generation
(~5x estimated speedup)



October 28
------------
middle of the set of partitions

--> 9 3's 5 1's, 5 -3's, 11 -1's

==>  1.27x10^15 sequences (16 digits), likely worst case



--> 7 3's 11 1's, 5 -1's, 7 -3's

==> 2.18x10^15 (16 digits), likely worst case

==> at worst, 2.18x10^15 * 127 = 276.86x10^15 = 6.86x10^17 sequences upper bound for 90 3-compressions

10^8 takes 1s 
==> 10^9 seconds * 6.86
==> 6 billion seconds
==> 11574 days * 6
==> 31 years * 6
==> parallel factor of 1000 becomes 66 days
==> this is just permuting through all compressions; psd's + orderly generation of each sequence will take longer
assuming 10^8 takes 0.5s, divide all of this by 2.

a single worst case partition 
2.18x10^15 
==> 2.18x10^7 seconds
==> 231 days
==> parallel factor of 1000 becomes 0.231 days
assuming 10^8 takes 0.5s, divide all of this by 2.

these calculations are on home pc, so on sharcet it will be close to 2x longer

this is just for a's, the b's are likely smaller in count though.


previous RRG on graham - 155 CPU years remaining
                       - 16 CPU years used


ask ilias if he has a RAC submission 

on overleaf upload the latex template document, ask ilias if he can upload his own latex document from previous submissions and perhaps base the submission off of that

find how long it takes to find a solution for ORDER 72 (just one solution)

remind ilias of the meeting, ask if he has a previous RAC submission to send


PG72 running until it finds one solution
 - 8697 seconds, no matches found (one core for a's, one core for b's)
 ==> 2.4 hours

 20 parallel CPUs

 - 6 hours, (~50% done, candidates files are 1.3GB) no matches found


October 29
----------------
- after 6 hours of no solutions, jobs ran overnight
==> 668 total solutions after running overnight ~8 hours
==> 673 total solutions after running another ~6 hours

4.8GB file sizes for each candidates file

October 30
-----------
Can index the PSD's by line number in the file
separate PSD's and actual sequences into two different files (line numbers are the same)
give the PSD files the line numbers of the sequences

get an estimate of total runtime for the 72 6-uncompression candidate

benchmark the uncompression of the 72 3-uncompression code

keep in mind that in current code, the 3-uncompression count variable will be roughly the same across each process, while for 6-uncompressions the count is the count of their own search space segment.

72 3-uncompression code finished successfully in 90 seconds with a parallel factor of 40.

72 6-uncompression code is projected to finish in 7 days with a parallel factor of 20.

From testing, I've found that Order 50 will take over 65 CPU years with current code.
The problem is that the permutations of the base sequence are not being parallelized, and whereas this was negligible before,
I've calculated that it will take, on a single core, around 3 days to complete the permutation loop.
This implies that Order 50 with a parallel factor of 8000 will use 65 CPU years.

November 1
------------
legendre pairs of length 0 mod 5, length 87?
- 2000 3-uncompressions
- each uncompression was maybe a day
and periodic golay pairs of length 72

-mention that the post processing is trivial (with scripts), negligible compared to the time to produce the output

see how long the pg72 will take after a day of runtime

mention orderly generation for getting the uncompression time down

copy the funding available table

computational expertise, copy the table and add in combinatorial expertise
(we have computed complex golay, williamson sequences)

mention order 50 progress

select graham (or cedar, higher job limit)

perhaps suggest a higher job limit

mention the exact speedup time when using orderly generation to generate the compressed sequences

ask for 250 CPU years (justify why that specific number)


- figure out how to separate the search space evenly

50 {0, 10}

0 can be divided evenly

1000 processes ==>

every permutation of the first 10 elements in the alphabet of {1, -1} as our parallel process factors

November 3
---------------
72 6-uncompression still estimated to take around a week of real time with parallel factor of 20.

mention fftw in dependencies, apparently compute canada already has fftw.

linking my code not necessary, but I can.

mention GNU sort, any code that I haven't written myself in the code pipeline section

parallel approach -- splitting every uncompression into one individual job

track details about the 3-uncompresson for 90, number of sequences in the 

benchmark ilias's code with/without fftw to notice a speedup ()

-- potential speedup: store all calculations in the fftw_complex data type rather than converting each time, could be negligible speedup though

mention complex golay and williamson sequences in the management sections or others, cite that ilias and curtis co-authored them


November 6, 2023
------------------
Define the PSD in terms of DFT's

look at legendre pairs, how many sequences it took for them to find a solution, then scale that to our 250 CPU years

outline the method of search stronger

3-compressed pair, uncompress the a and b, and then match those results, describe how they are matched (psd's are equal), accomplished by 

in this proposal' we will focus on 3-compressions because the uncompression time is significantly better than if the compression factor were larger
(5-compression is about 330x larger for a typical sequence)

November 11, 2023
------------------------
Refactor: 
- Have golay.h contain all of the includes for the header files, that way only one include is necessary.
- have all of the header files use functions with templates so that arrays of variable length can be given (or even vectors and c arrays)
- compile main search function with the order embedded to maintain previous philosophy

November 12, 2023
------------------------------------
load balancing using the split search space approach is suboptimal when using orderly generation because 
the lower sections are going to finish significantly slower, as the later sections will be found to not be candidates significantly faster.

Interesting tidbit though, when I separate the search into thousands of threads, the splitting of the search space actually completes faster.
Probably because when a core is split into threads of different search spaces, I'd imagine that it indirectly makes the splitting of the search space irregular.

//a sequences, line 90: //30.8x10^12 permutations ==> 13 digits

A: line 95 is generating a lot of candidates

- talk about partitioning the search set for orderly generation
- talk about the FFTW results
- talk about the existence of integer partition algorithms
- talk about the course


November 13, 2023
----------------------

begin implementing compressions with older raw searches to compute 50 exhaustively.
good repo in the mathcheck repo: williamson sequences for compression examples.

Lingering problem: computing the equivalence class of the end pairs.


IDEA for compression: Get the alphabet somehow, generate all possible combinations of that alphabet into a length of n, use only those which have the correct rowsum.

FIXED DUMB PROBLEM WHERE DECIMATION WASNT PROPERLY COMPUTED BECAUSE #define LEN ORDER / COMPRESS CAUSES ORDER OF OPERATIONS TO BE BUGGY WHEN COMPUTING INDEXES

72 6-compression generation test found the candidate compression noted in the overleaf document.
-6 0 0 0 0 0 6 0 0 0 0 0  0 0 0 0 0 6 0 0 0 0 0 6 is the exact sequence

check_if_pair nukes very many pairs found in the candidate generation. In particular, the previously mentioned 72 6-compression candidate is nuked

^fixed, was cause to due LEN issue

generate the {-1, 1} partition of each element of the alphabet

November 19, 2023
------------------------
For meeting:
worked on uncompression code, doesnt seem to work (unknown if this is due to the compression generation or the uncompression generation).
Order 26 seems to not generate any a sequences when compressed by 2; this could be a clue as to why the entire pipeline doesnt seem to work correctly.

Interesting results on the 90 3-compression generation submitted a few days ago, the A sequences seem to be almost finished. It is at least 2/3 of the way complete, and
it can be safely stopped after the first digit changes to a -1, as every permutation on will trivially be a shift of some permutation starting with -3.

The B sequences are unknown, I couldn't manage to load the results file within vscode because it is so large; The progress is likely to be different, however.

ORDER 26 A-Candidate: -1 -1 -1 -1 1 1 -1 -1 1 1 1 -1 1        -1 1 -1 1 1 -1 1 1 -1 1 1 1 1 



2-compressed form: -2 0 -2 0 2 0 0 0 0 2 2 0 2

IDEA: Since when we search all permutations that start with a certain letter, we can finish the search (as every permutation onwards is trivially a shift of some compression we already found), can't we abuse this fact to make the search space only a sequence with the smallest letter count as the first index? This creates a much smaller search space.


Order 8: 0, 4

particular combination for rowsum 4:

permutations:

-2, 2, 2, 2

2, -2, 2, 2

2, 2, -2, 2

2, 2, 2, -2

As is shown, the sequences starting with -2 are significantly less than the ones starting with 2. As well, they are trivially a shift of each other.


-1 1 -1 1 -1 -1 -1 -1 1 -1 1 -1 1 -1 1 -1 

6 1, 10 -1's

November 20, 2023
------------------------
72 6-compression generation: 131 seconds

50-unique-filtered-0: 53.43MB, 1:02PM


November 25, 2023
------------------------


set all

size = set.size

set.insert base

set new = all


while(set.size != size)

iter = equivalence(new)

new = iter

all.insert iter

November 27, 2023
-----------------------
- New optimization
- Permission to enroll in computational math

- Generate sequences by prefix, use orderly generation on these prefixes; Should be a lot faster, can remove huge sections of a search space
- reducing pairs of circulatant matrices to graph
- construct hadamard matrix from pairs, reduce hadamard matrix to graph, run graph isomorphism on the new graph

- algebraic graph theory, GTM, incidence graph, cited in ovals paper

- run equivalence check on the list of 3-compressed sequences

- send email to margaret for permission to enroll, CC bright

December 1, 2023
--------------------

Filtering given list of 2000 90 3-compression pairs up to equivalence:

Equivalence with altnegative practically memory bombed my computer, one equivalence class used all 16gb of my ram, and it wasnt even enumerated fully.

took a look at the PG90 2022 paper, it seems they omit altnegative when they filter out equivalent compression pairs. Could they have found the same result?

Equivalence without altnegative is very quick. 115200 equivalent sequences in each set.

Not a big deal, because altnegative should rarely filter extra sequences (yet to be shown for compressions)

^^ this was wrong. Apparently, decimation is memory bombing my computer.

^^ fixed. was due to LEN decomposition again. Too many incorrect decimations were being generated.


-----
About 1m40s for a single equivalence class to be generated for a 90 3-compression pair.

lets say 2 minutes per equivalence class, then for a list of 2000 pairs that leaves an upper bound of (2000 * 2) / 60 = 66 hours to complete

without altnegative, a single equivalence class seems to take a few seconds. The equivalence class is 8 times smaller, maybe 16.

Upper bound of 2 hours to equivalence check the list of 2000 given pairs without altnegative.

December 7, 2023
----------------------
SIGNIFICANTLY improved equivalence check between pairs.

Logic: Rather than generating equivalence class of every single pair (time-consuming), generate the equivalence class of this pair:

{1 2 3 ... n}, {n + 1, n + 2, n + 3 ... n + n}

where the elements of each sequence are its indexes plus one (The second sequence is its index plus n + 1, as we need to differentiate between the first seqence).

Once we generate the equivalence classes of this pair, we can now generate any equivalence class of a pair by rearranging its indexes along with this sample pair's indexes. This is significantly faster in testing.

With this, we need only generate the equivalence class exhaustively once, (storing it in memory), rather than n times.

NEW RESULTS:

Order 32 - 834 (Likely incorrect, the 2022 paper had 838 classes listed. -- need to debug)
Time: 1717 seconds

Order 34 - 373 (correct)
Time: 814 seconds

The equivalence counts generated by each sequence seem to be wrong? Most of the time it is double the expected count. Should look into this.

Current estimate for Order 40:

One equivalence class (through the generators) takes ~3 seconds, there are 9301 equivalence classes so
9301 * 3 = 27903 seconds
27903 / 60 = 465 minutes
465 / 60 = 7.75 hours

Very doable!

December 8, 2023
-------------------------

Fixed bug with Order 32 incorrectly removing equivalence class solutions, I read the altnegative section wrong in the PGP 2022 paper, you are supposed to apply altnegative pair-wise, not sequence wise.

Now the generators construct half as many, so the total runtime of my equivalence filtering algorithm has been halved (Order 32 takes ~800 seconds now)

So for the new estimate of order 40 filter, 7.75 hours / 2 = 3.8 hours

Very doable.

Note: All of my computed equivalence class counts (up to Order 34) line up with the PGP2022 paper.

Considering that I tested with compression enabled, this implies that my compression pipeline is likely correct.

Order 26 search takes ~10 seconds, while the end equivalence filter takes ~40 seconds.

Ran equivalence filter on Order 40. Results do not line up with the PG2022 paper.
Mine: 9281 unique pairs, 14732 seconds
theirs: 9301 unique pairs

Likely losing solutions somewhere. Should test with the pairs file generated without compression to compare to these results that were generated with compression.

December 10, 2023
---------------------------
Ran equivalence filter on the order 40 results that were generated without compression.
Interesting tidbit: Towards the end of the list, the classes generated are pretty much unanimously of size 204800. The expected size is 819200.

The results were the same as on pairs generated with compressoin, 9281 unique pairs found.


pair => e1(pair) e2(pair)...

e1 union e2

{1, 2, 3, 4 ... n}  {n + 1, n + 2, ... n + n}


{1, 2, 3, 4} {5, 6, 7, 8}

{2, 3, 4, 1} {5, 6, 7, 8}

{-1, 1, 1, 1} {-1, 1, 1 ,1}

{1, 1, 1, -1} {-1, 1, 1, 1}

December 24, 2023 
-------------------------
Applied a few optimizations to partition/orderly methods. 

Orderly seems to outpace partition method when considering uncompressed sequences.

34 
partitions: ~267s
orderly: ~161s

Interestingly enough, the partition method seems to outpace the orderly method when considering compressed sequences.
This could be due to the overhead created when generating tail combinations?

40 2-compressed
partitions: ~20s
orderly: ~46s

Lex least/largest discrepancy still not investigated.

December 25, 2023
----------------------
New idea! For the orderly method, what if we constructed the sequences from the outside inward?
EX: 1 ??? 1 ==> 1 1 ? 1 1 ==> 1 1 1 1 1
The first and last indexes should be the most significant in terms of filtering power, so it makes more sense to generate them at the start (most sequences get filtered earlier)

January 1, 2024
--------------------
- Balonin email is "headache-inducing"

January 4, 2024
-----------------
Explored the use of compression-layering to speed up the compression search step, order 50 goes from 8 hours to 20 minutes.
order 40 goes from 380 seconds to 2 seconds

The difference in ratios of these two orders are likey due to the compression factors.
order 50 goes:
50 -> 25 -> 5
    2     5
order 40 goes:
40 -> 20 -> 10
    2    2

The 5-uncompression for order 50 is probably very expensive relative to its candidate generation

January 16, 2024
----------------
Original filter_equivalent method measuring up to around 12 hours with 32540 classes generated.
Equivalence class sizes are 7200 and num of pairs is 16000000.

New method takes around 2 minutes to get to the same number of classes.

Interesting tidbit:
Using fewer equivalences in our generators actually filters sequences faster. ex. We omitted reverse and swap, and the filter was extremely faster.
important note: the new equivalence class sizes were 120, 60x smaller.

Possible strategy: Filter in waves, e.g. filter with shifts ==> filter with shifts + decimation ==> filter with shifts + decimation + reverse, etc.

The fewer the sizes of our sets the easier it will be to filter quickly.








 






