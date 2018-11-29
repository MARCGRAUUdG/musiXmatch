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

                s_it->show();

                s_it.reset();
            }
        }
        fs_MSD.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::getline(fs_MSD, tid, '<');
    }
}

void llegirmXm(std::set<Song>& song_SET, Songs& allSongs, std::ifstream& fs_mXm)
{
    bool readFrequent = false;
    regex re(",|%");
    string lletra;
    getline(fs_mXm, lletra);
    std::string tid_MSD, tid_mXm;
    ushort idx, cnt;
    std::shared_ptr<Song> s;

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
    std::cout << "He acabat de llegir el primer fitxer!" << std::endl;
}

int main() {
    std::set<Song> song_SET;
    Songs allSongs;
    std::string trainName, matchesName;

    //std::getline(std::cin, trainName);
    std::ifstream fs_mXm("train.txt");
    //std::getline(std::cin, matchesName);
    std::ifstream fs_MSD("matches.txt");

    llegirmXm(song_SET, allSongs, fs_mXm);

    llegirMSD(allSongs, fs_MSD);

    fs_mXm.close(); fs_MSD.close();

    return 0;
}