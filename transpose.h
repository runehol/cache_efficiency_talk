#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "tensor3d.h"
void transpose_simple(Tensor3D &out, const Tensor3D &in);
void transpose_blocked(Tensor3D &out, const Tensor3D &in);


#endif //TRANSPOSE_H
