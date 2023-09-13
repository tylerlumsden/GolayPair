- https://archive.org/details/introductiontoko00limi_695
explains why probability is not the right concept to characterize the randomness of a sequence
first chapter

generate sequences from row sums
row sums = 2
    -->
    {- - - -}
    {- - - +}
    {- - + -}
    {- - + +}
    {- + - -}
    {- + - +}
    {- + + -}
    {- + + +} skip to here
    {+ - - -}
    {+ - - +}
    {+ - + -}
    {+ - + +} skip to here
    {+ + - -}
    {+ + - +} skip to here
    {+ + + -} skip to here
    {+ + + +}
    ...


every combination of three +'s
if all three plusses are in a row then place one plus backwards
eg. {- + + +}

-> {+ - + +}

{- - - - + + + -}
-->
{- - - + - + + -}

recursive approach 
--> take the largest degree +, find the next largest row sums - 1 of the sub array below that plus.


--++++++
-+-+++++
-++-++++
-+++-+++
-++++-++
-+++++-+
-++++++-
+--+++++
+-+-++++
+-++-+++
+-+++-++
+-++++-+
+-+++++-
++--++++
++-+-+++
++-++-++
++-+++-+
++-++++-
+++--+++
+++-+-++
+++-++-+
+++-+++-
++++--++
++++-+-+
++++-++-
+++++--+
+++++-+-
++++++--

--++++++
-+-+++++
-++-++++
-+++-+++
-++++-++
-+++++-+
-++++++-
+--+++++
+-+-++++
+-++-+++
+-+++-++
+-++++-+
+-+++++-
++--++++
++-+-+++
++-++-++
++-+++-+
++-++++-
+++--+++
+++-+-++
+++-++-+
+++-+++-
++++--++
++++-+-+
++++-++-
+++++--+
+++++-+-
++++++--





+-+++++-

++-++++-

++--++++ old algo
++-+-+++ new algo
