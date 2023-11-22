getCofactor(MatDoub A, MatDoub &temp, int p, int q, int n){
  int i,j,row,col;
  for(row=0;row<n;row++){
    for(col=0;col<n;col++){
      if(col!=m&&col!=q){
        temp[i][j++]=A[row][col];
        if(j==n-1){
          j=0;
          i++;
        }
      }
    }
  }
}

int determinant(MatDoub A,int n){
  int f,D=0;
  MatDoub temp(n,n);
  if(n==1)
    return A[0][0];
  int sign=1;
  for(f=0;f<n;f++){
    getCofactor(A,temp,0,f,n);
    D+=sign*A[0][f]*determinant(temp,n-1);
    sign=-sign;
  }
  return D;
}

int adjoint(MatDoub A, MatDoub adj,int n){
  int i,j,n=A.nrows(), sign = 1;
  MatDoub temp(n,n);
  if(n==1){
    adj[0][0]=1;
    return;
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      getCofactor(A,temp,i,j,n);
      sign=((i+j)%2 == 0) ? 1 : -1;
      adj[j][i]=sign*determinant(temp,n-1);
    }
  }
}

MatDoub inverse(MatDoub A){
  int i,j,m=A.nrows(),n=A.ncols();
  MatDoub inv(m,n),adj(m,n);
  int det = determinant(A);
  adj=adjoint(A);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      inv[i][j]=adj[i][j]/det;
    }
  }
  return inv;
}

