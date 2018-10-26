//
// Created by Marc Grau on 26/10/2018.
//

#ifndef MUSIXMATCH_SONGS_H
#define MUSIXMATCH_SONGS_H

#include <iostream>
#include <memory>
#include <set>

#include "Song.h"

class Songs {//A set of songs, indexed by the both tid and mXm_tid, and a list of words

    typedef unsigned short ushort;

    std::shared_ptr<Song> addSong(const std::string tid,
            const std::string MSD_artist_name,
            const std::string MSD_title,
            const std::string mXm_tid,
            const std::string mXm_artist_name,
            const std::string mXm_title);
    // Pre:  there is no song with this  tid  and  mXm_tid  in this set of songs
    // Post: the song has been added and a shared pointer to it is returned

    bool deleteSong(const std::string id);
    //Pre: --
    //Post: the song with (tid == id) or (mXm_tid == id) in this set has been deleted; says if it succeeded.

    void addWord(const std::string s);
    //Pre: --
    //Post: s has been added as the last word in the list of words.

    std::shared_ptr<Song> getSong(const std::string id) const;
    //Pre: --
    //Post: if there is a song (tid == id) or (mXm_tid == id) in this set then  returns a pointer to this song; otherwise it returns nullptr.

    std::set<std::pair<std::string, std::string>> songsWithWord(std::string w) const;
    //Pre: --
    //Post: returns the set of pairs <mXm_artist_name, mXm_title> of songs with word w.

    std::list<std::string> mostFrequentWordsIn(const std::string id) const;
    //Pre: --
    //Post: if there is a song (tid == id) or (mXm_tid == id) in this set then returns the list of its most frequent words; otherwise it returns an empty list

    std::set<std::string> mostFrequentN(ushort n) const;
    //Pre: --
    // Post: the song with (tid == id) or (mXm_tid == id) in this set has been deleted; says if it succeeded

private:

};


#endif //MUSIXMATCH_SONGS_H
