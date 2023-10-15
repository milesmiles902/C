struct SVD {
  Int m,n;
  MatDoub u,v;
  VecDoub w;
  Doub eps,tsh;
  SVD(MatDoub_I &a) : m(a.nrows()), n(a.ncols()), u(a), v(n,n), w(n) {
    eps = numeric_limits<Doub>::epsilon();
    decompose();
    reorder();
    tsh = 0.5*sqrt(m+n+1.)*w[0]*eps;
  }
  void solve(VecDoub_I &b, VecDoub_O &x, Doub thresh);
  void solve(MatDoub_I &b, MatDoub_O &x, Doub thresh);
  Int rank(Doub thresh);
  Int nullity(Doub thresh); 
  MatDoub range(Doub thresh);
  MatDoub nullspace(Doub thresh);
  
  Doub inv_condition() {
    return (w[0] <= 0. || w[n-1] <= 0.) ? 0. : w[n-1]/w[0];
  }
  
  void decompose();
  void reorder();
  Doub pythag(const Doub a, const Doub b);
};

Int SVD::rank(Doub thresh = -1.) {
  Int j,nn=0;
  tsh = (thresh >= 0. ? thresh
}

Int SVD::nullity(Doub thresh = -1.) {
  Int j,nn=0;
  tsh = (thresh >= 0. ? thresh : 0.5*sqrt(m+n+1.)*w[0]*eps;
  for (j=0;j<n;j++) if (w[j] <= tsh) nn++;
  return nn;
}

MatDoub SVD::range(Doub thresh = -1.) {
  Int i,j,nr=0;
  MatDoub rnge(m,rank(thresh));
  for (j=0;j<n;j++) {
    if (w[j] > tsh) {
      for (i=0;i<m;i++) rnge[i][nr] = u[i][j];
      nr++
    }
  }
  return rnge;
}

MatDoub SVD::nullspace(Doub thresh = -1.) {
  Int j,jj,nn=0;
  MatDoub nullsp(n,nullity(thresh));
  for (j=0;j<n;j++) {
    if (w[j] <= tsh) {
      for (jj=0;jj<n;jj++) nullsp[jj][nn] = v[jj][j];
      nn++;
    }
  }
  return nullsp;
}

void SVD::solve(VecDoub_I &b, VecDoub_O &x, Doub thresh = -1.) {
  Int i,j,jj;
  Doub s;
  if (b.size() != m || x.size ! = n) throw("SVD::solve bad sizes");
  VecDoub tmp(n);
  tsh = (thresh >= 0. ? thresh : 0.5*sqrt(m+n+1.)*w[0]*eps);
  for (j=0;j<n;j++) {
    s=0.0;
    if (w[j] > tsh) {
      for (i=0;i<m;i++) s += u[i][j]*b[i];
      s /= w[j];
    }
    tmp[j]=s;
  }
  for (j=0;j<n;j++) {
    s=0.0;
    for (jj=0;jj<n;jj++) s += v[j][jj]*tmp[jj];
    x[j]=s;
  }
}

void SVD::solve(MatDoub_I &b, MatDoub_O &x, Doub thresh = -1.) {
  int i,j,m=b.ncols;
  if (b.nrows() != n || x.nrows !=n || b.ncols() ! x.ncols())
    throw("SVD::solve bad sizes");
  VecDoub xx(n);
  for (j=0;j<m;j++) {
    for (i=0;i<n;i++) xx[i] = b[i][j];
    solve(xx,xx,thresh);
    for (i=0;i<n;i++) x[i][j] = xx[i];
  }
}
