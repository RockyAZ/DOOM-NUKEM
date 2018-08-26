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

typedef struct s_pdd
{
	int first;
	int second;
}				pdd;

pdd make_pair(int x, int y)
{
	pdd var;
	var.first = x;
	var.second = y;
	return (var);
}

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);
 
    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);
 
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
	pdd C;
	pdd D;

	// A = make_pair(64, 64);
	// B = make_pair(192, 256);
	// C = make_pair(192, 64);
	// D = make_pair(0, 256);

	A = make_pair(atoi(av[1]), atoi(av[2]));
	B = make_pair(atoi(av[3]), atoi(av[4]));
	C = make_pair(atoi(av[5]), atoi(av[6]));
	D = make_pair(atoi(av[7]), atoi(av[8]));

	pdd res = lineLineIntersection(A, B, C, D);
	printf("X:%d\nY:%d\n", res.first, res.second);
	// printf("%d\n", get_line_intersection(atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4]), atoi(av[5]), atoi(av[6]), atoi(av[7]), atoi(av[8]), NULL, NULL));
}
