// 210101062_Kmeans_Assignment5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"       
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

#define P 12
#define DELTA 0.0001

vector<vector<long double>> universe;	//variables to hold the universe values and centroids
vector<vector<long double>> codebook;
vector<vector<int>> clusters;			//to keep track of vectors in each region
string inputFile = "Universe.csv";
int k = 8;		//codebook size
double tokhuraWeights[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};			//tokhura's distance
int M = 0;		//size of the universe
int m = 0;		//iteration

//function to print the code vectors
void printCodebook(){
	if(codebook.size() == 0){
		return;
    }
	cout<<"----------------------------------------------------------------------------------------------------------------------------------------------\n";
	for (int i=0; i<8; i++) {
        for (int j=0; j<P; j++) {
            printf("%10.7lf  ", codebook[i][j]);
        }
        cout << endl;
    }
}

//function to calculate the Tokhura distance between the current centroid and current row of universe
long double tokhuraDistance(vector<long double> &currentCentroid, vector<long double> &currentVector){
	long double ans = 0;
	for(int i=0; i<P; i++){
		long double d = currentVector[i]-currentCentroid[i];
		ans += (tokhuraWeights[i] * d * d);			//using tokhura distance
	}
	return ans;
}

//function to assign vectors of universe to a cluster using tokhura distance
void nearestNeighbors(){	
    for(int i=0; i<M; i++){
		int index = 0;
		vector<long double> currentVector = universe[i];   
		long double minDistance = LDBL_MAX;
		for(int j=0; j<k; j++){
			vector<long double> currentCentroid = codebook[j];
            long double distance = tokhuraDistance(currentCentroid, currentVector);		//distance between current cluster and current row of universe
            if(distance < minDistance){       
				minDistance = distance;
				index = j;
			}
		}
		clusters[index].push_back(i);		//add the index of the current vector to the cluster
	}
}

//function to calculate the average total distortion
long double totalDistortion(){
    long double totalDist = 0;
	for(int i=0; i<k; i++){
		int size = clusters[i].size();
		for(int j=0; j<size; j++){		//all the vectors of a particular cluster
			int index = clusters[i][j];
			totalDist += tokhuraDistance(codebook[i], universe[index]);
		}
	}
	long double avg = totalDist/M;		//taking average of total distortion
	return avg;
}

//function to update the code vectors
void updateCodeVector(){
	for(int i=0; i<k; i++){
		vector<long double> temp(P, 0.0);		//temporary vector to sum up all the cluster vector values
		int size = clusters[i].size();
		for(int j=0; j<size; j++){
			int index = clusters[i][j];		//take index of the universe vector
			for(int k=0; k<P; k++){
				temp[k] += universe[index][k];		//add all the values of universe
			}
		}
		for(int j=0; j<P; j++){
			codebook[i][j] = temp[j]/((long double)size);		//take average for finding centroid
		}
	}
}

//Lloyds algorithm to perform vector quantization
void kMeans(){
	long double dist = totalDistortion();
	long double distortion = 0;  //storing old distortion
    printf("Distortion in iteration %2d: %.7lf\n\n", m, dist);

	while(abs(distortion - dist) > DELTA){		//until abs(current_dist - old_dist) becomes less than delta
		updateCodeVector();
		printCodebook();
		
		clusters.clear();		//clear the current clusters
		clusters.resize(k);
		nearestNeighbors();		//assign clusters for the next rounds

		distortion = dist;
		dist = totalDistortion();
		m++;
		printf("Distortion in iteration %2d: %.7lf\n\n", m, dist);
	}
}

int main()
{
	clusters.clear();
	clusters.resize(k); 

	fstream fin;
	fin.open(inputFile);    
	if(!fin){			//file does not exist
		fin.close();
		printf("Failed to open file\n");
		return 1;
	}
	long double word;
	char delim;
	while(fin >> word){			//until input is available
		vector<long double> line;
		line.push_back(word);
		for(int i=1; i<P; i++){
			fin>>delim>>word;
			line.push_back(word);	//save whole row
		}
		universe.push_back(line);	//add row to universe vector
	}
	fin.close();
	M = universe.size();

	if(M == 0) return 1;

    srand(static_cast<unsigned>(time(0)));	//seed random number generator
    vector<int> selected_indices;			//to keep track of selected indices to avoid duplicates
    while (codebook.size() < 8) {
        int random_index = rand() % M; //random index between 0 and universe.size() - 1
        if (find(selected_indices.begin(), selected_indices.end(), random_index) == selected_indices.end()) {	//check if the index is already selected
            codebook.push_back(universe[random_index]); // Add the vector to codebook
            selected_indices.push_back(random_index);   // Mark the index as selected
        }
    }

    printCodebook();
	nearestNeighbors();
	kMeans();
	return 0;
}

