#include <iostream>
#include <string>
#include <map>
#include <vector>

class Song {
private:
	std::string name;
	std::string artist;
	int year;
	std::string genre;
public:
	Song();
	void SetSong(std::string n, std::string a, int y, std::string g);
	void setName(std::string n);
	void setArtist(std::string a);
	void setYear(int y);
	void setGenre(std::string g);
	std::string getName() const;
	std::string getArtist() const ;
	int getYear();
	std::string getGenre();
	Song(std::string n, std::string a, int y, std::string g);
	void input();
	bool operator<(Song other) const;
	bool operator>(Song other) const;
	friend std::ostream& operator<<(std::ostream& out, Song s);
};

class PlayList {
private:
	std::string name;
	int songCount;
	std::map<Song, int> songs;
public:
	PlayList();
	PlayList(std::string n, int c, std::map<Song, int>s);
	void input();
	void display();
	friend std::ostream& operator<<(std::ostream& out, PlayList pl);
	void addSongtoPlayList(Song s);
	bool removeSongfromPlayList(Song s);
	bool searchSong(std::string SongName);
    std::vector <Song> searchByArtist(std::string Artist);
};

PlayList::PlayList() {
	name = "";
	songCount = 0;
	songs = {};
}

PlayList::PlayList(std::string n, int c, std::map<Song, int>s) {
	name = n;
	songCount = c;
	songs = s;
}

void PlayList::input() {
	std::cout << "Enter name of PlayList:";
	std::getline(std::cin >> std::ws, name);
	std::cout << "Enter count of songs:";
	std::cin >> songCount;
	std::cout << "Enter song for the PlayList:" << std::endl;
	for (int i = 0;i < songCount;i++) {
		std::cout << i+1 << ".song:" << std::endl;
		Song s;
		s.input();
		songs.insert({ s,0 });
	}
}

std::ostream& operator<<(std::ostream& out, PlayList pl) {
	out << "Name of the PlayList:" << pl.name << std::endl;
	out << "Count of songs on the Play List:" << pl.songCount << std::endl;
	for (auto item : pl.songs) {
		out << "-------------------" << std::endl;
		out << "Song:";
		out << item.first.getName();
		out << "Count of listen:";
		out << item.second;
		out << std::endl;
	}
	return out;
}

void PlayList::addSongtoPlayList(Song s) {
	songs.insert({ s,0 });
	songCount++;
}

bool PlayList::removeSongfromPlayList(Song s) {
	if (songs.erase(s) == 0) {
		return false;
	}

	songCount--;
	return true;
}

bool PlayList::searchSong(std::string SongName) {
	for (auto item : songs) {
		if (item.first.getName() == SongName) {
			return true;
		}
	}
	return false;
}

std::vector <Song> PlayList::searchByArtist(std::string Artist) {
	std::vector<Song> result;
	for (auto item : songs) {
		if (item.first.getArtist() == Artist) {
			result.push_back(item.first);
		}
	}
	return result;
}

void PlayList::display() {
	std::cout <<"Name: " << name << std::endl;
	std::cout <<"Count of songs: " << songCount << std::endl;
	std::cout << "Songs:" << std::endl;
	for (auto item : songs) {
		std::cout << "Song Name:";
		std::cout<<item.first.getName();
		std::cout << std::endl;
		std::cout << "Count of listen:";
		std::cout<<item.second;
		std::cout << std::endl;
	}
}

Song::Song() {
	name = "";
	artist = "";
	year = 0;
	genre = "";
}

Song::Song(std::string n, std::string a, int y, std::string g) {
	name = n;
	artist = a;
	year = y;
	genre = g;
}


void Song::SetSong(std::string n, std::string a, int y, std::string g) {
	name = n;
	artist = a;
	year = y;
	genre = g;
}

void Song::setName(std::string n) {
	name = n;
}

void Song::setArtist(std::string a) {
	artist = a;
}

void Song::setYear(int y) {
	year = y;
}

void Song::setGenre(std::string g) {
	genre = g;
}

std::string Song::getName() const {
	return name;
}

std::string Song::getArtist()const {
	return artist;
}

int Song::getYear() {
	return year;
}

std::string Song::getGenre() {
	return genre;
}

void Song::input() {
	std::cout << "Enter name of Song:";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter artist:";
	std::getline(std::cin >> std::ws, artist);

	std::cout << "Enter year:";
	std::cin >> year;

	std::cout << "Enter genre:";
	std::getline(std::cin >> std::ws, genre);
}

bool Song::operator<(Song other) const {
	if (other.getYear() > year) return true;
	if (other.getYear() == year){
		return other.getName() > name;
	}
	return false;
}

bool Song::operator>(Song other) const {
	if (other.getYear() < year)return true;
	if (other.getYear() == year) {
		return other.getName() < name;
	}
	return false;
}
std::ostream& operator<<(std::ostream& out, Song s) {
	out << "Name:" << s.name << std::endl;
	out << "Artist:" << s.artist << std::endl;
	out << "Year:" << s.year << std::endl;
	out << "Genre:" << s.genre << std::endl;
	return out;
}

int main() {
	PlayList pl;

	pl.input();

	std::cout << "\n--- PLAYLIST ---" << std::endl;
	pl.display();

	Song s1("Believer", "Imagine Dragons", 2017, "Rock");
	pl.addSongtoPlayList(s1);

	std::cout << "\n--- AFTER ADDING SONG ---" << std::endl;
	pl.display();

	std::string songName;
	std::cout << "\nEnter song name to search: ";
	std::getline(std::cin >> std::ws, songName);

	if (pl.searchSong(songName)) {
		std::cout << "Song found!" << std::endl;
	}
	else {
		std::cout << "Song not found!" << std::endl;
	}

	std::string artistName;
	std::cout << "\nEnter artist name: ";
	std::getline(std::cin >> std::ws, artistName);

	std::vector<Song> result = pl.searchByArtist(artistName);

	if (result.empty()) {
		std::cout << "No songs found for this artist." << std::endl;
	}
	else {
		std::cout << "Songs by " << artistName << ":" << std::endl;

		for (auto song : result) {
			std::cout << song << std::endl;
		}
	}

	Song s2;
	std::cout << "\nEnter the song to remove:" << std::endl;
	s2.input();

	if (pl.removeSongfromPlayList(s2)) {
		std::cout << "Song removed successfully!" << std::endl;
	}
	else {
		std::cout << "Song not found in playlist!" << std::endl;
	}

	std::cout << "\n--- FINAL PLAYLIST ---" << std::endl;
	pl.display();

	return 0;
	
}