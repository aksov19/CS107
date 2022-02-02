using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";


string getNameFrom(char*& p);
film getMovieFrom(char*& p);

int cmpfnActor(const void* a, const void* b);
int cmpfnFilm(const void* a, const void* b);

/* Structure that holds information about a movie/actor and a corresponding file
   Used in cmpfnActor and cmofnFilm */
struct fileHolder{
    string name;
    int year;
    const void* file;
 };

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

// you should be implementing these two methods right here... 
bool imdb::getCredits(const string& player, vector<film>& films) const {
  if( player == "" ) return false;
  
  int actorNum = *(int*) actorFile;

  fileHolder holder;
  holder.name = player;
  holder.file = actorFile;

  int* offsetPtr = (int*)bsearch(&holder, (int*)(actorFile+sizeof(int)), actorNum, sizeof(int), cmpfnActor);
  if( offsetPtr == NULL ) return false;

  char* cur = (char*) (actorFile + *offsetPtr);
  string name = getNameFrom(cur);
  if( name.length() % 2 == 0 ) cur++;

  short movies = *cur;
  cur += sizeof(short);
  if( (name.length() + (name.length() % 2 == 0) + 3) % 4 != 0 ) cur += 2;

  for(int i = 0; i < movies; i++){
    int movieOffset = *(int*) (cur + sizeof(int) * i);
    char* movieCur = (char*) (movieFile + movieOffset);

    film f = getMovieFrom(movieCur);
    films.push_back(f);
  }

  return true; 
}

// Compare function for actors, used for the bsearch function
int cmpfnActor(const void* a, const void* b){
  string s1 = ((fileHolder*) a)->name;
  char* c = (char*)((fileHolder*) a)->file + *(int*)b;
  string s2 = getNameFrom(c);

  return s1.compare(s2);
}

// Gets an actor name from the given pointer, also moves the pointer to the end of the string
string getNameFrom(char*& p){
  string name = p;
  p += name.length() + 1;
  return name;
}

// Gets the name and year of a movie from the pointer, also moves the pointer to the end of the data
film getMovieFrom(char*& p){
  film ans;
  ans.title = getNameFrom(p);
  ans.year = 1900 + (int)p[0];
  p++;
  
  return ans;
}

bool imdb::getCast(const film& movie, vector<string>& players) const {
  if( movie.title == "" ) return false;

  int movieNum = *(int*) movieFile;

  fileHolder holder;
  holder.name = movie.title;
  holder.year = movie.year; 
  holder.file = movieFile;

  int* offsetPtr = (int*)bsearch(&holder, (int*)(movieFile+sizeof(int)), movieNum, sizeof(int), cmpfnFilm);
  if( offsetPtr == NULL ) return false;

  char* cur = (char*) (movieFile + *offsetPtr);
  film f = getMovieFrom(cur);
  if( f.title.length() % 2 == 1 ) cur++;

  short actorNum = (short)cur[0];
  cur += sizeof(short);

  if( (f.title.length() + (f.title.length() % 2) ) % 4 != 0 ) cur += 2;
  
  for(int i = 0; i < actorNum; i++){
    int actorOffset = *(int*) (cur + sizeof(int) * i);
    char* actorCur = (char*) (actorFile + actorOffset);

    string s = getNameFrom(actorCur);
    players.push_back(s);
  }

  return true;
}

// Compare function for films, used for the bsearch function
int cmpfnFilm(const void* a, const void* b){
  film f1;
  f1.title = ((fileHolder*) a)->name;
  f1.year = ((fileHolder*) a)->year;;

  char* c2 = (char*)((fileHolder*) a)->file + *(int*)b;
  film f2 = getMovieFrom(c2);

  if( f1 == f2 ) return 0;
  if( f1 < f2 ) return -1;
  return 1;
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}
