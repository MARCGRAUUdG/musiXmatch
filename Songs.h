/** @file Songs.h
 * @brief Classe Songs: A set of songs, indexed by the both tid and mXm_tid, and a list of words
 */

#ifndef MUSIXMATCH_SONGS_H
#define MUSIXMATCH_SONGS_H

#include <iostream>
#include <memory>
#include <set>
#include <map>
#include <vector>

#include "Song.h"

/**@class Songs
 * @brief Conjunbt de cançons indexat per el tid de mXm i el de MSD
 * @author Marc Grau Genoher
 */
class Songs {//A set of songs, indexed by the both tid and mXm_tid, and a list of words

public:

    typedef unsigned short ushort; ///equivalent a unsigned short

    /**@brief Mètode que afegeix una cançó i retorna un shared pointer a aquesta
     * @pre No hi ha cap cançó amb el mateix mXm_tid i MSD_tid a aquesta classe
     * @post La cançó s'ha afegit i s'ha retornat un shared pointer
     *
     * @param tid id de la Song corresponent al MSD
     * @param MSD_artist_name nom de l'autor de la Song corresponent al MSD
     * @param MSD_title títol de la Song corresponent al MSD
     * @param mXm_tid id de la Song corresponent al mXm
     * @param mXm_artist_name nom de l'autor de la Song corresponent al mXm
     * @param mXm_title títol de la Song corresponent al mXm
     * @return Un shared pointer a la Cançó
     */
    std::shared_ptr<Song> addSong(const std::string tid,
            const std::string MSD_artist_name,
            const std::string MSD_title,
            const std::string mXm_tid,
            const std::string mXm_artist_name,
            const std::string mXm_title);

    /**@brief Elimina la cançó amb l'id indicat per paràmetre
     * @pre cert
     * @post la Song amb el tid de l'MSD o de l'mXm a aquesta classe s'ha esborrat; diu si s'ha eliminat correctament
     *
     * @param id
     * @return
     */
    bool deleteSong(const std::string id);

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

    std::map<std::pair<std::string, std::string>, std::shared_ptr<Song> > _song;
    std::vector<std::string> frequentWords;

};


#endif //MUSIXMATCH_SONGS_H
