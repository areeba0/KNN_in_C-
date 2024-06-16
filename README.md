# K-Nearest Neighbors (KNN) Implementation in C++
K-Nearest Neighbors (KNN) is a supervised learning algorithm commonly used for classification and regression tasks. In this implementation, the algorithm is adapted to cluster a set of data points into predefined groups by iteratively refining group averages until convergence.

# Features
- Data Structures: Defines structures for storing points and groups.
- Distance Calculation: Computes the Euclidean distance between points.
- Nearest Group Assignment: Assigns data points to the nearest group.
- Iterative Convergence: Recalculates group averages and iterates until groups stabilize.
- Memory Management: Dynamically allocates and deallocates memory for group points.

# Explanation = 
## Structures:

- Point: Holds the x and y coordinates.
- Group: Contains the average point, the number of points, and a dynamically allocated array of points.
  
## Functions:
- distance: Calculates the Euclidean distance between two points.
- nearestGroup: Determines the closest group to a given point based on the distance to group averages.

## Main Algorithm:
1)Data points are assigned to the nearest group.
2)Averages for each group are recalculated based on the current membership.
3)Iteration continues until the average points of all groups converge (no significant change).
