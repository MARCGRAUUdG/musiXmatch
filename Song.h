//
// Created by Marc Grau on 26/10/2018.
//

#ifndef MUSIXMATCH_SONG_H
#define MUSIXMATCH_SONG_H

#include <iostream>
#include <set>
#include <list>
#include <cctype>
#include <map>

class Song { //A song from the musiXmatch dataset

    typedef unsigned short ushort;
public:
    Song();
    Song(const std::string tid,
            const std::string MSD_artist_name,
            const std::string MSD_title,
            const std::string mXm_tid,
            const std::string mXm_artist_name,
            const std::string mXm_title);

    void show();
    //Pre: --
    //Post: print the attributes of the class.

    void addWord( ushort idx, ushort cnt);
    //Pre: There is no word with index idx in this song.
    //Post: The pair <idx,cnt> has been added to the set of words of this song.

    ushort count(ushort idx) const;
    //Pre: --
    //Post: Says which is the count for index idx.

    std::list<ushort> mostFrequentWordIdxs() const;
    //Pre: --
    //Post: Returns the indices of the most frequent words in this song.

private:

    std::string tid_MSD; ///id de la Song corresponent al MSD
    std::string name_MSD; ///nom de la Song corresponent al MSD
    std::string title_MSD; ///títol de la Song corresponent al MSD

    std::string tid_mXm; ///id de la Song corresponent al mXm
    std::string name_mXm; ///nom de la Song corresponent al mXm
    std::string title_mXm; /// títol de la Song corresponent al mXm

    std::map<ushort, ushort> words_MAP; ///map on es guarda un índex i un comptador
};


#endif //MUSIXMATCH_SONG_H
