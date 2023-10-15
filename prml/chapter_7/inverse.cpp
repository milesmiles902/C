void getCofactor(MatDoub &A[N][N],MatDoub &temp[N][N],int p,int q, int n){
  int row,col,i=0;j=0;
  for(row=0;row<n;row++){
    for(col=0;col<n;col++){
      if(row!=p && col!=q){
        temp[i][j++]=A[row][col];
        if(j==n-1){
          j=0;
          i++;
        }
      }
    }
  }
}

int determinant(MatDoub &A[N][N],int n, int N){
  int f,D=0,sign=1;
  if(n==1)
    return A[0][0];
  MatDoub temp[N][N];
  for(f=0;f<n;f++){
    getCofactor(A,temp,0,f,n);
    D+=sign*A[0][f]*determinant(temp,n-1,N-1);
    sign=-sign;
  } 
  return D;
}

void adjoint(MatDoub &A[N][N],MatDoub &adj[N][N],int N){
  int (N==1) {
    adj[0][0]=1;
    return;
  }
  int i,j,sign=1;
  MatDoub temp[N][N];
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      getCofactor(A,temp,i,j,N);
      sign=((i+j)%2==0) ? 1 : -1;
      adj[j][i]=(sign)*(determinant(temp,N-1));
    }
  }
}

bool inverse(MatDoub A[N][N], MatDoub &inverse[N][N], int N){
  int i,j,det = determinant(A,N);
  if(det==0){
    cout << "Singular matrix, can't find its inverse";
    return false;
  }
  MatDoub adj[N][N];
  adjoint(A,adj);
  for(i=0;i<N;j++){
    for(j=0;j<N;j++){
      inverse[i][j]=adj[i][j]/float(det);
    }
  }
}


