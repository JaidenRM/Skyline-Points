/* Skeleton code for COMP10002 Assignment 1, March 2017.
   Jianzhong Qi, jianzhong.qi@unimelb.edu.au
*/

/* Completed code for COMP10002 Assignment 1, April 2017.
   Jaiden Muscat, muscatj@student.unimelb.edu.au, Student #831489
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIV "==========" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define READ_OK 1 /* reading point succeeded */
#define READ_FAILED 0 /* reading point failed */

#define MAX_NUM_POINTS 99 /* maximum number of points */
#define MAX_NUM_DIMENSIONS 10 /* maximum number of dimensions */

typedef double point_t[MAX_NUM_DIMENSIONS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);
void stage_five(point_t points[], int num_points, int num_dimensions);

void print_stage_heading(int stage);
int read_one_point(point_t one_point, int num_dimensions);

/* algorithms are fun*/

/* add your own function prototypes here */
void sum_coords(point_t points[], int num_dimensions, double *coordinate_sums, 
	int num_points);
void graph_sums(double *coordinate_sums, int num_points);
void skyline_points(point_t points[], int num_dimensions, int i);
void sort_points_dominated(int *array_points_dominated, int 
	*index_skyline_points, int index);

/* main program binds it all together */
int
main(int argc, char *argv[]) {

	/* storage for the input data */
	int num_dimensions;
	point_t points[MAX_NUM_POINTS];
	
	/* storage for statistics */
	int num_points = 0; /* number of points read in */
	double coordinate_sums[MAX_NUM_POINTS]; /* coordinate sums of the points */
	
	/* read the first line - number of dimensions */
	scanf("%d", &num_dimensions);
	
	/* stage 1 */
	stage_one(points[0], &num_points, num_dimensions);

	/* stage 2 */
	stage_two(points, &num_points, num_dimensions, 
		coordinate_sums);
	
	/* stage 3 */
	stage_three(coordinate_sums, num_points);

	/* stage 4 */
	stage_four(points, num_points, num_dimensions);

	/* stage 5 */
	stage_five(points, num_points, num_dimensions);
	
	/* and done! */
	return 0;
}

/* print out a stage heading, with a prior blank line once the stage number
   goes plus one 
*/
void 
print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if (stage > STAGE_NUM_ONE) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n%s\n", stage, DIV);
}

/* read the coordinates of one point, store them in one_point
*/
int 
read_one_point(point_t one_point, int num_dimensions) {
	int i = 0;
	
	/* keep reading until num_dimensions numbers have been obtained */
	while (i < num_dimensions) {
		if (scanf("%lf", one_point+i) != 1) {
			return READ_FAILED;
		}
		i++;
	}
	
	return READ_OK;
}

/* stage 1 - read in and print one point
*/
void 	/* */
stage_one(point_t one_point, int *num_points, int num_dimensions) {
	/* print stage heading for stage 1 */
	print_stage_heading(STAGE_NUM_ONE);
	
	/* add your code here for stage 1 */
	int i = 0;
	printf("Point 01:%c%c", ' ', '<');
	while(i<num_dimensions) {
		if(i>0){
			printf("%c%c", ',', ' ');
		}
		scanf("%lf", &one_point[i]);
		printf("%.2f", one_point[i]);
		i++;
	}
	printf("%c\n", '>');
	(*num_points)++;
}

/* stage 2 - read in the rest of the points and visualise them
*/
void 
stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums) {
	/* print stage heading for stage 2 */
	print_stage_heading(STAGE_NUM_TWO);
	
	/* add your code here for stage 2 */
	point_t one_point;
	int i = 0;
	int j = 1;
	int k = 0;
	/*uses read_one_point to read coords which are then stored in points[] a 2d
	array while the total number of points is tallied too
	*/
	while (read_one_point(one_point, num_dimensions)) {
		while(i<num_dimensions) {			
			points[j][k] = one_point[i];
			i++;
			k++;
		}
		j++;
		i = 0;
		k = 0;
		(*num_points)++;
	}
	sum_coords(points, num_dimensions, coordinate_sums, *num_points);
	graph_sums(coordinate_sums, *num_points);
}	

/* sum_coords - returns the points into coordinate_sums after they've been 
   summed and then divided by 100
*/
void
sum_coords(point_t points[], int num_dimensions, double *coordinate_sums, 
	int num_points) {
	double counter = 0.00;
	int i,j;
	for(i=0; i<num_points; i++) {
		for(j=0; j<num_dimensions; j++) {
			counter += points[i][j];
		}
		coordinate_sums[i] = counter/100;
		counter = 0;
	}
}

/* graph_sums - returns the points in ascending order, their value from 
   sum_coords and then prints out a graphical display of this value which is 
   always rounded up and '+' represents every 10th value.
*/
void graph_sums(double *coordinate_sums, int num_points) {
	int i=0;
	int j=0;
	while(i<num_points) {
		printf("Point %02d, sum of coordinates (/100):%6.2f", i+1, 
		coordinate_sums[i]);
		printf(" |");
		while(coordinate_sums[i]>j) {
			if((j+1)%10==0 && j!=0) {	// j+1 is to make sure it is rounded up
				printf("%c", '+'); 
			}
			else {
				printf("%c", '-');
			}
			j++;
		}
		i++;
		j=0;
		printf("\n");
	}
}
			
