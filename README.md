/********************************************************/
* README
* Rodrigo Campos
* Date: April 27th 2021
*********************************************************/

Compile/run:
     - Compile using
            make
     - run executable with
            ./6degs filename [inputFile] [outputFile] 

both inputFile and outputFile are optional, but a properly formatted file of
artists is necessary.

ACKNOWLEDGEMENETS: This section talks about the resources I used to build the
program. 

-Lab slides/handouts from Elizabeth Hom and Amanda Westlake
-Lecture videos about graphs
-Lecture slides
-Reference implementation
-Office hours to make code more modular
-Piazza posts

PROGRAM Purpose: This section talks about the uses of the program

This program allows users to find paths between artists using
the commands "bfs", "dfs", and "not". 

"bfs" finds the shortest possible path between 2 artists. To use this query,
it woud look like: (note the newlines)
bfs
artist1
artist2

"dfs" finds any possible path between 2 artists. To use this query, it would
look like:
dfs
artist1
artist2 


"not" finds a possible path between 2 artists excluding any artists the user
wants. The not query would look like: 
not
artist1
artist2 
[artist3]
[artist4] 
*

where artist 3 and artist 4 are artists that the user does not want to include
in the search. More exclusions can be made, but it always ends with "*".

DATA STRUCTURES: This section talks about how a graph is implemented.

The main data structure is a graph with edges and vertices. In this case, each
vertex is an artist, and the edges between 2 artists are the songs that they
collaborated with their neighbors. 

This program uses an unordered map, whose main use is to be helpful in
setting neighbors, edges, and vertices. 

The use of vectors is also implemented to make a list of neighbors for each
artist, as well as reading in all the artists it needs to. Vectors are used
for populating the graph as well as for the "not" function. 

Additionally, Breadth First Search relies on queues, allowing the FIFO order
to constantly check for the shortest path between 2 vertices. 

For the algorithms:
BFS: This function uses queues to find the shortest path between artists a
to b. This works because FIFO allows for the neighbors to be quickly marked and
removes elements from the queue. 

DFS: I think of this function as super greedy and constantly reaching for
paths. What I mean by that is that the stack's LIFO just keeps searching the
last neighbor's neighbors and keeps checking for a path. I implemented this
recursively and kept calling the function every time I found a neighbor
that was unmarked.

Not: This function was the hardest to implement for me. In simplicity, all it
does is mark the vertices of the artists the users DO NOT want to see, and
then run bfs, finding a path from a to b without any of the artists. However,
to copy the reference program, I had to do a lot of error checking to match
the order of the way things would execute. 

TL;DR: This program uses queues, stacks and vectors in the context of a graph 
to find paths between artists.

FILES SUBMITTED: This section talks about the files submitted
 
wrongArtists: this file was just used to see if the error message was printed
properly

smallArt.txt: This file contains a list of a few artists that I made up to 
check if my program's reading in functions were working properly. 

testingread.txt: This file contains the print statements I used to check if 
the edges were being added properly for each artist. 

6degs.h: This header file for 6degs uses mostly private functions to 
help build a fun game for the client. 

medArtists.txt: This file is slightly larger than smallArt.txt used 
primarily for testing. I'm proud of it.

getVertMed.txt: this file tested the get_vertex_neighbors function on 
medArtists.txt

testgetneighbors.txt: this file tests get_vertex_neighbors on smallArt.txt

testreadMed.txt: This file tests for reading in data, especially collabs 
between 2 artists. 

testRepPath.txt: This file is used for testing the report path function

6degs.cpp: This cpp file currently fill out the graph using the data 
passed on by the user and will have the main command loop that the user 
interacts with. 

Main.cpp: This cpp file has the main function that is used to run the program.
Checks for preliminary errors in usage of the command line arguments.

Collabgraph.cpp: This cpp file contains the implementation of the graph 
function

Collabgraph.h: This header file has the public function for the collabgraphs 
using artists to create a graph.

faultyInput.txt: This was just to see if my code was handling incorrect data
files incorrectly.

ariana.in: This does some testing with bfs with ariana grande used for diff
testing

ariana.txt: used to diff with gt(the demo version)

ariana.gt: used to keep as reference implementation.

easybfs.txt: I used this file to test when two of the same artists are the
source and destination for a bf

easybfs.gt: Reference file

test_easy.txt: Used to test when 1 artist is both source and dest of bfs

