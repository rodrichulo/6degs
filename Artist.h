/**
 ** Artist.h
 **
 ** 6degs
 **
 ** Purpose:
 **   Represent an artist (musician), storing their name and
 **   and discography. Accessor and mutator functions are provided,
 **   and two artists can be compared in several ways.
 **
 **/

#ifndef __ARTIST__
#define __ARTIST__

#include <iostream>
#include <string>
#include <vector>

class Artist {

public:

    /* Constructors */
    Artist();
    Artist(const std::string &);

    /* copy constructor/assignment */
    Artist(const Artist &);
    Artist &operator=(const Artist &);

    /* move constructor/assignment */
    Artist(Artist &&);
    Artist &operator=(Artist &&);

    /* Mutators */
    void add_song(const std::string &);
    void set_name(const std::string &);

    /* Accessors */
    std::string get_name() const;
    bool        in_song(const std::string &) const;
    std::string get_collaboration(const Artist &) const;
    
    
    /* friend functions */
    friend bool           operator == (const Artist &, const Artist &);
    friend bool           operator != (const Artist &, const Artist &);
    friend std::ostream & operator << (std::ostream &, const Artist &);

private:
    std::string name;
    std::vector<std::string> discography;
};

#endif /* __ARTIST__ */