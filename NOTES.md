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




