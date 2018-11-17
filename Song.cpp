//
// Created by Marc Grau on 26/10/2018.
//

#include <algorithm>
#include "Song.h"

Song::Song() {
    tid_MSD = "";
    name_MSD = "";
    title_MSD = "";

    tid_mXm = "";
    name_mXm = "";
    title_mXm = "";
}

Song::Song(const std::string tid, const std::string MSD_artist_name, const std::string MSD_title,
           const std::string mXm_tid, const std::string mXm_artist_name, const std::string mXm_title) {
    tid_MSD = tid;
    name_MSD = MSD_artist_name;
    title_MSD = MSD_title;

    tid_mXm = mXm_tid;
    name_mXm = mXm_artist_name;
    title_mXm = mXm_title;
}

void Song::addWord(Song::ushort idx, Song::ushort cnt) {
    words_MAP.insert(std::pair<ushort, ushort> (idx, cnt));
    std::cout << "Sha inserit a la pos " << idx << " el valor " << cnt << std::endl;
    std::cout << "Llista: " << std::endl;
    for (auto& word : words_MAP)
    {
        std::cout << "(" << word.first << "-" << word.second << ") ";
    }
    std::cout << std::endl;
}

Song::ushort Song::count(Song::ushort idx) const {
    int count = 0;
    if (words_MAP.find(idx) != words_MAP.end())
    {
        count = words_MAP.at(idx);
    }
    return count;
}

std::list<Song::ushort> Song::mostFrequentWordIdxs() const {
    std::list<ushort> indices;
    int cntMax = 0;
    for (auto& word2 : words_MAP)
    {
        if (word2.second >= cntMax)
        {
            cntMax = word2.second;
        }
    }
    for (auto& word3 : words_MAP)
    {
        if (word3.second == cntMax)
        {
            indices.push_back(word3.first);
            }
    }
    return indices;
}

void Song::show() {
    std::cout << "tid_mXm: " << tid_mXm << std::endl;
    std::cout << "name_mXm: " << name_mXm << std::endl;
    std::cout << "title_mXm: " << title_mXm << std::endl;

    std::cout << "tid_MSD: " << tid_MSD << std::endl;
    std::cout << "name_MSD: " << name_MSD << std::endl;
    std::cout << "title_MSD: " << title_MSD << std::endl;
    std::cout << "Llista: " << std::endl;
    for (auto& word : words_MAP)
    {
        std::cout << "(" << word.first << "-" << word.second << ") ";
    }
}

const std::string &Song::getTid_MSD() const {
    return tid_MSD;
}

const std::string &Song::getName_MSD() const {
    return name_MSD;
}

const std::string &Song::getTitle_MSD() const {
    return title_MSD;
}

const std::string &Song::getTid_mXm() const {
    return tid_mXm;
}

const std::string &Song::getName_mXm() const {
    return name_mXm;
}

const std::string &Song::getTitle_mXm() const {
    return title_mXm;
}

void Song::setName_MSD(const std::string &name_MSD) {
    Song::name_MSD = name_MSD;
}

void Song::setTitle_MSD(const std::string &title_MSD) {
    Song::title_MSD = title_MSD;
}

void Song::setName_mXm(const std::string &name_mXm) {
    Song::name_mXm = name_mXm;
}

void Song::setTitle_mXm(const std::string &title_mXm) {
    Song::title_mXm = title_mXm;
}



