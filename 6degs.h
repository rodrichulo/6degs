/* SixDegrees.h
 *
 *
 * This file holds the outline for populating a collabgraph with an input file 
 * This estalishes a graph and executes commands through an input stream
 * Commands include: 
 * DFS (Depth-first-Search)
 * BFS (Breadth-first-search)
 * Not (exclusion of artists, but still BFS)
 *
 *April 19th 2021
 */
 
 
 #ifndef __SIX_DEGREES__
 #define __SIX_DEGREES__
 
 #include <iostream> 
 #include <stack>
 #include <queue> 
 #include <string>
 #include <fstream>
 
 #include "Artist.h" 
 #include "CollabGraph.h"
 
 class SixDegrees {
 public:
     SixDegrees(std::string filename);
     ~SixDegrees();
     void play(std::istream &input, std::ostream &output);
     
 private:
     CollabGraph graph; 
     std::vector<Artist> artistList;
     void fillGraph(std::istream &artFile); 
     bool checkDFSBFS(const Artist &a, const Artist &b, std::ostream &output);
     void printBadArt(std::string name, std::ostream &output);
     void fillneighbors(std::vector<Artist> list);
     void prepBFS(std::istream &input, std::ostream &output);
     void prepDFS(std::istream &input, std::ostream &output);
     void prepNot(std::istream &input, std::ostream &output);
     bool checkNot(std::vector<Artist> check, std::ostream &output);
     bool bfs(const Artist &a, const Artist &b);
     void print(std::ostream &output, const Artist &a, const Artist &b);
     bool dfs(const Artist &a, const Artist &b);
     Artist artistLookup(std::string name);
     
     
 };
 
 #endif