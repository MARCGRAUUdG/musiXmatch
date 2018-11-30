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
    regex reMSD("<SEP>");
    std::string canco, tid, ign;
    std::getline(fs_MSD, tid, '<');
    std::shared_ptr<Song> s_it;

    std::cout << "Reading second file ... " << std::endl;

    while (tid != "")
    {
        if (tid[0] != '#')
        {
            s_it = as.getSong(tid);
            if (s_it != nullptr)
            {
                std::getline(fs_MSD, canco);
                sregex_token_iterator it(canco.begin(), canco.end(), reMSD, -1);
                sregex_token_iterator reg_end;

                s_it->setName_MSD(it->str().erase(0,4)); ++it;
                s_it->setTitle_MSD(it->str()); ++it;


                ++it; //Passem tid_mXm
                s_it->setName_mXm(it->str()); ++it;
                s_it->setTitle_mXm(it->str()); ++it;

                //s_it->show();

                s_it.reset();
            }
        }
        fs_MSD.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::getline(fs_MSD, tid, '<');
    }
    std::cout << "DONE!" << std::endl;
}

void llegirmXm(std::set<Song>& song_SET, Songs& allSongs, std::ifstream& fs_mXm)
{
    bool readFrequent = false;
    regex re(",|%|:");
    string lletra;
    getline(fs_mXm, lletra);
    std::string tid_MSD, tid_mXm;
    ushort idx, cnt;
    std::shared_ptr<Song> s;

    std::cout << "Reading first file ... " << std::endl;

    while (lletra != "")
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
    std::string id;
    std::cin >> id;
    std::cout << id << std::endl;
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
        std::cout << "Song not found" << std::endl;
    }
}

void where(Songs allSongs)
{
    std::string word;
    std::cin >> word;
    std::cin >> word;
    std::set <std::pair<std::string, std::string> > songsWith = allSongs.songsWithWord(word);
    if (songsWith.size() != 0)
    {
        std::cout << "Word [" << word << "] occurs in " << songsWith.size() << " songs: " <<  std::endl;
        for (auto &song : songsWith)
        {
            if (song.first != "" && song.second != "")
            {
                std::cout << song.first << " - " << song.second << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Word [" << word << "] not found in any song!" << std::endl;
    }
}

void most(Songs allSongs)
{
    std::string song;
    std::cin >> song;
    std::cin >> song;
    std::cin >> song;
    std::cin >> song;

    std::list<std::string> freqW = allSongs.mostFrequentWordsIn(song);
    std::cout << "The most frequent words in song [" << song << "] are: " << std::endl;
    for (auto &word : freqW)
    {
        std::cout << word << std::endl;
    }
}

void list(Songs allSongs)
{
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

    //std::getline(std::cin, trainName);
    std::ifstream fs_mXm("test.txt");
    //std::getline(std::cin, matchesName);
    std::ifstream fs_MSD("matches.txt");

    llegirmXm(song_SET, allSongs, fs_mXm);

    llegirMSD(allSongs, fs_MSD);

    demanarOpcions(allSongs);

    fs_mXm.close(); fs_MSD.close();

    return 0;
}