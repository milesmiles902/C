/*
 * @file .cpp
 * @Description: Transform a kernel matrix( or inner product matrix) to a squared distance matrix
 * Input:
 *  K(nxn): kernel matrix
 * Output:
 *  D(nxn): squared distance matrix
 */

MatDoub kn2sd(MatDoub K){
  int i,j;
  MatDoub d, D;
  for(i=0;i<K.nrows();i++){
    for(j=0;j<K.ncols();j++){
       d=K[i][i];
       if(i==j){
         D[i][j]=-2K[i][j]+K[i][j]*K[i][j];
       } else {
         D[i][j]=-2K[i][j];
       }
    }
  }
  return D;
}
