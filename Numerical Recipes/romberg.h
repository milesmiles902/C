template <class T>
Doub qromb(T &func, Doub a, Doub b, const Doub eps=1.0e-10){
  const Int JMAX=20, JMAXP=JMAX+1,K=5;
  VecDoub s(JMAX),h(JMAXP);
  Poly_interp polint(h,s,K);
  h[0]=1.0;
  Trapzd<T> t(func,a,b);
  for (Int j=1;j<=JMAX;j++){
    s[j-1]=t.next();
    if (j>=K){
      Doub ss=polint.rawinterp(j-K,0.0);
      if (abs(polint.dy) <= eps*abs(ss)) return ss;
    }
    h[j]=0.25*h[j-1];
  }
  throw("Too many steps in routine qromb");
}


