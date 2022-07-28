/*
 * Student Name = Ahmet Ramazan Çapoğlu
 * StudentID = 150190080
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <strings.h>

using namespace std;

struct Row{
    string strArr[6];
};
int partition(vector<Row>&, int, int, bool); //declaration partition()
void quickSort(vector<Row>&, int, int, bool); //declaration of quickSort()

int main(int argc,char* argv[]) {
    srand (time(NULL));

    int N = stoi(argv[1]);
    string A = argv[2];
    string I = argv[3];
    string O = argv[4];

    vector<Row> rows;

    //-----------Reading from a file-----------start----

    string columnNames;
    string myLine;
    fstream filePointer;

    filePointer.open(I);
    if(filePointer.is_open()) {
        getline(filePointer,columnNames);

        for(int rowN = 0; rowN < N; rowN++){
            getline(filePointer,myLine);

            istringstream ss(myLine);
            string LineString;

            string sstr[6];
            for(int colN = 0; colN < 6; colN++){
                getline(ss,LineString,'\t');
                sstr[colN] = LineString;
            }

            Row r;
            int six = 6;
            int iTh = 0;
            while(six > 0){
                r.strArr[iTh ] = sstr[iTh];
                six--;
                iTh++;
            }
            rows.push_back(r);

        }
    }
    //-----------Reading from a file-----------end----
    //****************************************************
    //----------Calculating time of Quicksort--------------start-----
    clock_t T;
    T = clock();
    if(A == "deterministic"){
        quickSort(rows, 0, N-1, false);
    }
    else if(A == "randomized") {
        quickSort(rows, 0, N-1, true);
    }
    T = clock() - T;
    cout << "Sorted in " <<  ((float)T)/CLOCKS_PER_SEC*1000 << " milliseconds by using " << A << " pivot selection." << endl;
    //----------Calculating time of Quicksort--------------end-----
    //****************************************************
    //------------Writing to a file---------------start----
    ofstream fileOut(O);
    fileOut << columnNames <<endl;

    for(int i = 0; i < N; i++)
    {
        fileOut << rows[i].strArr[0] << '\t' << rows[i].strArr[1] << '\t' << rows[i].strArr[2] << '\t' << rows[i].strArr[3] << '\t' << rows[i].strArr[4] << '\t' << rows[i].strArr[5] << endl;
    }
    //------------Writing to a file---------------end-----
    fileOut.close();
    filePointer.close();
    }

int partition(vector<Row>& A, int lowest, int highest, bool random){
    Row pivot;
    int i = (lowest - 1);
    if(random == false) {
        pivot = A[highest];

    }
    else if(random == true) {
        int pindex = rand() % (highest - lowest + 1) + lowest;
        Row pivot = A[pindex];
        iter_swap(A.begin() + highest, A.begin() + pindex); //swapping elements in vector
    }
    for (int j = lowest; j < highest; j++){
        if (A[j].strArr[5] < pivot.strArr[5]){  //comparison of country names
            i++;
            iter_swap(A.begin() + i, A.begin() + j);//swapping elements in vector
        }
        else if(A[j].strArr[5] == pivot.strArr[5]){
            if(strcasecmp(A[j].strArr[3].c_str(), pivot.strArr[3].c_str()) < 0){ //comparison of artist name
                i++;
                iter_swap(A.begin() + i, A.begin() + j); //swapping elements in vector
            }
            else if(A[j].strArr[3] == pivot.strArr[3]){
                if(stoi(A[j].strArr[2]) < stoi(pivot.strArr[2])){ //comparison of unix_time
                    i++;
                    iter_swap(A.begin() + i, A.begin() + j); //swapping elements in vector
                }
            }
        }
    }

    iter_swap(A.begin() + i + 1, A.begin() + highest); //swapping elements in vector

    return(i + 1);
}

void quickSort(vector<Row>& A, int lowest, int highest, bool random) {
    if (lowest< highest) {

        int p_index;

        if(random){
            p_index = partition(A, lowest, highest,true);
        }
        else{
            p_index = partition(A, lowest, highest,false);
        }

        quickSort(A, lowest, p_index - 1, random);
        quickSort(A, p_index + 1, highest, random);
    }
}