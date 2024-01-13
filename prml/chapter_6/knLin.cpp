/*
 * @file .cpp
 * @Description Linear kernel (inner product)
 * Input:
 *   X(dxnx): Data Matrix
 *   Y(dxny): Data Matrix
 * Output:
 *   K(nxxny): Kernel Matrix
 */

MatDoub knLin(MatDoub X, MatDoub Y){
   Int i,j,k,xrow,xcol;
   xrow=X.nrow();
   xcol=X.ncol();
   MatDoub K(xrow,xcol);
   for(i=0;i<xrow;i++){
     for(j=0;j<xcol;j++){
       for(k=0;k<xrow;k++){
         K[i][j]+=X[k][j]*Y[k][j];
       }
     }
   }
   return K; 
}