/* stage 3 - print statistics
*/
void 
stage_three(double *coordinate_sums, int num_points) {
	/* print stage heading for stage 3 */
	print_stage_heading(STAGE_NUM_THREE);
	
	/* add your code here for stage 3 */
	int i;
	double max = 0;
	int elem = 0;
	printf("Total: %d points\n", num_points);
	for(i=0;i<num_points;i++) {
		coordinate_sums[i]*=100;
		if(max<coordinate_sums[i]) {
			max = coordinate_sums[i];
			elem = i;	// to track the index of the max sum
		}
		else if(max==coordinate_sums[i]) {	//if tied, lowest point is chosen
			if(elem>i) {
				elem = i;
			}
		}
	}
	printf("Point of largest sum of coordinates: %02d\n", elem+1);
	printf("Largest sum of coordinates: %.2f\n", coordinate_sums[elem]);
}

/* stage 4 - find and print the skyline points
*/
void 
stage_four(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 4 */
	print_stage_heading(STAGE_NUM_FOUR);
	
	/* add your code here for stage 4 */
	printf("Skyline points:\n");	
	int counter, i, j, k;
	int cnt_not_dominated = 0;
	/* starts from one point and checks if it is dominated by any of the other 
	   points
	*/
	for(i=0;i<num_points; i++) {
		for(j=0; j<num_points; j++) {
			counter = 0;
			for(k=0; k<num_dimensions; k++) {
				/* counts whenever the points coords dominates another points
				   coords
				*/
				if(points[i][k]>points[j][k] && j != i) {
					counter++;
				}
			}
			/* if the counter does not equal to 0 it means that point can't be
			   dominated by the other point as it has at least a coord greater
			   than the other point
			*/
			if(counter != 0) {
				cnt_not_dominated++;
			}
		}
		/* if the point isn't dominated by any points then it's a skyline point
		*/
		if(cnt_not_dominated == (num_points-1)) {
			skyline_points(points, num_dimensions, i);
		}
		cnt_not_dominated = 0;
	}
}

/* skyline_points - prints out the points found to be a skyline point
*/
void
skyline_points(point_t points[], int num_dimensions, int i) {
	int j;
	for(j=0;j<num_dimensions;j++) {
		/* if/else statements used to correctly format
		*/
		if(j==num_dimensions-1) {
			printf("%.2f>\n", points[i][j]);
		}
		else if(j==0) {
			printf("Point %02d: <%.2f, ", i+1, points[i][j]);
		}
		else {	
			printf("%.2f, ", points[i][j]);
		}
	}
}

/* stage 5 - sort and print the skyline points by the number of points 
   they dominate
*/
void 
stage_five(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 5 */
	print_stage_heading(STAGE_NUM_FIVE);
	
	/* add your code here for stage 5 */
	int counter, i, j, k;
	int cnt_dominated = 0;
	int index = 0;
	int index_skyline_points[num_points];
	int array_points_dominated[num_points];
	int cnt_not_dominated = 0;
	/* these loops are used to store the skyline points indexes in an array and
	   how many of them are in a counter called 'index'
	*/
	for(i=0;i<num_points; i++) {	
		for(j=0; j<num_points; j++) {
			counter = 0;
			for(k=0; k<num_dimensions; k++) {
				if(points[i][k]>points[j][k] && j != i) {
					counter++;
				}
			}
			if(counter != 0) {
				cnt_not_dominated++;
			}
		}
		if(cnt_not_dominated == (num_points-1)) {
			index_skyline_points[index] = i;
			index++;
		}
		cnt_not_dominated = 0;
	}
	/* these loops are used to store how many points each skyline point
	   dominates in an array
	*/
	for(i=0;i<index; i++) {	
		for(j=0; j<num_points; j++) {
			counter = 0;
			for(k=0; k<num_dimensions; k++) {
				if(points[index_skyline_points[i]][k]>=points[j][k] && j != 
				index_skyline_points[i]) {
					counter++;
				}
			}
			if(counter == num_dimensions) {
				cnt_dominated++;
			}
		}
		array_points_dominated[i] = cnt_dominated;
		cnt_dominated = 0;
	}
	sort_points_dominated(array_points_dominated, index_skyline_points, index);
	printf("Sorted skyline points:\n");
	for(i=0;i<index;i++) {
		for(j=0;j<num_dimensions;j++) {
			if(j==num_dimensions-1) {
				printf("%.2f>\n", points[index_skyline_points[i]][j]);
			}
			else if(j==0) {
				printf("Point %02d: <%.2f, ", index_skyline_points[i]+1, 
				points[index_skyline_points[i]][j]);
			}
			else {	
				printf("%.2f, ", points[index_skyline_points[i]][j]);
			}
		}
		printf("Number of points dominated: %d\n", array_points_dominated[i]);
	}
}

/* sort_points_dominated - sorts the number of points dominated out in
   descending order
*/
void sort_points_dominated(int *array_points_dominated, int *index_skyline_points, int index) {
	int i, j, max = 0, temp = 0, place = 0;
	for(i=0;i<index;i++) {
		/* this loop determines the highest number of points dominated left and 
		   its matching index number while making sure it there is a tie that
		   the lowest point is chosen first. Also, j=i is to make sure the
		   already sorted numbers aren't being chosen again
		*/
		for(j=i	; j<index;j++) {
			if(array_points_dominated[j]>max) {
				max = array_points_dominated[j];
				place = j;
			}
			else if(array_points_dominated[j]==max) {
				if(index_skyline_points[j]<index_skyline_points[place]) {
					max = array_points_dominated[j];
					place = j;
				}
			}
		}
		/* this moves the max and index chosen from the j loop and moves it to
		   the front in descending order
		*/
		temp = array_points_dominated[i];
		array_points_dominated[i] = max;
		array_points_dominated[place] = temp;
			
		temp = index_skyline_points[i];
		index_skyline_points[i] = index_skyline_points[place];
		index_skyline_points[place] = temp;
		max = -1;
	}
}