bfs1.in: This file tests the bfs function as well as a not edge case where the
file ends before seeing the "*".

bfs1.out: My output used to diff against the reference implementation

bfs1.gt: Reference implementation used for diffing

bfsNoFinish.in: This file just has bfs and one artist.

bfsNoFinish.out: My output file for bfsNoFinish.in 

bfsNoFinish.gt: Reference file for bfsNoFinish.in

notTest: This file tested the not function using edge cases such as having 2
duplicates in the list of excluded artists, not finishing the file, and
having artists that aren't in the dataset.

not.out: My output for notTest 

not.gt: Reference program output for notTest

dfs1: Used to test what would happen if only dfs was the command and file ended

dfs1.out: My output

dfs1.gt: True output, used for diff testing.

dfstest: This file was used to test edge cases on dfs. Tested wrong artists,
correct artists, with newline at the end, and with duplicate artists

dfstest.out: My output for dfstest

dfstest.gt: Reference implementation for dfstest

TESTING: This section talks about how I tested my code to where it is now.

PHASE 1:

Checking for usage of command line: To write my main function and check for 
errors, I referred to the reference implementation. The main focus was to see
what would happen if the user entered both an incorrect inputfile and datafile,
and the text that comes out with it. 

Fillgraph: To test the population of the graph, I mainly used print statements.
I created a file called smallArt.txt with very few artists so that I would know
which artists collaborated with others. testingread.txt has the basic output of
my testing output. testreadMed.txt does the same thing with a larger sample 
size.

To check if the vector of artists was working properly and had the correct
members, I created a cheeky testing function commented out in 6degs.cpp
to check that the artists were being added properly to the vector.

To test the logic of my fillgraph function, I created testingfiles
(smallArt.txt and medArtists.txt) and checked everytime 2 artists would
collab with each other, which would be right before an edge was inserted 
between the 2 artists. This way I know on what they're collabing, and check
with my handwritten solutions(which I can do on small test data)

get_vertex_neighbors: To test this function, I created a testing function in 
my fillgraph function. This function went through all the artists, and called
get_vertex_neighbors on each one of them to receive a vector of all the 
neighbors. I then printed out all the neighbors, using a small and medium 
database of artists(smallArt.txt and medArtists.txt) and made sure that each
vertex had the correct neighbors. 

report_path: I made a function where I created artists, inserted them as 
vertices and set their predecessors. For sake of simplicity, I labeled them
numbers just so I could see the proper path. I also checked an invalid vertex
and an artist who's predecessor was a nullptr to ensure it would print nothing.


PHASE 2: This section talks about testing for phase 2.

I first started testing all my functions using both print statements and
testing the program using cin and cout. 

BFS: To test this function I used cin and cout statements. At first I started
getting an endless loop printing out the neighbors, which turned out to simply
be because I wasn't marking the vertex! This was a quick fix and seemed to
work perfectly so I started testing with input files. I tested on 1 artist as
both source and destination, 2 artists that didn't exist, 1 artist that didn't
exist, and 2 artists with no path between them. This function didn't seem to
cause too many issues, so I believe there are no bugs left regarding this.

DFS: I approached this function recursively, so it took a little cin and cout
testing before I actually got an answer I wanted. To make sure the path was
different from BFS, I ran DFS on the reference implementation and then ran it
on my program to compare output and see if I matched it. Similar to BFS, once
I got 1 case working through cin and cout, I used input files to test:
-wrong Artists
-no path
-2 of the same artists
I used dfstest as well as cin and cout to test the output. I used input files
to test the behavior of the program after a file had ended.

NOT: I approached Not by marking all the exclusions and then running bfs on
the vector of artists I read in from the user. I did a lot of testing with the
reference implementation program to see the order of things would happen;
if the program would run if one of the excluded artists didn't exist, 
what the_6degs would do if the file ended before it found "*" in the not
command. I also tested to see with a duplicate artist, so if I put:
artist1
artist2
artist1
*
The program would output no path, so I had to implement that too. Originally,
I was checking for any duplicates, and wouldn't run bfs if any of the excluded
artists were duplicates. However, it shouldn't matter because marking the
vertex of excluded artists twice doesn't impact the path from artist1 and
artist2 (first 2 in the vector). I used notTest to catch this bug and test
my not function.

TIME SPENT: 20 h



