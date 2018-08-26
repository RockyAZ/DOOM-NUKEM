#include <stdio.h>
#include <stdlib.h>

// int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
// {
// 	float s1_x, s1_y, s2_x, s2_y;
// 	s1_x = p1_x - p0_x;
// 	s1_y = p1_y - p0_y;

// 	s2_x = p3_x - p2_x;
// 	s2_y = p3_y - p2_y;

// 	float s, t;
// 	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
// 	t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
// 	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
// 	{
// 		// Collision detected
// 		if (i_x != NULL)
// 			*i_x = p0_x + (t * s1_x);
// 		if (i_y != NULL)
// 			*i_y = p0_y + (t * s1_y);
// 		return 1;
// 	}
// 	return 0; // No collision
// }

typedef struct s_pddd
{
	int first;
	int second;
}				pddd;

typedef struct s_pdd
{
	int x1;
	int y1;

	int x2;
	int y2;
}				pdd;


pddd make_pair(int x, int y)
{
	pddd var;
	var.first = x;
	var.second = y;
	return (var);
}

pddd lineLineIntersection(pdd a, pdd b)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = a.y2 - a.y1;
    double b1 = a.x1 - a.x2;
    double c1 = a1*(a.x1) + b1*(a.y1);
 
    // Line CD represented as a2x + b2y = c2
    double a2 = b.y2 - b.y1;
    double b2 = b.x1 - b.x2;
    double c2 = a2*(b.x1)+ b2*(b.y1);
 
    double determinant = a1*b2 - a2*b1;

	if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
		return make_pair(0, 0);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}

int main(int zc, char **av)
{
	pdd A;
	pdd B;
	// pdd C;
	// pdd D;

A.x1 = atoi(av[1]);
A.y1 = atoi(av[2]);

A.x2 = atoi(av[3]);
A.y2 = atoi(av[4]);


B.x1 = atoi(av[5]);
B.y1 = atoi(av[6]);

B.x2 = atoi(av[7]);
B.y2 = atoi(av[8]);

	// // A = make_pair(64, 64);
	// // B = make_pair(192, 256);
	// // C = make_pair(192, 64);
	// // D = make_pair(0, 256);

	// A = make_pair(atoi(av[1]), atoi(av[2]));
	// B = make_pair(atoi(av[3]), atoi(av[4]));
	// C = make_pair(atoi(av[5]), atoi(av[6]));
	// D = make_pair(atoi(av[7]), atoi(av[8]));

	pddd res = lineLineIntersection(A, B);
	printf("X:%d\nY:%d\n", res.first, res.second);
	// printf("%d\n", get_line_intersection(atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4]), atoi(av[5]), atoi(av[6]), atoi(av[7]), atoi(av[8]), NULL, NULL));
}
