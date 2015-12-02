#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

double leaveOneOut(vector < vector<double> > data, vector<int> currentSet,int feature_add){
    double accuracy = (double)rand();
    double dist = 0;
    int correct = 0;
    double bestDist = 0;

    //loop through instances
    for(int i = 0; i < data.size()-1; i++){
        //loop through features
        for(int j = 1; j <= data[0].size(); j++){
            //make sure the features are not the same
            if(i != j){
                vector<int> weight(data.size());
                for(int i = 1; i <= data.size(); i++){
                    //cout << "hello" << endl;
                    if(find(currentSet.begin(), currentSet.end(), i) != currentSet.end())
                        weight[i-1] = 1;
                    else
                        weight[i-1] = 0;
                    cout << "weight vector: " << weight[i-1] << " ";
                }
                cout << endl;
                for(int k = 0; k < data.size()-1; k++){
                    double findD = (data[i][j] - data[k][j])*(data[i][j] - data[k][j]) * weight[j-1];

                    //cout << "this is the distance: " << findD << endl;
                    //dist = sqrt(findD);
                    cout << "This is distance at " << i << "th feature: " << dist << endl;
                }


                //dist = Euclid10(currentSet, test, comp);
                //dist = bestDist;
            }    
            /*if(dist < bestDist){

            }*/

        }
    }

    return accuracy;
}

bool intersect(vector<int> currentSet, int k){
    for(int i = 0 ; i < currentSet.size(); i ++){
        if(currentSet[i] == k)
            return true;
    }
    return false;
}

void featureSearch(vector< vector<double> > data){
    double accuracy;
    //create a current set
    vector<int> currentSet;
    //go through rows
    //cout << "hello" << endl;
    for(int i = 1; i <= data[0].size(); i++){
        cout << "On the " << i << "th level of the search tree." << endl;
        int feature_add = 0;
        double best_so_far = 0;
        //cout << "hello" << endl;
        //go through rows
        for(int j = 1; j <= data[0].size(); j++){
            if((intersect(currentSet, j) == false)){
                cout << "--Considering adding the " << j << "th feature." << endl;
                accuracy = leaveOneOut(data, currentSet, j);

                if(accuracy > best_so_far){
                    best_so_far = accuracy;
                    feature_add = j;
                }

            }
        }
        currentSet.push_back(feature_add);
        cout << "On level " << i << " I added feature " << feature_add << " to current set" << endl;
        //check to see if we have the right values in current set
        cout << "Current set: " << endl;
        for(int i =0; i < currentSet.size(); i ++)
            cout << currentSet[i] << endl;
    }
}

int main(){
    vector< vector <double> > data;
    double t;
    string dataLine;
    ifstream myfile("cs_170_small3TEST.txt");
    if(myfile.is_open()){
        while(!myfile.eof()){
            vector<double> temp;
            getline(myfile, dataLine);    
            istringstream ss(dataLine);
            while(ss >> t){
                temp.push_back(t);
            }
            data.push_back(temp);
        }
        myfile.close();
    }
    
    cout << "data.size " << data.size() << endl;
    cout << "data[0].size " << data[0].size() << endl;
    for(int i = 0; i < data.size() -1; i++){
        for(int j = 0; j< data[0].size(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Hello" << endl;
    featureSearch(data);

    return 0; 
}
