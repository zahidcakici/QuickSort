#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include<bits/stdc++.h>
#include <time.h>


using namespace std;

class Data{
public:
    string* str;
};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partition(vector<Data>& A, int low, int high){
    Data pivot;
    // select the rightmost element as pivot
    pivot = A[high];
    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++){
        if (A[j].str[5] < pivot.str[5]){

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            //swap(&array[i], &array[j]);

            iter_swap(A.begin() + i, A.begin() + j);
        }
        else if(A[j].str[5] == pivot.str[5]){
            if(A[j].str[3] < pivot.str[3]){
                i++;
                iter_swap(A.begin() + i, A.begin() + j);
            }
            /*
            string s1 = A[j].str[3];
            string s2 = pivot.str[3];
            transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
            transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
             */
            else if(A[j].str[3] == pivot.str[3]){
                if(A[j].str[2] < pivot.str[2]){
                    i++;
                    iter_swap(A.begin() + i, A.begin() + j);
                }
            }
        }
    }

    // swap pivot with the greater element at i
    //swap(&array[i + 1], &array[high]);
    iter_swap(A.begin() + i + 1, A.begin() + high);

    // return the partition point
    return(i + 1);
}



int randomPivotPartition(vector<Data>& A, int low, int high){
    int pindex = rand() % (high-low+1) + low;
    Data pivot = A[pindex];
    iter_swap(A.begin() + high, A.begin() + pindex);

    return partition(A, low, high);
}

void quickSort(vector<Data>& A, int low, int high, bool random) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi;
        if(random == true){
            pi = randomPivotPartition(A, low, high);
        }
        else pi = partition(A, low, high);

        // recursive call on the left of pivot
        quickSort(A, low, pi - 1, random);

        // recursive call on the right of pivot
        quickSort(A, pi + 1, high, random);
    }
}
// function to print the array
void printArray(int array[], int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}


// Driver code
int main(/*int argc,char* argv[]*/) {
    srand (time(NULL));
    /*
    int N = stoi(argv[1]);
    string A = argv[2];
    string I = argv[3];
    string O = argv[4];
    */
    //*********************************
    vector<Data> datas;

    fstream myfile;
    string line;

    myfile.open("tweets_unsorted.csv");
    string id,datetime,unixtime,artistname,tracktitle,country;
    int count = 0;
    int count2 = 0;
    if(myfile.is_open()) {
        //myfile >> id >> datetime >> unixtime >> artistname >> tracktitle >> country;
        getline(myfile,line);
        while(getline(myfile,line)){
            if(count == 20000)
                break;
            istringstream ss(line);
            string substr;

            string* newdata = new string[6];
            int j = 0;
            while(getline(ss,substr,'\t')){
                newdata[j] = substr;
                //cout << substr << " ";
                j++;
            }
            Data temp;
            for(int i = 0; i<6; i++)
            {
                temp.str[i] = newdata[i];
            }

            datas.push_back(temp);
            //ss >> id >> datetime >> unixtime >> artistname >> <  >> country;

            count++;
        }
    }

    /*
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < 6; j++)
        {
            cout << datas[i].str[j] << ' ';
        }
        cout << endl;
    }
    */
    clock_t timer;
    timer = clock();
    //if(A == "deterministic") quickSort(datas, 0, N-1, false);
    quickSort(datas, 0, 49999, false);
    //else quickSort(datas, 0, N-1, true);
    timer = clock() - timer;
    cout << "Sorted in " <<  ((float)timer)/CLOCKS_PER_SEC*1000 << " milliseconds by using " << "deterministic" << " pivot selection." << endl;

    ofstream fout("10ktweet.csv");

    for(int i = 0; i < 50000; i++)
    {
        fout << datas[i].str[0] << '\t' << datas[i].str[1] << '\t' << datas[i].str[2] << '\t' << datas[i].str[3] << '\t' << datas[i].str[4] << '\t' << datas[i].str[5] << endl;
    }

    fout.close();
    myfile.close();

    /*
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < 6; j++)
        {
            cout << datas[i].str[j] << ' ';
        }
        cout << endl;
    }
     */

    }












