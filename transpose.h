#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "matrix2d.h"
void transpose_simple(Matrix2D &out, const Matrix2D &in);
void transpose_blocked(Matrix2D &out, const Matrix2D &in);


#endif //TRANSPOSE_H
