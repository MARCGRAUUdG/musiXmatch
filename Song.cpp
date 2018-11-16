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



