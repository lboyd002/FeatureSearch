#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

double leaveOneOut(vector < vector<double> > data, vector<int> currentSet,int feature_add){
    double accuracy;
    double correct = 0;

    //loop through instances
    for(int i = 0; i < data.size()-1; i++){
        double dist;
        double bestDist = INFINITY;
        int row1, row2;

        //loop through features
        for(int j = 0; j < data.size()-1; j++){

            //make sure the features are not the same
            if(i != j){
                //cout << "weight vector: ";
                
                //create the weight vector from the features added
                /*vector<int> weight(data[0].size());

                for(int i = 1; i < data[0].size(); i++){
                    if(find(currentSet.begin(), currentSet.end(), i) != currentSet.end())
                        weight[i-1] = 1;
                    else
                        weight[i-1] = 0;
                    cout << weight[i-1] << " ";
                }
                cout << endl;
                */

                //find the distances
                dist = 0;
                for(int f = 0; f < currentSet.size(); f++){
                    dist = dist + (data[i][currentSet[f]] - data[j][currentSet[f]])*(data[i][currentSet[f]] - data[j][currentSet[f]]);
                }

                dist = dist + (data[i][feature_add] - data[j][feature_add])*(data[i][feature_add] - data[j][feature_add]);

                dist = sqrt(dist);

                //cout << "Here is the distance at row " << i << " and row " << j << " on feature " << feature_add << ": " << dist << endl;
                
                if(dist < bestDist)
                    bestDist = dist;
               
                //cout << "Here is the best distance so far: " << bestDist << endl;

                if(bestDist == dist){
                    row1 = i;
                    row2 = j;
                }
            }    
        }
        if(data[row1][0] == data[row2][0])
            correct++;
    }
    
    
    accuracy = (correct / data.size()) * 100;
    
    //cout << "Here is the accuracy: " << accuracy << endl;

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
    vector<int> highSet;
    
    //go through features
    for(int i = 1; i < data[0].size(); i++){
        cout << "On the " << i << "th level of the search tree." << endl;
        int feature_add = 0;
        double best_so_far = 0;
        
        //go through features
        for(int j = 1; j < data[0].size(); j++){
            //check to make sure you are not going through the same feature
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
        cout << "Feature set: {";
        for(int i =0; i < currentSet.size(); i++){
            if(i+1 == currentSet.size())
                cout << currentSet[i] << "}";
            else
                cout << currentSet[i] << ", ";
        }

        cout << " was best, accuracy is " << best_so_far << "%." << endl << endl;

        
        
    }

    /*cout << "Search is finished!! The best feature subset is: {";

    for(int i =0; i < highSet.size(); i++){
        if( i + 1 == highSet.size())
            cout << highSet[i] << "}" << endl;
        else
            cout << highSet[i] << ", ";
    }

    cout << ", which has an accuracy of " << highAcc << "%". << endl;
    */
}

int main(){
    vector< vector <double> > data;
    double t;
    string dataLine;
    ifstream myfile("cs_170_small3.txt");
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
    for(int i = 0; i < data.size()-1; i++){
        for(int j = 0; j< data[0].size(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    featureSearch(data);

    return 0; 
}
