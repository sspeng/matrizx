#include "matrizx.h"

/* This is some demonstration code for matrizx.h */

int main(void)
{
    matrix *a,*b,*result; //create some pointers to matrix structs
    
    //Initialize both matrices
    a = m_new(4,4); 
    b = m_new(4,4);
    
    //Set some elements on matrix A
    a->array[0][0] = 1;
    a->array[1][1] = 2;
    a->array[2][2] = 1;
    a->array[3][3] = 2;
    
    m_set_elements(b,4); //Set all elements from B to 4    
    
    result = m_multiplication(a,b); //Multiply the matrices and return the adress of the result
    
    printf("\nMatriz A:\n");
    m_printf(a);
    
    printf("\nMatriz B:\n");
    m_printf(b);
    
    printf("\nResult: \n");
    m_printf(result);
    
    return 0;
}
