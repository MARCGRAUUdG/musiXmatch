/** @file main.cpp
 * @brief Programa principal. Aquest llegeix els dos fitxers seqüencialment i guarda la informació de les
 * cançons a una estructura de dades. A partir d'aquí l'usuari entra vàries consultes i aquest mostrarà la
 * informació per pantalla fins que l'usuari entri un '*' com a acabament del programa.
 */

#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::regex;
using std::string;
using std::sregex_token_iterator;

#include "Songs.h"

typedef unsigned short ushort;

void llegirMSD(Songs& as, std::ifstream& fs_MSD)
{
    //Pre: cert
    //Post: Llegeix i actualitza les dades del segon fitxer
    regex reMSD("<SEP>");
    std::string canco, ign;
    std::getline(fs_MSD, canco);
    std::shared_ptr<Song> s_it;

    std::cout << "Reading second file ... " << std::endl;

    while (!fs_MSD.eof())
    {
        sregex_token_iterator it(canco.begin(), canco.end(), reMSD, -1);
        sregex_token_iterator reg_end;
        if (canco[0] != '#')
        {
            s_it = as.getSong(it->str());
            if (s_it != nullptr)
            {
                ++it;
                s_it->setName_MSD(it->str().erase(0,4)); ++it;
                s_it->setTitle_MSD(it->str()); ++it;


                ++it; //Passem tid_mXm
                s_it->setName_mXm(it->str()); ++it;
                s_it->setTitle_mXm(it->str()); ++it;

                //s_it->show();

                s_it.reset();
            }
        }
        std::getline(fs_MSD, canco);
    }
    std::cout << "DONE!" << std::endl;
}

void llegirmXm(std::set<Song>& song_SET, Songs& allSongs, std::ifstream& fs_mXm)
{
    //Pre: cert
    //Post: Llegeix i actualitza les dades del primer fitxer
    bool readFrequent = false;
    regex re(",|%|:");
    string lletra;
    getline(fs_mXm, lletra);
    std::string tid_MSD, tid_mXm;
    ushort idx, cnt;
    std::shared_ptr<Song> s;

    std::cout << "Reading first file ... " << std::endl;

    while (!fs_mXm.eof())
    {
        sregex_token_iterator it(lletra.begin(), lletra.end(), re, -1);
        sregex_token_iterator reg_end;

        if (it->str().front() != '#')
        {
            if (readFrequent == false)
            {
                for (; it != reg_end; ++it) {
                    allSongs.addWord(it->str());
                }
                readFrequent = true;
            }
            else
            {
                bool esIndex = true, llegirid = true;
                for (; it != reg_end; ++it) {
                    if (llegirid)
                    {
                        tid_MSD = it->str();
                        ++it;
                        tid_mXm = it->str();
                        s = allSongs.addSong(tid_MSD, "", "", tid_mXm, "", "");
                        llegirid = false;
                    }
                    else if (esIndex)
                    {
                        idx = atoi(it->str().c_str());
                        esIndex = false;
                    }
                    else
                    {
                        cnt = atoi(it->str().c_str());
                        s->addWord(idx,cnt);
                        esIndex = true;
                    }
                }
                //s->show();
            }
        }
        s.reset();
        getline(fs_mXm, lletra);
    }
    std::cout << "DONE!" << std::endl;
}

void get(Songs allSongs)
{
    //Pre: cert
    //Post: Donar t´ıtol i autor d’una can¸c´o (que aparegui al 1r fitxer) a partir de qualsevol dels seus
    //dos codis identificadors.
    std::string id;
    std::cin >> id;
    std::shared_ptr<Song> ps = allSongs.getSong(id);
    if (ps != nullptr)
    {
        ps->show();
    }
    else
    {
        std::cout << "[" << id << "] NOT FOUND" << std::endl;
    }
}

void del(Songs &allSongs)
{
    //Pre; cert
    //Post: Esborrar una can¸c´o a partir de qualsevol dels seus dos codis.
    bool esborrat;
    std::string id;
    std::cin >> id;
    esborrat = allSongs.deleteSong(id);
    if (esborrat)
    {
        std::cout << "[" << id << "] DELETED" << std::endl;
    }
    else
    {
        std::cout << "[" << id << "] NOT FOUND" << std::endl;
    }
}

void where(Songs allSongs)
{
    //Pre: cert
    //Post: Dir en quines can¸cons apareix una paraula determinada (de la llista de paraules del 1r
    //fitxer). Donar llista amb artista i can¸c´o, ordenada per ordre alfab`etic.
    std::string word;
    std::cin >> word;
    std::cin >> word;
    std::set <std::pair<std::string, std::string> > songsWith = allSongs.songsWithWord(word);
    if (songsWith.size() != 0)
    {
        std::cout << "Word [" << word << "] occurs in " << songsWith.size() << " songs: " <<  std::endl;
        for (auto &song : songsWith)
        {
            std::cout << song.first << " - " << song.second << std::endl;
        }
    }
    else
    {
        std::cout << "Word [" << word << "] not found in any song!" << std::endl;
    }
}

void most(Songs allSongs)
{
    //Pre: cert
    //Post: Dir quina ´es la paraula que apareix m´es vegades en una can¸c´o determinada (a partir de
    //qualsevol dels seus dos codis). En cas d’empat donar-les totes, en qualsevol ordre.
    std::string song;
    std::cin >> song;
    std::cin >> song;
    std::cin >> song;
    std::cin >> song;

    std::list<std::string> freqW = allSongs.mostFrequentWordsIn(song);
    if (freqW.size() != 0)
    {
        std::cout << "The most frequent words in song [" << song << "] are: " << std::endl;
        for (auto &word : freqW)
        {
            std::cout << word << std::endl;
        }
    }
    else
    {
        std::cout << "Ups! Song [" << song << "] NOT FOUND" << std::endl;
    }

}

void list(Songs allSongs)
{
    //Pre: cert
    //Post: Llistar les n paraules m´es freq¨uents en el conjunt de can¸cons, en ordre alfab`etic. Nota:
    //en cas d’empat llistar-les totes.
    int n;
    std::string str;
    std::cin >> str;
    std::cin >> str;
    std::cin >> n;

    std::set<std::string> freqW = allSongs.mostFrequentN(n);
    std::cout << "The " << n << " most frequent words are: " << std::endl;
    for (auto &word : freqW)
    {
        std::cout << word << std::endl;
    }
}

void demanarOpcions(Songs allSongs)
{
    //Pre: cert
    //Post: crida la opció desitjada; * per acabar
    std::string opcio;
    std::cout << "Entra opcions: " << std::endl;
    std::cin >> opcio;

    while (opcio != "*")
    {
        if (opcio == "GET") {get(allSongs);}
        else if (opcio == "DELETE") {del(allSongs);}
        else if (opcio == "WHERE") {where(allSongs);}
        else if (opcio == "MOST") {most(allSongs);}
        else if (opcio == "LIST") {list(allSongs);}
        std::cout << std::endl;
        std::cin >> opcio;
    }
}

int main() {
    std::set<Song> song_SET;
    Songs allSongs;
    std::string trainName, matchesName;

    std::getline(std::cin, trainName);
    std::ifstream fs_mXm(trainName);
    std::getline(std::cin, matchesName);
    std::ifstream fs_MSD(matchesName);

    llegirmXm(song_SET, allSongs, fs_mXm);

    llegirMSD(allSongs, fs_MSD);

    demanarOpcions(allSongs);

    fs_mXm.close(); fs_MSD.close();

    return 0;
}