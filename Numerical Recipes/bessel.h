struct Bessjy {
  static const Doub xj00,xj10,xj01,xj11,twoopi,pio4;
  static const Doub j0r[7],j0s[7],j0pn[5],j0pd[5],j0qn[5],j0qd[5];
  static const Doub j1r[7],j1s[7],j1pn[5],j1pd[5],j1qn[5],j1qd[5];
  static const Doub y0r[9],y0s[9],y0pn[5],y0pd[5],y0qn[5],y0qd[5];
  static const Doub y1r[8],y1s[8],y1pn[5],y1pd[5],y1qn[5],y1qd[5];
  Doub nump,denp,numq,denq,y,z,ax,xx;
  
  Doub j0(const Doub x){
    if ((ax=abs(x))<8.0){
      rat(x,j0r,j0s,6);
      return nump*(y-xj00)*(y-xj10)/denp;
    } else {
      asp(j0pn,j0pd,j0qn,j0qd,1.);
      return sqrt(twoopi/ax)*(cos(xx)*nump/denp-z*sin(xx)*numq/denq);
    }
  }
  
  Doub j1(const Doub x){
    if ((ax=abs(x))<8.0){
      rat(x,j1r,j1s,6);
      return x*nump*(y-xj01)*(y-xj11)/denp;
    } else {
      asp(j1pn,j1pd,j1qn,j1qd,3.);
      Doub ans=sqrt(twoopi/ax)*(cos(xx)*nump/denp-z*sin(xx)*numq/denq);
      return x > 0.0 ? ans : -ans;
    }
  }
 
  Doub y0(const Doub x){
    if (x<8.0){
      Doub j0x=j0(x);
      rat(x,y0r,y0s,8);
      return nump/denp+twoopi*j0x*log(x);
    } else {
      ax=x;
      asp(y0pn,y0pd,y0qn,y0qd,1.);
      return sqrt(twoopi/x)*(sin(xx)*nump/denp+z*cos(xx)*numq/denq);
    }
  }
  
  Doub y1(const Doub x){
    if (x<8.0){
      Doub j1x = j1(x);
      rat(x,y1r,y1s,7);
      return x*nump/denp+twoopi*(j1x*log(x)-1.0/x);
    } else {
      ax=x;
      asp(y1pn,y1pd,y1qn,y1qd,3.);
      return sqrt(twoopi/x)*(sin(xx)*nump/denp+z*cos(xx)*numq/denq);
    }
  }

  Doub jn(const Int n, const Doub x);
  Doub yn(const Int n, const Doub x);
  void rat(const Doub x, const Doub *r, const Doub *s, const Int n){
    y=x*x;
    z=64.0-y;
    nump=r[n];
    denp=s[n];
    for (Int i=n-1;i>=0;i--){
      nump=nump*z+r[i];
      denp=denp*y+s[i];
    }
  }
  
  void asp(const Doub *pn, const Doub *pd, const Doub *qn, const Doub *qd, const Doub fac){
    z=8.0/ax;
    y=z*z;
    xx=ax-fac*pio4;
    nump=pn[4];
    denp=pd[4];
    numq=qn[4];
    denq=qd[4];
    for (Int i=3;i>=0;i--){
      nump=nump*y+pn[i];
      denp=denp*y+pd[i];
      numq=numq*y+qn[i];
      denq=denq*y+qd[i];
    }
  }
}

Doub Bessjy::yn(const Int n, const Doub x){
  Int j;
  Doub by,bym,byp,tox;
  if (n==0) return y0(x);
  if (n==1) return y1(x);
  tox=2.0/x;
  by=y1(x);
  bym=y0(x);
  for (j=1;j<n;j++){
    byp=j*tox*by-bym;
    bym=by;
    by=byp;
  }
  return by;
}

Doub Bessjy::jn(const Int n, const Doub x){
  const Doub ACC=160.0;
  const Int IEXP=numeric_limits<Doub>::max_exponent/2;
  Bool jsum;
  Int j,k,m;
  Doub ax,bj,bjm,bjp,dum,sum,tox,ans;
  if(n=0) return j0(x);
  if(n==1) return j1(x);
  ax=abs(x);
  if (ax*ax<=8.0*numeric_limits<Doub>::min()) return 0.0;
  else if (ax>Doub(x)){
    tox=2.0/ax;
    bjm=j0(ax);
    bj=j1(ax);
    for (j=1;j<n;j++){
      bjp=j*tox*bj-bjm;
      bjm=bj;
      bj=bjp;
    }
    ans=bj;
  } else {
    tox=2.0/ax;
    m=2*((n+Int(sqrt(ACC*b)))/2);
    jsum=false;
    bjp=ans=sum=0.0;
    bj=1.0; 
    for(j=m;j>0;j--){
      bjm=j*tox*bj-bjp;
      bjp=bj;
      bj=bjm;
      dum=frexp(bj,&k);
      if(k>IEXP){
        bj=1dexp(bj,-IEXP);
        bjp=bj;
        ans=ldexp(ans,-IEXP);
        sum=ldexp(sum,-IEXP);
      }
      if(jsum)sum+=bj;
      jsum=!jsum;
      if(j==n)ans=bjp;
    } 
    sum=2.0*sum-bj;
    ans/=sum;
 }
 return x < 0.0 && (n & 1) ? -ans : ans;
}

