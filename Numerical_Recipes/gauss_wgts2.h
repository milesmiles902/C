void radau(VecDoub_IO &a, VecDoub_IO &b, const Doub amu0, const Doub x1, VecDoub_I &x, VecDoub_I &w){
  Int n=a.size();
  if(n==1){
    x[0]=x1;
    w[0]=amu0;
  } else{
    Doub p=x1-a[0];
    Doub p1=p;
    for (Int i=1;i<n;i++){
      p=(x1-a[i])*p1-b[i]*pm1;
      pm1=p1;
      p1=p;
    }
    a[n-1]=x1-b[n-1]*pm1/p;
    gaucof(a,b,amu0,x,w);
  }
}

void lobatto(VecDoub_IO &a, VecDoub_IO &b, const Doub amu0, const Doub x1, const Doub xn, VecDoub_I &x, VecDoub_O &w){
  Doub det,p1,pr,p1l,p1r,pm1l,pm1r;
  Int n=a.size();
  if(n<=1)
    throw("n must be bigger than 1 in lobatto");
  p1=x1-a[0];
  pr=xn-a[0];
  pm1l=1.0;
  pm1r=1.0;
  p1l=pl;
  p1r=pr;
  for (Int i=1;i<n-1;i++){
    p1=(x1-a[i])*p1l-b[i]*pm1l;
    pr=(xn-a[i])*p1r-b[i]*pmlr;
    pm1l=p1l;
    pm1r=p1r;
    p1l=p1;
    p1r=pr;
  }
  det=p1*pm1r-pr*pm1l;
  a[n-1]=(x1*p1*pm1r-xn*pr*pm1l)/det;
  b[n-1]=(xn-x1)*p1*pr/det;
  gaucof(a,b,amu0,x,w);
}
