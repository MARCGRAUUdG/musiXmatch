/** @file Song.h
 * @brief Classe Song: A song from the musiXmatch dataset
 */

#ifndef MUSIXMATCH_SONG_H
#define MUSIXMATCH_SONG_H

#include <iostream>
#include <set>
#include <list>
#include <cctype>
#include <map>

/** @class Song
 *  @brief Classe que enregistra les dades i lletra d'una cançó
 *  @author Marc Grau Genoher
 */

class Song { //A song from the musiXmatch dataset

    typedef unsigned short ushort;
public:
    /**@brief Constructor per defecte
     *
     */
    Song();

    /**@brief Constructor per paràmetres
     *
     * @param tid id de la Song corresponent al MSD
     * @param MSD_artist_name nom de l'autor de la Song corresponent al MSD
     * @param MSD_title títol de la Song corresponent al MSD
     * @param mXm_tid id de la Song corresponent al mXm
     * @param mXm_artist_name nom de l'autor de la Song corresponent al mXm
     * @param mXm_title títol de la Song corresponent al mXm
     */
    Song(const std::string tid,
            const std::string MSD_artist_name,
            const std::string MSD_title,
            const std::string mXm_tid,
            const std::string mXm_artist_name,
            const std::string mXm_title);

    /**@brief Mostra les dades complertes de la cançó per veure que aquestes són correctes
     * @pre cert
     * @post mostra per pantalla els atributs de la classe
     */
    void show();

    /**@brief Donat un índex de paraula i les vegades que aquest es repeteix a la cançó, els insereix a l'atribut corresponent de la classe
     * @pre No hi ha cap paraula amb índex idx a aquesta cançó
     * @post La parella <idx, cnt> s'han afegit al a la llista de paraules de la cançó
     *
     * @param idx Índex de la paraula per inserir
     * @param cnt Comptador de vegades que apareix la paraula a la cançó
     */
    void addWord( ushort idx, ushort cnt);

    /**@brief Mètode que retorna el nombre de vegades que ha aparegut la paraula desitjada
     * @pre cert
     * @post Diu quin és el cnt per l'índex idx
     *
     * @param idx Índex de la paraula per inserir
     * @return El nombre de vegades que apareix la paraula amb índex idx
     */
    ushort count(ushort idx) const;

    /**@brief Mètode que retorna una llista amb la paraula més freqüent de la canço, o en cas d'empat, les més freqüents
     * @pre cert
     * @post Retorna els índex de les paraules més freqüents
     *
     * @return L'índex, o en cas d'empat, els índex de les paraules més freqüents de la cançó
     */
    std::list<ushort> mostFrequentWordIdxs() const;

    /**@brief Mètode consultor que retorna el tid de l'MSD
     *
     * @return el tid de l'MSD
     */
    const std::string &getTid_MSD() const;

    /**@brief Mètode consultor que retorna el nom de l'autor de l'MSD
     *
     * @return el nom de l'autor de l'MSD
     */
    const std::string &getName_MSD() const;

    /**@brief Mètode consultor que retorna el títol de la cançó de l'MSD
     *
     * @return el títol de la cançó de l'MSD
     */
    const std::string &getTitle_MSD() const;

    /**@brief Mètode consultor que retorna el tid de l'mXm
     *
     * @return el tid de l'mXm
     */
    const std::string &getTid_mXm() const;

    /**@brief Mètode consultor que retorna el nom de l'autor de l'mXm
     *
     * @return el nom de l'autor de l'mXm
     */
    const std::string &getName_mXm() const;

    /**@brief Mètode consultor que retorna el títol de la cnaçó de l'mXm
     *
     * @return el títol de la cançó de l'mXm
     */
    const std::string &getTitle_mXm() const;

    /**@brief Mètde modificador que assigna el valor del paràmetre a l'atribut name_MSD
     *
     * @param name_MSD nom de l'autor de la Song corresponent al MSD
     */
    void setName_MSD(const std::string &name_MSD);

    /**@brief Mètde modificador que assigna el valor del paràmetre a l'atribut title_MSD
     *
     * @param title_MSD títol de la Song corresponent al MSD
     */
    void setTitle_MSD(const std::string &title_MSD);

    /**@brief Mètde modificador que assigna el valor del paràmetre a l'atribut name_mXm
     *
     * @param name_mXm nom de l'autor de la Song corresponent al mXm
     */
    void setName_mXm(const std::string &name_mXm);

    /**@brief Mètde modificador que assigna el valor del paràmetre a l'atribut title_mXm
     *
     * @param title_mXm títol de la Song corresponent al mXm
     */
    void setTitle_mXm(const std::string &title_mXm);

    const std::map<ushort, ushort> &getWords_MAP() const;

private:

    std::string tid_MSD; ///id de la Song corresponent al MSD
    std::string name_MSD; ///nom de l'autor de la Song corresponent al MSD
    std::string title_MSD; ///títol de la Song corresponent al MSD

    std::string tid_mXm; ///id de la Song corresponent al mXm
    std::string name_mXm; ///nom de l'autor de la Song corresponent al mXm
    std::string title_mXm; ///títol de la Song corresponent al mXm

    std::map<ushort, ushort> words_MAP; ///map on es guarda un índex i un comptador
};


#endif //MUSIXMATCH_SONG_H
