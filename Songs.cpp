//
// Created by Marc Grau on 26/10/2018.
//

#include "Songs.h"

std::shared_ptr<Song>
Songs::addSong(const std::string tid, const std::string MSD_artist_name, const std::string MSD_title,
               const std::string mXm_tid, const std::string mXm_artist_name, const std::string mXm_title) {
    return std::shared_ptr<Song>();
}

bool Songs::deleteSong(const std::string id) {
    return false;
}

void Songs::addWord(const std::string s) {

}

std::shared_ptr<Song> Songs::getSong(const std::string id) const {
    return std::shared_ptr<Song>();
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
