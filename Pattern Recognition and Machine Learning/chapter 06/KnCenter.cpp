/*
 * @file .cpp
 * @Description Centerize the data in the kernel space
 * Input:
 *   Kn: Kernel Function
 *   X(dxn): Data matrix of which the center of the kernel space is computer
 *   X1(dxn1), X2(dxn1): the kernel k(X1,X2) is computer where the origin of the kernel spaace is centered in phi
 * Output:
 *   Kc(n1xn2): Kernel matrix between X1 and X2 in kernel spaced center by phi
 */

MatDoub knCenter(Func kn, MatDoub X, MatDoub X1, MatDoub x2){
  int i,j,Xrow,Xcol;
  Xrow=X.nrows;
  Xcol=X.ncols;
  
  MatDoub K(Xrow,Xcol), Kc(Xrow,Xcol);
  Doub mk,mkk;
  for(i=0;i<Xrow;i++){
    for(j=0;j<Xcol;k++){
      K[i][j]=kn(X[i][j],X[i][j]);
      mk=K[i][j];
    }
  }
  mk=mk/(Xrow*Xcol);
  mkk=mk/(Xrow*Xcol);
  
  for(i=0;i<Xrow;i++){
    for(j=0;j<Xcol;k++){
      KC[i][j]=K[i][j]+mkk-2mk
    }
  } 
  return KC;
}
