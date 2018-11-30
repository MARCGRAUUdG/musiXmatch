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
    auto it = _song_MSD.find(id);

    if (it == _song_MSD.end())
    {
        it = _song_mXm.find(id);
        if (it == _song_mXm.end())
        {
            return false;
        }
        else
        {
            std::string idAux;
            idAux = it->second->getTid_MSD();
            auto itAux = _song_MSD.find(idAux);
            _song_MSD.erase(itAux);
            _song_mXm.erase(it);
            return true;
        }
    }
    else
    {
        std::string idAux;
        idAux = it->second->getTid_mXm();
        auto itAux = _song_mXm.find(idAux);
        _song_mXm.erase(itAux);
        _song_MSD.erase(it);
        return true;
    }
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
    std::set<std::pair<std::string, std::string> > setSong;
    bool trobat;
    int i=1, index;
    while (i < frequentWords.size() && !trobat)
    {
        if (frequentWords[i] == w)
        {
            index = i;
            trobat = true;
        }
        i++;
    }

    for (auto &song : _song_MSD)
    {
        for (auto &word : song.second->getWords_MAP())
        {
            if (word.first == index)
            {
                setSong.insert(std::make_pair(song.second->getName_mXm(), song.second->getTitle_mXm()));
            }
        }
    }
    return setSong;
}

std::list<std::string> Songs::mostFrequentWordsIn(const std::string id) const {
    std::list<std::string> mfw;
    std::list<ushort> mfi;

    auto it = _song_MSD.find(id);

    if (it == _song_MSD.end())
    {
        it = _song_mXm.find(id);
        if (it != _song_mXm.end())
        {
            mfi = it->second->mostFrequentWordIdxs();
            for (auto & index : mfi)
            {
                mfw.push_back(frequentWords[index]);
            }
        }
    }
    else
    {
        mfi = it->second->mostFrequentWordIdxs();
        for (auto & index : mfi)
        {
            mfw.push_back(frequentWords[index]);
        }
    }
    return mfw;
}

std::set<std::string> Songs::mostFrequentN(Songs::ushort n) const {
    std::vector<int> cnTotal;
    std::set<std::string> result;
    cnTotal.resize(frequentWords.size());

    for (int i = 1; i <= frequentWords.size(); i++)
    {
        cnTotal[i] = 0;
    }

    for (auto &song : _song_MSD)
    {
        for (auto &word : song.second->getWords_MAP())
        {
            cnTotal[word.first] += word.second;
        }
    }

    int apuntades = 0;
    while (apuntades < n)
    {
        int cntMax = 0;
        for (auto &cnt : cnTotal)
        {
            if (cnt >= cntMax)
            {
                cntMax = cnt;
            }
        }
        for (int i = 1; i<=cnTotal.size(); i++)
        {
            if (cntMax == cnTotal[i])
            {
                result.insert(frequentWords[i]);
                cnTotal[i] = 0;
                apuntades++;
            }
        }
    }

    return result;
}
