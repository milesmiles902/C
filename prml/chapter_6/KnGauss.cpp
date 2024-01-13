/*
 * @file .cpp
 * @Description Gaussian (RBF) Kernel K = exp(-|x-y|/(2s));
 * Input:
 *   X(dxnx): Data Matrix
 *   Y(dxny): Data Matrix
 *   S: sigma of gaussian
 * Output: 
 *   K(nxxny) Kernel Matrix
 */

MatDoub knGauss(X,Y,s){
  int i,j,k,xrow,xcol;
  xrow=X.nrows();
  xcol=X.ncols();
  MatDoub D(xrow,xcol),K(xrow,xcol);
  
  for(i=0;i<xrow;i++){
    for(j=0;i<xcol;i++){
      for(k=0;k<xrow;k++){
        D[i][j]+=X[i][k]*X[k][j]+Y[i][k]*Y[k][j]-2*X[i][k]*Y[k][j];
      }
      K[i][j]=exp(D[i][j]/(-2*S*S);
    }
  }
  return K;
}
