
#include <iostream>
#include <vector>

class Song;
class MusicSystem;
class IMusic;
class Albom;
class Visitor;


class Visitor
{
public:
	void visitAlbom(Albom* albom);
};

class IMusic
{
public:
	virtual void accept(Visitor v) = 0;
};

class Song
{
private:
	float time;
public:
	Song()
	{
		time = 0;
	}
	Song(float _time)
	{
		time = _time;
	}
	void SetTime(float _newTime)
	{
		time = _newTime;
	}
	float getTime() const
	{
		return time;
	}
};
class Albom : public IMusic
{
private:
	std::vector<Song> songs;
public:
	Albom()
	{
		songs.clear();
	}
	void AddSong(Song& song)
	{
		songs.push_back(song);
	}
	void deleteLast()
	{
		songs.pop_back();
	}
	void clear()
	{
		songs.clear();
	}
	std::vector<Song>& getSongs()
	{
		return songs;
	}
	void accept(Visitor v) override
	{
		v.visitAlbom(this);
	}
};
class MusicSystem
{
private:
	std::vector<Albom> alboms;
public:
	MusicSystem()
	{
		alboms.clear();
	}
	void addAlbom(Albom& albom)
	{
		alboms.push_back(albom);
	}
	void delLast()
	{
		alboms.pop_back();
	}
	void clear()
	{
		alboms.clear();
	}
	Albom* getAlbom(int indx)
	{
		if (indx < alboms.size())
		{
			return &alboms[indx];
		}
	}
	void accept(Visitor v, int indx)
	{
		getAlbom(indx)->accept(v);
	}
};

void Visitor::visitAlbom(Albom* albom)
{
	int quantity = 0;
	float totalTime = 0;
	for (int i = 0; i < albom->getSongs().size(); i++)
	{
		quantity++;
		totalTime += albom->getSongs()[i].getTime();
	}
	std::cout << "Songs quantity: " << quantity << "\nTotal time: " << totalTime << '\n';
}

int main()
{
	Visitor visitor;
	MusicSystem test;
	Albom albom;
	Song biber(1.50);
	Song notBibrt(1.70);
	Song Michael(1.80);
	albom.AddSong(biber);
	albom.AddSong(notBibrt);
	albom.AddSong(Michael);
	test.addAlbom(albom);
	test.accept(visitor, 0);
}
