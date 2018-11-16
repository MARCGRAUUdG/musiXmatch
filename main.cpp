#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <string>

using std::regex;
using std::string;
using std::sregex_token_iterator;

#include "Song.h"
#include "Songs.h"

typedef unsigned short ushort;

void llegirmXm(std::set<Song>& song_SET, Songs allSongs)
{
    bool readFrequent = false;
    regex re(",|%|:");
    string lletra;
    getline(std::cin, lletra);
    Song s;

    while (lletra != "")
    {
        std::string tid_mXm, tid_MSD, name_mXm, name_MSD, title_mXm, title_MSD;
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
        getline(std::cin, lletra);
    }
}

int main() {
    std::set<Song> song_SET;
    Songs allSongs;

    llegirmXm(song_SET, allSongs);

    return 0;
}