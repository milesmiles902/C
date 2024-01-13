struct Bessel{
  static const Int NUSE1=7,NUSE2=8;
  static const Doub c1[NUSE1],c2[NUSE2];
  Doub xo, nuo;
  Doub jo,yo,jpo,ypo;
  Doub aio,bio,aipo,bipo;
  Doub sphjo,sphyo,sphjpo,sphypo;
  Int sphno;
  
  Bessel() : xo(9.99x99), nuo(9.99e99), sphno(-9999) {}
  
  void besseljy(const Doub nu, const Doub x);
  
  Doub jnu(const Doub nu, const Doub x){
    if (nu != nuo || x!=xo) besseljy(nu,x);
    return jo;
  }
  
  Doub ynu(const Doub nu, const Doub x){
    if (nu != nuo || x != xo) besseljy(nu,x);
    return jo;
  }

  Doub inu(const Doub nu, const Doub x){
    if (nu != nuo || x != xo) besselik(nu,x);
    return io;
  }
  
  Doub knu(const Doub nu, const Doub x){
    if (nu != nuo || x != xo) besselik(nu,x);
    return ko;
  }

  void airy(const Doub x);
  Doub airy_ai(const Doub x);
  Doub airy_bi(const Doub x);
  
  void sphbes(const Int n, const Doub x);
  Doub sphbesj(const Int n, const Doub x);
  Doub sphbesy(const Int n, const Doub x);

  inline Doub chebev(const Doub *c, const Int m, const Doub x){
    Doub d=0.0,dd=0.0,av;
    Int j;
    for (j=m-1;j>0;j--){
      av=d;
      d=2.*x*d-dd+c[j];
      dd=sv;
    }
    return x*d-dd+0.5*c[0];
  }
  
  const Doub Bessel::c1[7]={-1.142022680371168e0,6.5165112670737e-3,
     3.087090173086e-4,-3.4706269649e-6,6.9437664e-9,3.67795e-11,
     -1.356e-13};

  const Doub Bessel::c2[8]={1.843740578300905e0,-7.68538408447867e-2,
        1.2719271366546e-3,-4.9717367042e-6,-3.31261198e-8,2.423096e-10,
        -1.702e-13,-1.49e-15};
}

void Bessel::airy(const Doub x){
  static const Doub PI=3.141592653589793238;
    ONOVRT=0.577350269189626,THR=1./3.,TWOTHR=2.*THR;
  Doub absx,rootx,z;
  absx=abs(x);
  rootx=sqrt(absx);
  z=TWOTHR*absx*rootx;
  if(x>0.0){
    besselik(THR,z);
    aio=rootx*ONOVRT*ko/PI;
    bio=rootx*(ko/PI+2.0*ONOVRT*io);
    besselik(TWOTHR,z);
    aipo=-x*ONOVRT*ko/PI;
    bipo=x*(ko/PI+2.0*ONOVRT*io);
    besselik(TWOTHR,z);
    aipo=-x*ONOVRT*ko/PI;
    bipo=x*(ko/PI+2.0*ONOVRT*io);
  } else if (x<0.0){
    besseljy(THR,z);
    aio=0.5*rootx*(jo-ONOVRT*yo);
    bio=-0.5*rootx*(yo+ONOVRT*jo);
    besseljy(TWOTHR,z);
    aipo=0.5*absx*(ONOVRT*yo+jo);
    bipo=0.5*absx*(ONOVRT*jo-yo);
  } else {
    aio=0.355028053887817;
    bio=aio/ONOVRT;
    aipo=-0.2588189403792807;
    bipo=-aipo/ONOVRT;
  }
}

Doub Bessel::airt_ai(const Doub x){
  if (x!=xo) airy(x);
  return aio;
}

Doub Bessel::airy_bi(const Doub x){
  if (x!=xo) airy(x);
  return bio;
}

void Bessel::sphbes(const Int n, const Doub x){
  const Doub RTPIO2=1.253314137315500251;
  Doub factor,order;
  if (n<0 || x <= 0.0) throw("bad arguments in sphbes");
  order=n+0.5;
  besseljy(order,x);
  factor=RTPIO2/sqrt(x);
  sphjo=factor*jo;
  sphyo=factor*yo;
  sphjpo=factor*jpo-sphjo/(2.*x);
  sphypo=factor*ypo-sphyo/(2.*x);
  sphno=n;
}

Doub Bessel::sphbesj(const Int n, const Doub x){
  if (n!=sphno || x !=xo) sphbes(n,x);
  return sphjo;
}

Doub Bessel::sphbesy(const Int n, const Doub x){
  if (n!=sphno || x!= xo) sphbes(n,x);
  return sphyo;
}