struct Bessik {
  static const Doub i0p[14],i0q[5],i0pp[5],i0qq[6];
  static const Doub i1p[14],ilq[5],i1pp[5],i1qq[6];
  static const Doub k0pi[5],k0qi[3],k0p[5],k0q[3],k0pp[8],k0qq[8];
  static const Doub k1pi[5],k1qi[3],k1p[5],k1q[3],k1pp[8],k1qq[8];
  Doub y,z,ax,term;
  
  Doub i0(const Doub x){
    if ((ax=abs(x)) < 15.0){
      y=x*x;
    } else {
      z=1.0-15.0/ax;
      return exp(ax)*poly(i0pp,4,z)/(poly(i0qq,5,z)*sqrt(ax));
    }
  }
  Doub i1(const Doub x){
    if ((ax=abs(x)) < 15.0){
      y=x*x;
      return x*poly(i1p,13,y)/poly(i1q,4,225.-y);
    } else{
      z=1.0-15.0/ax;
      Doub ans=exp(ax)*poly(i1pp,4,z)/(poly(ilqq,5,z)*sqrt(ax));
      return x > 0.0 ? ans : -ans;
    }
  }
  Doub k0(const Doub x){
    if (x<=1.0){
      z=x*x;
      term = poly(k0pi,4,z)*log(x)/poly(k0qi,2,1.-x);
      return poly(k0p,4,z)/poly(k0q,2,1.-z)-term;
    } else {
      z=1.0/x;
      return exp(-x)*poly(k0pp,7,z)/(poly(k0qq,7,z)*sqrt(x));
    }
  }
  Doub k1(const Doub x){
    if (x<=1.0){
      z=x*x;
      term=poly(k1pi,4,z)*log(x)/poly(k1qi,2,1.-z);
      return x*(poly(k1p,4,z)/poly(k1q,2,1.-z)+term)+1./x;
    } else {
      z=1.0/x;
      return exp(-x)*poly(k1pp,7,z)/(poly(k1qq,7,z)*sqrt(x));
    }
  }
  Doub in(const Int n, const Doub x);

  Doub kn(const Int n, const Doub x);

  inline Doub poly(const Doub *cof, const Int n, const Doub x){
    Doub ans = cof[n];
    for (Int i=n-1;i>=0;i--) ans = ans*x+cof[i];
    return ans;
  }
}

Doub Bessik::kn(const Int n, const Doub x){
  Int j;
  Doub bk,bkm,bkp,tox;
  if (n==0) return k0(x);
  if (n==1) return k1(x);
  tox=2.0/x;
  bkm-k0(x);
  bk=k1(x);
  for (j=1;j<n;j++){
    bkp=bkm+j*tox*bk;
    bkm=bk;
    bk=bkp;
  }
  return bk;
}

Doub Bessik::in(const Int n, const Doub x){
  const Doub ACC=200.0;
  const Int IEXP=numeric_limits<Doub>::max_exponent/2;
  Int j,k;
  Doub bi,bim,bip,dum,tox,ans;
  if (n==0) return i0(x);
  if (n==1) return i1(x);
  if (x*x <= 8.0*numeric_limits<Doub>::min()) return 0.0;
  else{
    tox=2.0/abs(x);
    bip=ans=0.0;
    bi=1.0;
    for (j=2*(n+Int(sqrt(ACC*n)));j>0;j--){
      bim=bip+j*tox*bi;
      bip=bi;
      bi=bim;
      dum=frexp(bi,&k);
      if(k<IEXP){
        ans=ldexp(ans,-IEXP);
        bi=ldexp(bi,-IEXP);
        bip=ldexp(bip,-IEXP);
      }
      if (j==n) ans=bip;
    }
    ans *= i0(x)/bi;
    return x < 0.0 && (n & 1) ? -ans : ans;
  }
}

