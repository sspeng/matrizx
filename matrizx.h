#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct matrix matrix;

struct matrix {
	float **array;
	int row;
	int col;
};


float **m_alloc_array(int row, int col)
{
	/* alloc a two dimension array */

	int count;
	float **m = (float **)malloc(row*sizeof(float*));

	if(!m) {
		fprintf(stderr,"\nMemory allocation error\n");
		exit(1);
	}

	for(count=0; count<row; count++) {
		m[count] = (float *)malloc(col*sizeof(float));

		if(!m[count]) {
			fprintf(stderr,"\nMemory allocation error\n");
			exit(1);
		}
	}
	return m;
}

void m_set_elements(matrix *m,float element)
{
	/* set all elements from a matrix struct to the value given */

	int x,y;

	for(y=0; y<(m->row); y++) {
		for(x=0; x<(m->col); x++) {
			m->array[y][x] = element;
		}
	}
}

matrix *m_new(int row,int col)
{
	/* Creates a new matrix struct */

	matrix *m;
	m = (matrix *)malloc(sizeof(matrix));

	if(!m) {
		fprintf(stderr,"\nMemory allocation error\n");
		exit(1);
	}

	m->array = m_alloc_array(row,col);
	m->row = row;
	m->col = col;

	m_set_elements(m,0);

	return m;
}

void m_printf(const matrix *m)
{
	/* prints all elements of the matrix struct formated */

	int x,y;

	for(y=0; y<(m->row); y++) {
		for(x=0; x<(m->col); x++) {
			printf(" %05.2f ",m->array[y][x]);
		}
		putchar('\n');
	}
}

int m_is_same_size(const matrix *a, const matrix *b)
{
	/* Checks if matrices are of the same size.
	 Returns 1 (true) or 0 (false) */

	if((a->row != b->row) || (a->col != b->col)) {
		return 0;
	}

	return 1;
}

matrix *m_copy(matrix *src)
{
	/* Creates a new matrix and copy all elements from src matrix
	into it */

	int x,y;
	matrix *cp;

	cp = (matrix *)malloc(sizeof(matrix));

	if(!cp) {
		fprintf(stderr,"\nMemory allocation error\n");
		exit(1);
	}

	cp->array = m_alloc_array(src->row,src->col);
	cp->row = src->row;
	cp->col = src->col;

	for(y=0; y<(cp->row); y++) {
		for(x=0; x<(cp->col); x++) {
			cp->array[y][x] = src->array[y][x];
		}
	}

	return cp;
}

void m_free(matrix *m)
{
	int y;

	for(y=0; y<(m->row); y++) {
		free(m->array[y]);
	}

	free(m->array);

	free(m);
}



/* matrix operations functions */

int m_add(matrix *a, matrix *b)
{
	/* adds two matrices together, putting the result in matrix a */
	/* returns 1 in error and 0 in success */

	int x,y;

	if(!m_is_same_size(a,b)) {
		return 1;
	}

	for(y=0; y<(a->row); y++) {
		for(x=0; x<(a->col); x++) {
			a->array[y][x] += b->array[y][x];
		}
	}

	return 0;
}


void m_multiply_by_num(matrix *m, float number)
{
	/* Multiply all elements from a Matrix
	by the given number */

	int x,y;

	for(y=0; y<(m->row); y++) {
		for(x=0; x<(m->col); x++) {
			m->array[y][x] *= number;
		}
	}
}


int m_sub(matrix *a, matrix *b)
{
	/* subtracts two matrices, and put the result into matrix a */
	/* returns 1 on error and 0 on success */

	int x,y;

	if(!m_is_same_size(a,b)) {
		return 1;
	}

	for(y=0; y<(a->row); y++) {
		for(x=0; x<(a->col); x++) {
			a->array[y][x] -= b->array[y][x];
		}
	}

	return 0;
}

matrix *m_multiplication(matrix *a, matrix *b)
{
	/* Perform a matrix multiplication between the two
	matrices, returns the result matrix */

	matrix *result;
	int ax,ay,bx,by,sum;

	if(a->col != b->row) {
		fprintf(stderr,"\nMatrix multiplication error: impossible multiplication\n");
		exit(1);
	}

	result = m_new(a->row,b->col);

	for(ay=0; ay<(a->row); ay++) {
		for(bx=0; bx<(b->col); bx++) {
			sum=0;
			by=0;
			for(ax=0; ax<(a->col); ax++) {
				sum+= a->array[ay][ax] * b->array[by][bx];
				by++;
			}

			result->array[ay][bx] = sum;
		}
	}

	return result;
}

matrix *m_transpose(matrix *m)
{
	/* returns the adress to the transposed matrix of M */

	matrix *result;
	int x,y;

	result = m_new(m->col,m->row);

	for(y=0; y<(m->row); y++) {
		for(x=0; x<(m->col); x++) {
			result->array[x][y] = m->array[y][x];
		}
	}

	return result;
}

float m_det(matrix *m)
{
	/* Returns the determinant of the matrix m */
	
	matrix *d;
	int i,j;
	float result=0;

	if(m->row != m->col) {
		fprintf(stderr,"\nDeterminant calculation error: non square matrix\n");
		exit(1);
	}

	if(m->row==1 && m->col == 1) {
		return m->array[0][0];
	}

	if(m->row==2) {
		return (m->array[0][0]*m->array[1][1]) - (m->array[0][1]*m->array[1][0]);
	}

	d = m_new(m->row-1,m->col-1);

	for(i=0; i<(m->row)-1; i++) {
		for(j=0; j<(m->col)-1; j++) {
			d->array[i][j] = m->array[i+1][j+1];
		}
	}

	i = 0;
	for(j=0; j<(m->col); j++) {
		result+=m->array[i][j]*(pow(-1,i+j+2)*m_det(d));
	}

	return result;
}
