#include <iostream>
#include <vector>

using namespace std;

void leaveOneOut(vector < vector<int> > data);

void featureSearch(vector< vector<int> > data){
    for(int i = 1; i < 4; i++){
        cout << "On the " << i << "th level of the search tree." << endl;
        for(int j = 0; j < 4; j++){
            cout << "--Considering adding the " << j << "th feature." << endl;
        }
    }
}

int main(){
    vector< vector <int> > data;

    data.push_back(vector<int>(4,1));
    data.push_back(vector<int>(4,2));
    data.push_back(vector<int>(4,3));
    data.push_back(vector<int>(4,4));


    data[0][0] = 3;
    data[0][1] = 5;
    data[0][2] = 1;
    data[0][3] = 10;
    data[1][0] = 14;
    data[1][1] = 5;
    data[1][2] = 1;
    data[1][3] = 10;
    data[2][0] = 2;
    data[2][1] = 5;
    data[2][2] = 1;
    data[2][3] = 10;
    data[3][0] = 2;
    data[3][1] = 5;
    data[3][2] = 1;
    data[3][3] = 10;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j< 4; j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    featureSearch(data); 
}
