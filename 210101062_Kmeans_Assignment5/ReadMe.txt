-------------------------------------- CS566 ASSIGNMENT 5------------------------------------------------
NAME: Lakshya Onkara
ROLL NO.: 210101062

AIM: Vector quantization using K-means algorithm
EXECUTION: Build and run the code on Visual Studio 2010. Use F5 key to run the code.

INPUT: Universe.csv
OUTPUT: A codebook of distinct analysis vectors.

CONSTANTS:
1. DELTA: Used to terminate the K-means algorithm (0.0001)
2. P: The number of past samples to consider (12)
3. k: Size of the codebook (8)
4. tokhuraWeights: Array to store the 12 Tokhura weight values.
5. M: Size of the universe.

VARIABLES:
1. universe: Vector of vectors to store input values.
2. codebook: Vector of vectors to store the code vectors.
3. clusters: Vector of vectors to store the assignment of vectors to regions.

FUNCTIONS:
1. printCodebook():
	Function to print the code vectors.

2. readUniverse():
	Function to read the input .csv file and store the input in universe vector.

3. tokhuraDistance():
	Function to calculate the Tokhura distance between the current centroid and current row of universe.

4. nearestNeighbors(): 
	Function to assign vectors of the universe to a cluster on the basis of minimum tokhura distance.

5. totalDistortion():
	Function to calculate the average total distortion.

6. updateCodeVector():
	Function to update the code vectors to minimise distortion.

7. kMeans():
	Function to implement Lloyd's algorithm for vector quantization.


PROCEDURE:
1. Set m = 0 and initialize the codebook with random vectors from the universe. The codebook will now contain k vectors, each consisting of 12 values.
2. For each vector in the universe, assign it to a region based on the nearest neighbor rule.
3. Calculate the total distortion (dist) for all regions. Compute the average distortion, avg_dist = dist / M. (Use Tokhura distance for this step.)
4. Compute the centroid for each region and update it accordingly.
5. Set m = m + 1
6. Repeat steps 2, 3, and 4 until abs(distortion - dist) > delta, where distortion is from the previous iteration and dist is the current distortion. (You can choose delta as either 0.0001 or 0.00001.).