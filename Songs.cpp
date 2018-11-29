//
// Created by Marc Grau on 26/10/2018.
//

#include "Songs.h"



std::shared_ptr<Song>
Songs::addSong(const std::string tid, const std::string MSD_artist_name, const std::string MSD_title,
               const std::string mXm_tid, const std::string mXm_artist_name, const std::string mXm_title) {

    std::shared_ptr<Song> pt (new Song(tid, MSD_artist_name, MSD_title, mXm_tid, mXm_artist_name, mXm_title));
    _song_MSD.insert( make_pair(tid, pt));
    _song_mXm.insert( make_pair(mXm_tid, pt));

    return pt;
}

bool Songs::deleteSong(const std::string id) {
    return false;
}

void Songs::addWord(const std::string s) {
    frequentWords.push_back(s);
}

std::shared_ptr<Song> Songs::getSong(const std::string id) const {
    std::shared_ptr<Song> s_pt;
    auto it = _song_MSD.find(id);

    if (it == _song_MSD.end())
    {
        it = _song_mXm.find(id);
        if (it == _song_mXm.end())
        {
            return nullptr;
        }
        else
        {
            s_pt = it->second;
            return s_pt;
        }
    }
    else
    {
        s_pt = it->second;
        return s_pt;
    }
}

std::set<std::pair<std::string, std::string>> Songs::songsWithWord(std::string w) const {
    return std::set<std::pair<std::string, std::string>>();
}

std::list<std::string> Songs::mostFrequentWordsIn(const std::string id) const {
    return std::list<std::string>();
}

std::set<std::string> Songs::mostFrequentN(Songs::ushort n) const {
    return std::set<std::string>();
}
