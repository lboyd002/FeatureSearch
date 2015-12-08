#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

void print( vector<int> set){
    for(int i =0; i < set.size(); i++){
        if(i+1 == set.size())
            cout << set[i] << "}";
        else
            cout << set[i] << ", ";
    }
}

double leaveOneOut(vector < vector<double> > data, vector<int> currentSet,int feature_add, int num){
    double accuracy;
    double correct = 0;

    //loop through instances
    for(int i = 0; i < data.size()-1; i++){
        double dist;
        double bestDist = INFINITY;
        int row1, row2;

        //loop through features
        for(int j = 0; j < data.size()-1; j++){

            //make sure we are not checking the same rows
            if(i != j){

                //create the weight vector from the features added
                vector<int> weight(data[0].size());

                for(int i = 1; i < data[0].size(); i++){
                    if(find(currentSet.begin(), currentSet.end(), i) != currentSet.end())
                        weight[i-1] = 1;
                    else
                        weight[i-1] = 0;
                }

                //find the distances using the feature we are adding from search funct
                dist = 0;

                //only add up the distances of the instances from the features in the current set
                for(int f = 1; f < data[0].size() ; f++){
                    dist = dist + (data[i][f] - data[j][f])*(data[i][f] - data[j][f])*weight[f-1];
                }

                //if backwards, subtract the feature to take away from the set
                if(num == 2){
                    dist = dist - (data[i][feature_add] - data[j][feature_add])*(data[i][feature_add] - data[j][feature_add]);
                }
                else{
                    //add the distance of the feature we are looking at to add
                    dist = dist + (data[i][feature_add] - data[j][feature_add])*(data[i][feature_add] - data[j][feature_add]);
                }

                dist = sqrt(dist);

                //check if this distance is the best so far
                if(dist < bestDist)
                    bestDist = dist;

                //if it is, then store the rows so we can check to see if the classes are the same 
                if(bestDist == dist){
                    row1 = i;
                    row2 = j;
                }
            }    
        }
        //if the classes are the same, increment the number of correct instances
        if(data[row1][0] == data[row2][0])
            correct++;
    }

    //calculate the accuracy
    accuracy = (correct / data.size()) * 100;

    return accuracy;
}

//checks we are going through the same feature
bool intersect(vector<int> currentSet, int k){
    for(int i = 0 ; i < currentSet.size(); i ++){
        if(currentSet[i] == k)
            return true;
    }
    return false;
}

//Searches through the tree
void featureSearch(vector< vector<double> > data, int num){

    cout << "Beginning search." << endl << endl;

    double accuracy;

    //create a current set
    vector<int> currentSet;
    //stores the set with the highest accuracy
    vector<int> highSet;
    double highAccuracy;

    //backwards elimination: put all the features into current set
    if(num == 2){
        for(int i = 1; i < data[0].size(); i++)
            currentSet.push_back(i);
    }

    //go through features
    for(int i = 1; i < data[0].size(); i++){
        //cout << "On the " << i << "th level of the search tree." << endl;
        int feature_add = 0;
        double best_so_far = 0;

        //go through features
        for(int j = 1; j < data[0].size(); j++){
            //check to make sure you are not going through the same feature
            if(((intersect(currentSet, j) == false) && num == 1) || ((intersect(currentSet,j == true) && num ==2))){
                //cout << "--Considering adding the " << j << "th feature." << endl;

                //accuracy = leaveOneOut(data, currentSet, j, num);
                cout << "\tUsing feature(s) {";

                if(currentSet.empty())
                    cout << j << "}";
                else
                    cout << j << ", "; 

                print(currentSet);
                

                accuracy = leaveOneOut(data, currentSet, j, num);

                
                cout << " accuracy is " << accuracy << "%" << endl;


                if(accuracy > best_so_far){
                    best_so_far = accuracy;
                    feature_add = j;
                }

            }
        }

        cout << endl;

        if(num != 2){
            currentSet.push_back(feature_add);
            //cout << "On level " << i << " I added feature " << feature_add << " to current set" << endl;

            //check to see if we have the right values in current set
            cout << "Feature set: {";
            print(currentSet);
            cout << " was best, accuracy is " << best_so_far << "%." << endl << endl;
        }
        else{
            currentSet.erase(currentSet.begin()+feature_add);
            //check to see if we have the right values in current set
            cout << "Feature set: {";
            print(currentSet);
            cout << " was best, accuracy is " << best_so_far << "%." << endl << endl;


        }

        if(best_so_far > highAccuracy){
            highAccuracy = best_so_far;
            highSet = currentSet;
        }
    }



    cout << "Search is finished!! The best feature subset is: {";

    print(highSet);

    cout << ", which has an accuracy of " << highAccuracy << "%." << endl;

}

int main(){
    vector< vector <double> > data;
    string file = "cs_170_small3.txt";
    int num;

    cout << "Welcome to Lauren Boyd's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";

    cout << file;
    cout << endl << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "\t1)  Forward Selection" << endl << "\t2)  Backward Elimination" << endl << "\t3)  Lauren's Special Algorithm" << endl << "\t\t\t";
    cin >> num;

    double t;
    string dataLine;
    ifstream myfile(file);
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
    else{
        cout << "Error opening file." << endl;
        return 1;
    }
    cout << "This dataset has " << data[0].size()-1 << " features(not including the class atribute), with " << data.size()-1 << " instances." << endl << endl;
    
    //print data matrix
    /*for(int i = 0; i < data.size()-1; i++){
      for(int j = 0; j< data[0].size(); j++){
      cout << data[i][j] << " ";
      }
      cout << endl;
      }
      cout << endl;
      */

    featureSearch(data,num);

    return 0; 
}
