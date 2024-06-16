
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
// in this question we calculate knn (ml model)
//This code defines two structures, one for points and one for groups, and two functions,
//one to calculate the distance between two points and another to find the index of the nearest group of a giiven point

//define a  structure  called POint to store coordinates x and y
struct Point 
{
                     float X;
                     float Y;
};
//define a structure called groyp to store group information
struct Group 
{
         //store the average point of the group
           Point average;
        //store the number of points in the group
           int size;
        //store an array of pointers to the points in the group
           Point* points;
};

// calculate distance between two points
//The function takes two arguments p1 (a) and p2 (b).
float distance(Point point_1, Point point_2) 
{
    //we calculates the difference between the x-coordinates and the y-coordinates
    // of the two points using the variables dx and dy, respectively.
    float dx = point_1.X - point_2.X;
    float dy = point_1.Y - point_2.Y;
    //calculates the Euclidean distance between the two points using
    // the Pythagorean theorem (sqrt(dxdx + dydy))
    float euclidean_distance;
    euclidean_distance = sqrt(dx*dx + dy*dy);
    return euclidean_distance;

}

// This function takes a point (P as an argumnet of the structure Point) ,
//an array of groups (Groups as an argumnet of the struct Group), and the total number of groups (num_of_groups) as parameters to find the centroid 
// It calculates the distance between the given point and the average point of each group in the array
// It then returns the index of the group with the closest average point to the given point.

int nearestGroup(Point P, Group* Groups, int num_of_groups)
{
    // Initialize the index of the nearest group as the index of the first group
int nearest = 0;
// Initialize the minimum distance as the distance between the given point and the first group's average point
double minimum_dist = distance(P, Groups[0].average);

// Loop through the rest of the groups in the array
for (int i = 1; i < num_of_groups; i++)
{
// Calculate the distance between  the current group's average point and the given point
double euclidean_distance = distance(P, Groups[i].average);
// If the current group is closer to the point than the previous closest group,
// update the minimum distance and the index of the nearest group (through counter loop)
if ( minimum_dist > euclidean_distance)
{
minimum_dist = euclidean_distance;
nearest = i;
}
}
// Return the index of the nearest group
return nearest;
}
int main() {
    // initialize data points and groups
    // take 10 data points
    Point data_points[] = {{2,10}, {3,7}, {4,2}, {7,5}, {7,5}, {5,1}, {3,9}, {1,5},{2,9},{7,1}};
    // the num of data points 10
    const int num_data_points = 10;
    // Define an array of 4 groups, each with an average point, size, and an array of points
    Group Groups[] = {{{2,10}, 0, nullptr}, {{7,5}, 0, nullptr}, {{3,9}, 0, nullptr},{{2,9}, 0 ,nullptr}};
    const int num_of_groups = 4;

    // assign each data point to the nearest group/index
    bool converged ;
    converged = false;
    //iteration
    int current_state = 1; // 1st iterate
    cout<<"--------------------------------------------------"<<endl;
    // Run the loop until the groups are converged
     do 
    {
        int a ;
        int b;
            // assign each data point to the nearest group/index
        for ( a = 0; a < num_data_points; a++ )
        {
            int nearest;
               // Find the index of the nearest group for the data point
            nearest = nearestGroup(data_points[a], Groups, num_of_groups);
            // If the points array for the group has not been allocated / is a null pointer, allocate memory for it
            if (Groups[nearest].points == nullptr) 
            {
                //alocate memory
                Groups[nearest].points = new Point[num_data_points];
            }
            // Add the data point to the points array of the nearest group
            Groups[nearest].points[Groups[nearest].size++] = data_points[a];
        }
        // calculate the averages for every group
        converged = true;
        
        for (int a = 0; a < num_of_groups; a++) 
        {
              // Initialize a sum variable for each group 
              // x and y coordinates 0
            Point sum = {0, 0};
            for ( b = 0; b < Groups[b].size; b++)
            {
                // Sum the X and Y coordinates of all points in the group
                sum.X = sum.X + Groups[a].points[b].X;
                sum.Y = sum.Y + Groups[a].points[b].Y;
            }
               // calculate the average
             Point average ;
             average = {sum.X / Groups[a].size, sum.Y / Groups[b].size};
               //  check If the distance between the current average points and previous average points is greater than the threshold (0.001)
               // than the groups have not converged
            if (distance(average, Groups[a].average) > 0.001)
            {
                Groups[a].average = average;
                converged = false;
            }
              // delete the memory allocated for the points array of each group
            delete[] Groups[a].points;
            Groups[a].points = nullptr;
            Groups[a].size = 0;
        }
        // Print the current iteration  of each group and its average points 
        cout << "Iteration / state of each group " << current_state << endl;
        cout<<"--------------------------------------------------"<<endl;
        for (int a = 0; a < num_of_groups; a++)
        {
            cout << a +1 <<") "<< "Group " << a+1 << " = ";
            for (int b = 0; b < Groups[a].size; b++)
            {
                cout << "(" << Groups[a].points[b].X << "," << Groups[a].points[b].Y << ") "<<endl;
            }
            cout << "AVERAGE  ="<<" (" << Groups[a].average.X << "," << Groups[a].average.Y << ")" << endl;
            
        }
        cout<<"---------------------------------------------------"<<endl;
        current_state++;
    } while (!converged) ;

    // delete the dynamically allocated memory
    int a;
   for ( a = 0; a < num_of_groups; a++) 
   {
   delete[] Groups[a].points;// release the memory allocated for the points array of each group
   }
   return 0;// exit the code
}
//terminate the program
   
