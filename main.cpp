#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <strings.h>

using namespace std;

class Tweet
{
private:
    string id;
    string name;
    string title;
    string country;
    string datetime;
    string unixtime;
public:
    Tweet(string id,
    string datetime,
    string unixtime,
    string name,
    string title,
    string country){
        this->id = id;
        this->name = name;
        this->title = title;
        this->country = country;
        this->datetime = datetime;
        this->unixtime = unixtime;
    }
    string getId(){return id;}
    string getName(){return name;}
    string getDatetime(){return datetime;}
    string getUnixtime(){return unixtime;}
    string getTitle(){return title;}
    string getCountry(){return country;}
};


int DeterministicPartition(vector<Tweet>& T, int low, int high){
    Tweet pivot = T[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if(T[j].getCountry() < pivot.getCountry()){
            i++;
            iter_swap(T.begin() + i, T.begin() + j);
        }
        else if (T[j].getCountry() == pivot.getCountry()
                  && strcasecmp(T[j].getName().c_str(), pivot.getName().c_str())  < 0 ){
            i++;
            iter_swap(T.begin() + i, T.begin() + j);
        }
        else if (T[j].getName() == pivot.getName()
                  && T[j].getUnixtime() < pivot.getUnixtime()  ){
            i++;
            iter_swap(T.begin() + i, T.begin() + j);
        }
    }
    iter_swap(T.begin() + i + 1, T.begin() + high);

    // return the partition point
    return i + 1;
}
int RandomizedPartition(vector<Tweet>& T, int low, int high){
    int pindex = rand() % (high-low+1) + low;
    Tweet pivot = T[pindex];
    iter_swap(T.begin() + high, T.begin() + pindex);

    return DeterministicPartition(T, low, high);
}
void quickSort(vector<Tweet>& T, int low, int high, bool isRandomized) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int index = isRandomized 
            ? RandomizedPartition(T, low, high) 
            : DeterministicPartition(T, low, high);

        // recursive call on the left of pivot
        quickSort(T, low, index - 1, isRandomized);

        // recursive call on the right of pivot
        quickSort(T, index + 1, high, isRandomized);
    }
}



int main(int argc, char* argv[]){
    srand (time(NULL));

    int N = stoi(argv[1]);
    string A = argv[2];
    string I = argv[3];
    string O = argv[4];

    vector<Tweet> Tweets;

    fstream file;
    string line,word,headers;
    
    int count = 0;
    file.open(I);
    if(file.is_open()){
        getline(file,headers);
        while(getline(file,line)){
            if(count == N)
                break;
            vector<string> tweetLine;
            istringstream ss(line);
            while (getline(ss,word,'\t'))
            {
                tweetLine.push_back(word);
                //istringstream ss(line);
            }
            Tweet t(tweetLine[0],tweetLine[1],tweetLine[2],tweetLine[3],tweetLine[4],tweetLine[5]);
            Tweets.push_back(t);
            count++;
        }
            
        
    }
    file.close();

    bool isRandomized = A == "randomized";

    clock_t time;
    time = clock();
    quickSort(Tweets, 0, N-1, isRandomized);
    time = clock() - time;
    cout << "Sorted in " <<  ((float)time)/CLOCKS_PER_SEC*1000 << " milliseconds by using " << A << " pivot selection." << endl;

    ofstream fout(O);

    fout << headers << endl;
    for(int i = 0; i < N; i++)
    {
        fout << Tweets[i].getId() << '\t' 
        << Tweets[i].getDatetime() << '\t' 
        << Tweets[i].getUnixtime() << '\t' 
        << Tweets[i].getName() << '\t' 
        << Tweets[i].getTitle() << '\t' 
        << Tweets[i].getCountry() << endl;
    }
    fout.close();
 
    return 0;
}