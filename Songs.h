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
     * @return Si s s'ha suprimit exitosament a la llista de paraules
     */
    bool deleteSong(const std::string id);

    /**@brief Afegeix la paraula amb l's indicat per paràmetre
     * @pre cert
     * @post s s'ha afegit a la última posició de la llista de paraules
     *
     * @param s String per afegir a la llista de paraules. Es correspón a una paraula
     */
    void addWord(const std::string s);

    /**@brief En cas d'existir la cançó amb l'id passat per paràmetre retorna un shared pointer a aquesta, en cas contrari retorna nullptr
     * @pre cert
     * @post Si hi ha una canço amb el id igual que el paràmetre retorna un shared pointer que apunta a aquesta cançó, altrament retorna nullptr
     *
     * @param id Id de la cançó que es vol obtenir
     * @return shared pointer en cas de que id es correspongui amb una id de la llista de cançons, nullptr altrament
     */
    std::shared_ptr<Song> getSong(const std::string id) const;

    /**@brief Donada una paraula entrada per paràmetre busca totes les cançons que contenen aquesta paraula i retornen en forma de pair el nom de l'artista i el títol de la cançó
     * @pre cert
     * @post retorna una llista de pairs <nom de l'artista, títol de la cançó> que contenen la paraula w entrada per paràmetre
     *
     * @param w Paraula per buscar si les cançons la contenen
     * @return Un set de pairs <nom de l'artista, títol de la cançó> que contenen la paraula entrada per paràmetre
     */
    std::set<std::pair<std::string, std::string>> songsWithWord(std::string w) const;

    /**@brief Retorna la paraula més freqüent de la cançó i en cas d'empat una llista de les més freqüents
     * @pre cert
     * @post si hi ha una cançó la cual el seu tid de mXm o bé de MSD es correspongui amb id, retorna una llista de la o en cas d'empat de les paraules més freqüents
     *
     * @param id id de la cançó que pot correspondre a l'MSD o a l'mXm
     * @return una o una llista de les paraules més freqüents de la cançó amb l aid passada per paràmetre
     */
    std::list<std::string> mostFrequentWordsIn(const std::string id) const;

    /**@brief Retorna les n paraules més freqüents d'aquesta cançó
     * @pre cert
     * @post Retorna les n paraules més freqüents d'aquesta cançó
     *
     * @param n Nombre de paraules que es desitja retornar d'una cançó
     * @return Les n paraules més freqïents d'aquesta cançó
     */
    std::set<std::string> mostFrequentN(ushort n) const;

private:

    std::map<std::string, std::shared_ptr<Song> > _song_mXm; ///map indexat per índex de mXm. per valor té un shared pointer a la cançó corresponent
    std::map<std::string, std::shared_ptr<Song> > _song_MSD; ///map indexat per índex de mXm. per valor té un shared pointer a la cançó corresponent
    std::vector<std::string> frequentWords; ///vector de posicions amb totes les paraules freqüents de les cançons

};


#endif //MUSIXMATCH_SONGS_H
