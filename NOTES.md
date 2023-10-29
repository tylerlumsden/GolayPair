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
