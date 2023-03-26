#include <stdio.h>
#include <math.h>

// Defining the value of pi
#define M_PI 3.14


double rot_z[3][3];
double rot_x[3][3];
double rot_y[3][3];



void create_rot_z(double theta) {
    // creates a rotation matrix around the z axis
    // takes an angle in degrees as input
    // the rotation matrix is stored in the global variable rot_z
    // there is no need to return anything, which is quite cool

    // converting the angle to radians
    theta = theta * M_PI / 180.0;

    // filling the matix with the rotation matrix
    rot_z[0][0] = cos(theta);
    rot_z[0][1] = -sin(theta);
    rot_z[0][2] = 0;
    rot_z[1][0] = sin(theta);
    rot_z[1][1] = cos(theta);
    rot_z[1][2] = 0;
    rot_z[2][0] = 0;
    rot_z[2][1] = 0;
    rot_z[2][2] = 1;

    }

void create_rot_x(double theta) {
    // Because we first rotate around Y and then around Z the rotation around X
    // is never used in this program, but I have included it to be able to test it.
    // Im leaving it here, because why not. :D

    theta = theta * M_PI / 180.0;

    rot_x[0][0] = 1;
    rot_x[0][1] = 0;
    rot_x[0][2] = 0;
    rot_x[1][0] = 0;
    rot_x[1][1] = cos(theta);
    rot_x[1][2] = -sin(theta);
    rot_x[2][0] = 0;
    rot_x[2][1] = sin(theta);
    rot_x[2][2] = cos(theta);

}

void create_rot_y(double theta) {
    // creates a rotation matrix around the y axis
    // takes an angle in degrees as input

    // converting the angle to radians
    theta = theta * M_PI / 180.0;

    // filling the matix with the rotation matrix
    rot_y[0][0] = cos(theta);
    rot_y[0][1] = 0;
    rot_y[0][2] = sin(theta);
    rot_y[1][0] = 0;
    rot_y[1][1] = 1;
    rot_y[1][2] = 0;
    rot_y[2][0] = -sin(theta);
    rot_y[2][1] = 0;
    rot_y[2][2] = cos(theta);
}

void matrix_vector_multiply(double matrix[3][3], double vector[3], double result[3]) {
    // multiplies a 3x3 matrix with a 3x1 vector
    // takes the matrix, the vector and the result as input
    // returns nothing, but stores the result in the result vector

    // looping through the rows of the matrix
    for (int i = 0; i < 3; ++i) {
        result[i] = 0;
        // looping through the columns of the matrix
        for (int j = 0; j < 3; ++j) {
            // multiplying the value of each element of the matrix with the corresponding element of the vector
            result[i] += matrix[i][j] * vector[j];
        }
    }
}



int main() {

    // creatin the B->A Vector
    double base_elbow[3] = {-9.3, 0, 3.5};

    // Creating the A->T Vector
    double elbow_wrist[3] = {17, 0, 0};

    double base_rot;
    double arm_direction;

    printf("Enter base rotation angle (degrees): ");
    scanf("%lf", &base_rot);
    printf("Enter arm direction angle (degrees): ");
    scanf("%lf", &arm_direction);

    //Getting a rotation matrix for both joints
    create_rot_z(base_rot);
    create_rot_y(arm_direction);

    // creating a temporary vector to store the result of the first matrix multiplication
    double temp_result[3];

    // Rotating the A->T vector around the Y axis
    matrix_vector_multiply(rot_y, elbow_wrist, temp_result);

    // Adding the B->A vector to the result of the first matrix multiplication 
    // to get the vector between the base and the hand
    for (int i = 0; i < 3; ++i) {
        temp_result[i] += base_elbow[i];
    }

    // Taking this result and rotating it around the Z axis
    double final_result[3];
    matrix_vector_multiply(rot_z, temp_result, final_result);

    // Printing the result
    printf("Vector between the base and the hand: ");
    for (int i = 0; i < 3; ++i) {
        printf("%.4f ", final_result[i]);
    }
    printf("\n");

    return 0;
}
