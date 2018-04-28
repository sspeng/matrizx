#include "matrizx.h"

/* This is some demonstration code for matrizx.h */

int main(void)
{
    matrix *a,*b,*result;

    a = m_new(4,4); //create new matrix a with 4 rows and 4 columns

    m_set_elements(a,1); // Set all elements of a to 1

	/* Set some more elements on a */
    a->array[0][3] = 2;
    a->array[1][1] = 5;
    a->array[1][2] = 3;
    a->array[2][2] = 0;
    a->array[3][1] = 6;

    b = m_new(4,4);

    m_set_elements(b,2);

    b->array[0][0] = 4;
    b->array[0][1] = 2;

	/* Print both matrices */
    printf("Matrix A:\n");
    m_printf(a); 

    printf("\nMatrix B:\n");
    m_printf(b);

	
    result = m_multiplication(a,b); // multiply matrices and return a pointer to the result

    printf("\nMatrix A*B:\n");
    m_printf(result);

    printf("\nDeterminant of the result: %f\n\n",m_det(result)); // get determinant of the result

    return 0;
}
