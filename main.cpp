//a
#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <string>
#include <fstream>

using std::regex;
using std::string;
using std::sregex_token_iterator;

#include "Song.h"
#include "Songs.h"

typedef unsigned short ushort;

std::string buscarMSD(Song& s, std::ifstream& fs_MSD)
{
    regex reMSD("<SEP>");
    std::string canco;
    getline(fs_MSD, canco);
    bool trobat = false;

    while (canco != "\n" || !trobat)
    {
        sregex_token_iterator it(canco.begin(), canco.end(), reMSD, -1);
        sregex_token_iterator reg_end;
        if (it->str().front() != '#')
        {
            if (it->str() == s.getTid_MSD())
            {
                ++it; //Passem tid_MSD
                std::cout << "name msd: " << it->str() << std::endl;
                s.setName_MSD(it->str()); ++it;
                std::cout << "title msd: " << it->str() << std::endl;
                s.setTitle_MSD(it->str()); ++it;


                ++it; //Passem tid_mXm
                std::cout << "name mxm: " << it->str() << std::endl;
                s.setName_mXm(it->str()); ++it;
                std::cout << "title mxm: " << it->str() << std::endl;
                s.setTitle_mXm(it->str());
                trobat = true;
            }
        }
        std::cout << canco << std::endl;
        std::getline(fs_MSD, canco);//std::cout << it->str() << std::endl;
    }
}

void llegirmXm(std::set<Song>& song_SET, Songs allSongs, std::ifstream& fs_mXm, std::ifstream& fs_MSD)
{
    bool readFrequent = false, emplenar_MSD = false;
    regex re(",|%|:");
    string lletra;
    getline(fs_mXm, lletra);
    Song s;

    while (lletra != "")
    {
        std::string tid_mXm, tid_MSD;
        ushort idx, cnt;
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
                emplenar_MSD = true;
                bool esIndex = true, llegirid = true;
                for (; it != reg_end; ++it) {
                    std::stringstream ss(it->str());
                    if (llegirid)
                    {
                        tid_MSD = it->str();
                        ++it;
                        tid_mXm = it->str();
                        s = Song(tid_MSD, "", "", tid_mXm, "", "");
                        llegirid = false;
                    }
                    else if (esIndex)
                    {
                        ss >> idx;
                        esIndex = false;
                    }
                    else
                    {
                        ss >> cnt;
                        s.addWord(idx,cnt);
                        esIndex = true;
                    }
                }
                s.show();
            }
        }
        if (emplenar_MSD == true)
        {
            buscarMSD(s, fs_MSD);
            s.show();
            emplenar_MSD = false;
        }
        getline(fs_mXm, lletra);
    }
}

int main() {
    std::set<Song> song_SET;
    Songs allSongs;
    std::ifstream fs_mXm("train.txt");
    std::ifstream fs_MSD("matches.txt");

    llegirmXm(song_SET, allSongs, fs_mXm, fs_MSD);

    fs_mXm.close(); fs_MSD.close();

    return 0;
}