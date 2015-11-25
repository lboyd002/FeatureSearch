#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

double Euclid10(vector<int> currentSet, vector<double> test, vector<double> comp){
    double distance = 0;
    vector<int> weight(10);
    for(int i = 1; i <= 10; i++){
        //cout << "hello" << endl;
        if(find(currentSet.begin(), currentSet.end(), i) != currentSet.end())
            weight[i-1] = 1;
        else
            weight[i-1] = 0;
       // cout << weight[i-1] << endl;
    }
    
    cout << test[1] << endl;
    //cout << "after filling in weight" << endl;
    double addition = 0;
    for(int i = 1; i < test.size(); i++){
        addition += (test[i] - comp[i])*(test[i] - comp[i]) * weight[i];
    }
    
    //cout << addition << endl;
    distance = sqrt(addition);
    
    return distance;
}

void Euclid40(){
    return;    
}

double leaveOneOut(vector < vector<double> > data, vector<int> currentSet,int feature_add){
    double accuracy = (double)rand();
    //int class = data[i][0];
    double dist = 0;
    int correct = 0;
    double bestDist = 0;
    vector<double> test;
    vector<double> comp;

    for(int i = 0; i < data.size(); i++){
        test = data[i];
        //cout << "test: " << test[i] << endl;
        for(int j = 0; j < data.size(); j++){
            comp =  data[j];
            //cout << comp[j] << endl;    
            if(i != j){
                //if(data.size() == 10)
                    //cout << "comp: " << comp[j] << endl;
                    dist = Euclid10(currentSet, test, comp);
                    //cout << "[" << i << ", " << j << "]" << endl;
                dist = bestDist;
            }    
            if(dist < bestDist){
                
            }
            
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
    for(int i = 1; i < data[0].size(); i++){
        cout << "On the " << i << "th level of the search tree." << endl;
        int feature_add = 0;
        double best_so_far = 0;
        
        //go through rows
        for(int j = 1; j < data[0].size(); j++){
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
    //for(int i =0; i < currentSet.size(); i ++)
    //    cout << currentSet[i] << endl;
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
    
    /*for(int i = 0; i < data.size(); i++){
        for(int j = 0; j< data[0].size(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */

    featureSearch(data);

   return 0; 
}
