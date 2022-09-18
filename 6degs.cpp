/* SixDegrees.cpp
 * This file implements the stacks and queues to populate the COLLABGRAPH
 * This file is also what interacts with main 
 * Includes the commands:
 * bfs
 * dfs 
 * not 
 * quit 
 */
 
 #include "Artist.h"
 #include "CollabGraph.h"
 #include "SixDegrees.h"
 using namespace std;


/*SixDegrees 
 *Arguments: string for the filename 
 *Returns: N/A 
 *Purpose: This constructor takes in a filename and initializes a graph, 
 *         after checking that the file is ok! 
 */
SixDegrees::SixDegrees(string filename)
{
    ifstream data(filename);
    
    //check to see if the input file fails or not
    if (data.fail()) {
        cerr << filename << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    
    //assuming reading in works, fill with data.
    fillGraph(data);
    // close the data file
    data.close();
}

/*~SixDegrees 
 *Arguments: none 
 *Returns: N/A
 *Purpose: Pretty
 */
SixDegrees::~SixDegrees() 
{
    
}


/*play
 *arguments: input stream and output stream 
 *returns: N/A 
 *Purpose: This function keeps the command loop going, constantly checking 
 *         if the command is quit or if the inputfile has ended 
 */
void SixDegrees::play(istream &input, ostream &output) 
{
    bool quit = false;
    string cmd;
    //take input until cannot use getline anymore...
    while ((quit == false) and (not getline(input,cmd).fail())) {
        if (cmd == "bfs") {
            prepBFS(input, output); //prepare for bfs
            
        } else if (cmd == "dfs") {
            prepDFS(input, output); //prepare for dfs
            
        } else if (cmd == "quit") { //we get to quit. Hooray!
            quit = true;
            
        } else if (cmd == "not") {
            prepNot(input, output); 
            
        } else { //invalid command 
            output << cmd << " is not a command. Please try again." << endl;
        }
    }
}

/*prepBFS
 *arguments: Input stream and output stream
 *Returns: none 
 *Purpose: This function gets more arguments to prepare to run bfs on the graph
*/
void SixDegrees::prepBFS(istream &input, ostream &output) 
{
    graph.clear_metadata();
    string source, dest;
    getline(input, source); //read in source
    getline(input, dest); //read in destination
    Artist a(source);
    Artist b(dest);
    
    //check to enforce valid vertex, print wrong artist if bad command
    if (checkDFSBFS(a, b, output)) {
        //Assume eeverything is in order, run bfs. Hooray!
        bfs(source, dest);
        print(output, source, dest); //will still check for empty path
    }
}


/*bfs
 *Arguments: Two artists: 
 *returns: boolean true or false if a path is possible.
 *Purpose: This function uses breadth-first search method to try and find the
 *         shortest path between artist a and artist b
 */
bool SixDegrees::bfs(const Artist &a, const Artist &b)
{
    if (a == b) return false; //if bfs is called on the same artist entry
    if (graph.is_marked(a)) return false; //possible fix to repeat artists
    queue<Artist> musix;
    musix.push(a);
    
    while (not musix.empty()) {
        Artist currArt = musix.front();
        musix.pop();
        graph.mark_vertex(currArt);
        vector<Artist> neighbors = graph.get_vertex_neighbors(currArt);
        
        //loop through all the neighbors for each vertex, marking predecessor
        for (size_t i = 0; i < neighbors.size(); i++) {
            Artist temp = neighbors.at(i);
            
            if (not graph.is_marked(temp)) {
                graph.set_predecessor(temp, currArt);
                musix.push(temp); //push neighbors onto the queue
                if (temp == b) return true;              
            }
        }
    }
    return false;
}

/*artistLookup
 *Arguments: an artist name 
 *Returns: an artist
 *Purpose: This function is used to find an Artist with type Artist, given a 
 *         string 
 */
Artist SixDegrees::artistLookup(string name)
{
    Artist a;
    for (size_t i = 0; i < artistList.size(); i++) {
        
        if (artistList.at(i).get_name() == name) {
            a = artistList.at(i); //get artist from vector of artists.
        } 
    }
    return a;
    
}

/*printBadArt
 *Arguments: Artist name(string) and output stream 
 *returns: void, prints to output stream 
 *Purpose: Remove clutter from bfs prep 
 */
void SixDegrees::printBadArt(string name, ostream &output)
{
    output << "\"" << name << "\" was not found in the dataset :(" << endl;
}

/*prepDFS
 *arguments: Input stream and output stream 
 *Returns: none 
 *Purpose: This function receives arguments necessary for DFS, and then runs
 *         the dfs function if all arguments are correct.
 */
void SixDegrees::prepDFS(istream &input, ostream &output) 
{
    graph.clear_metadata(); //clear the graph!
    string source, dest;
    getline(input, source); //get source
    getline(input, dest); //get destination
    Artist a(source);
    Artist b(dest);
    //find artist a and find artist b
    
    //check to enforce valid vertex and print out error messages if neeeded
    if (checkDFSBFS(a, b, output)) {
        dfs(a, b);
        print(output, a, b);
    }
}


/*dfs
 *arguments: artist source and artist destination 
 *Returns: bool value to indicate if path is possible 
 *Purpose: This functiton uses a recursive depth first search to find any 
 *         possible path between 2 artists. Uses recursion to keep the flow
 *         of a stack/Last In First Out
 */
bool SixDegrees::dfs(const Artist &a, const Artist &b) 
{
    graph.mark_vertex(a); //mark the vertex we are currently on.
    if (a == b) {
        return true; //recursive case once we find the desired artist
        
    } else { //keep looking
        //find all the neighbors of the current artist
        vector<Artist> neighbors = graph.get_vertex_neighbors(a);
        for (size_t i = 0; i < neighbors.size(); i ++) {
            Artist temp = neighbors.at(i); //set a temp artist
            if (not graph.is_marked(temp)) { 
                graph.set_predecessor(temp, a); //set predecessor 
                dfs(temp, b); //recurse with the neighbor! 
            }
        }
    }
    return false;
}

/*checkDFSBFS
 *arguments: 2 artists, a and b, output stream
 *Returns: boolean value 
 *Purpose: This functin checks if the artists are valid, and prints error
           messages to output stream if not.
 */
bool SixDegrees::checkDFSBFS(const Artist &a, const Artist &b, ostream &output)
{
    bool valid = true;
        
    if (not graph.is_vertex(a)) { 
        printBadArt(a.get_name(), output); //print bad name from getline
        valid = false;
    }
    if (not graph.is_vertex(b)) {
        printBadArt(b.get_name(), output);
        valid = false; //invalid artists make this false
    }
    
    return valid;
    
}

/*prepNot
 *Arguments: Input stream and output stream 
 *Returns: N/A
 *Purpose: This function takes as many artists from the input stream until 
 *         it finds "*" after at least 2 artists, to indicate exclusion from
 *         the search
 */
void SixDegrees::prepNot(istream &input, ostream &output) 
{
    graph.clear_metadata(); //clear the graph!
    string newArtist;    
    vector<Artist> exclusions;
    
    //keep checking for more input, add to a vector
    while (not getline(input, newArtist).fail() and (newArtist != "*")) {
            exclusions.push_back(Artist(newArtist)); //push to  vector
    }
    
    //check if the exclusions are valid
    if (checkNot(exclusions, output)) {
        //mark vertices for all the correct exclusions!
        for (size_t i = 2; i < exclusions.size(); i++) {
            graph.mark_vertex(exclusions.at(i));
        }
        bfs(exclusions.at(0), exclusions.at(1));
        print(output, exclusions.at(0), exclusions.at(1));     
    } 
}

/*checkNot
 *Arguments: A vector of artists
 *Returns: boolean value
 *Purpose: This function is swag and determines whether or not the vector
           Passed in is valid or not. If not valid, prints the error message.
*/
bool SixDegrees::checkNot(vector<Artist> check, ostream &output)
{
    bool legit = true;
    //check for valid vertices
    for (size_t i = 0; i < check.size(); i++) {
        if (not graph.is_vertex(check.at(i))) {
            printBadArt(check.at(i).get_name(),output);
            legit = false;
        }
    }
    if (legit == false) return false; //return early if the names are wrong
    //check for duplicates, not optimal, COULD BE FIXED!
    // for (size_t i = 2; i < check.size(); i++) {
    //     //check if any artists are the same as the first 2
    //     if (check.at(i) == check.at(0) or check.at(i) == check.at(1)) {
    //         legit = false;
    //     }
    // }
    // //Output error message if the vectors have dupliactes
    // if (legit == false) {
    //     output << "A path does not exist between \"" 
    //            << check.at(0).get_name() << "\" and \"" 
    //            << check.at(1).get_name() << "\"." << endl;
    // }
    // 
    return legit;
}

/*print
 *Arguments: Output stream, 2 Artists; source and destination
 *Returns: none, just prints to output.
 *Purpose: This function uses the report_path function in CollabGraph
 *         to print the correct output for whenever BFS/DFS/NOT is called.
 */
void SixDegrees::print(ostream &output, const Artist &a, const Artist &b)
{
    stack<Artist> path = graph.report_path(a,b); //get the path from a to b
    if (path.empty() or (a == b)) {
        output << "A path does not exist between \"" << a.get_name()
               << "\" and \"" << b.get_name() << "\"." << endl;
               return;
    }
    
    while (not path.empty()) {
        Artist temp = path.top();
        path.pop();
        if (not path.empty()) {
            Artist before = path.top();
            output <<  "\"" << temp.get_name() << "\" collaborated with \""
                   << before << "\" in \"" 
                   << graph.get_edge(temp,before) << "\"." << endl;
        }
    }
    output << "***" << endl;
}

/*fillGraph 
 *arguments: input stream for the artists and songs 
 *returns: N/A 
 *Purpose: This function is called from the constructor to insert edges and
 *         vertices for the graph.
 */
void SixDegrees::fillGraph(istream &artFile) 
{
    bool makeNew = true;
    string next;
    while (not getline(artFile,next).fail()) {
        if (next == "*") {//going to make new artist next 
            makeNew = true;
            
        } else if (makeNew == true) { //made new artist add to vector
            Artist tempArtist(next);
            artistList.push_back(tempArtist);  //push back to the vector 
            graph.insert_vertex(tempArtist); 
            makeNew = false; //set makeNew to false to prepare to read songs.
            
        //adding the songs for the artist baby! Woohoo!
        } else { 
            artistList.back().add_song(next);
        }    
    }
    
    //for loop to set each neighbor and set the edges.
    fillneighbors(artistList);
    
}


/*fillneighbors 
 *arguments: Vector of artists
 *Returns: none 
 *Purpose: This function finds the neighbors of each artists and marks the 
           edges on the graph as such
*/
void SixDegrees::fillneighbors(vector<Artist> list) 
{
    for (size_t i = 0; i < list.size(); i++) {
        Artist temp = list.at(i); //set artist to the current one.
        
        for (size_t i = 0; i < list.size(); i++) {
            Artist collaborating = list.at(i);
            //get collaboration between 2 artists
            string collab = temp.get_collaboration(collaborating);
            
            //check if artists are same or if no collab
            if ((temp != collaborating) and collab != "") {
                graph.insert_edge(temp, collaborating, collab); //insert edge
            }
        }
    }
}