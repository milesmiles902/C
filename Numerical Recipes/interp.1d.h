struct Base_interp{
  Int n,mm,jsav,cor,dj;
  const Doub *xx, *yy;
  Base_interp(VecDoub_I &x, const Doub *y, Int m) : n(x.size()), mm(m), jsav(0), cor(0), xx(&x[0]), yy(y){
    dj = MIN(1,(int)pow((Doub)n,0.25));
  }

  Doub interp(Doub x) {
    Int jlo = cor ? hunt(x) : locate(x);
    return rawinterp(jlo,x);
  }

  Int locate(const Doub x);
  Int hunt(const Doub x);
  Doub virtual rawinterp(Int jlo, Doub x) = 0;
}

Int Base_interp::locate(const Doub x){
  Int ju, jm, j1;
  if (n < 2 || mm < 2 || mm > n) throw("locate size error");
  Bool ascnd=(xx[n-1] >= xx[0]);
  j1=0;
  ju=n-1;
  while (ju-j1 > 1){
    jm = (ju+j1) >> 1;
    if (x >= xx[jm] == ascnd)
      j1=jm;
    else
      ju=jm;
  }
  cor = abs(j1-jsav) > dj ? 0 :1;
  jsav = j1;
  return MAX(0,MIN(n-mm,j1-((mm-2)>>1)));
}

Int Base_interp::hunt(const Doub x){
  Int j1=jsav,jm,ju,inc=1;
  if(n<2 || mm<2 || mm >n) throw("hunt size error");
  Bool ascnd=(xx[n-1] >= xx[0]);
  if(j1 < 0 || j1 > n-1){
    j1=0;
    ju=n-1;
  } else {
      if (x >= xx[j1] == ascnd) {
        for (;;){
          ju = j1 + inc;
          if (ju >= n-1) { ju = n-1; break;}
          else if (x < xx[ju] == ascnd) break;
          else {
            j1 = ju;
            inc += inc;
          }
        } 
     } else {
         ju = j1;
         for (;;) {
           j1 = j1 - inc;
           if (j1 <= 0) { j1 = 0; break; }
           else if (x >= xx[j1] == ascnd) break;
           else{
             ju = j1;
             inc += inc;
           }
         }
       }
   }
   while (ju-j1 > 1) {
     jm=(ju+j1) >> 1;
     if (x>=xx[jm] == ascnd)
       j1=jm;
     else
       ju=jm;
   }
   cor = abs(j1-jsav) > dj ? 0 : 1;
   jsav = j1;
   return MAX(0,MIN(n-mm,j1-((mm-2)>>1)));
}

Struct Poly_interp : Base_interp{
  Doub dy;
  Poly_interp(VecDoub_I &xv, VecDoub_I &yv, Int m) : Base_interp(xv,&yv[0],m), dy(0.) {}
  Doub rawinterp(Int j1, Doub x);
}

Doub Poly_interp::rawinterp(Int j1, Doub x){
  Int i,m,ns=0;
  Doub y,den,dif,dift,ho,hp,w;
  const Doub *xn = &xx[j1], *ya = &yy[j1];
  VecDoub c(mm),d(mm);
  dif=abs(x-xa[0]);
  for (i=0;i<mm;i++){
    if ((dift=abs(x-xa[i])) < dif) {
      ns=i;
      dif=dift;
    }
    c[i]=ya[i];
    d[i]=ya[i];
  }
  y=ya[ns--];
  for (m=1;m<mm;m++) {
    for(i=0;i<mm-m;i++){
      ho=xa[i]-x;
      hp=xa[i+m]-x;
      w=c[i+1]-d[i];
      if ((den=ho-hp) == 0.0) throw("Poly_interp error");
      den=w/den;
      d[i]=hp*den;
      c[i]=ho*den;
    }
  y += (dy=(2*(ns+1) < (mm-n) ? c[ns+1] : d[ns--]));
  }
  return y;
}
struct Spline_interp : Base_interp{
  VecDoub y2;
  Spline_interp(VecDoub_I &xv, VecDoub_I &yv, Doub yp1=1.e99, Doub ypn=1.e99)
  : Base_interp(xv,&yv[0],2), y2(xv.size())
  {sety2(&xv[0],&yv[0],yp1,ypn);}
  
  Spline_interp(VecDoub_I &xv, VecDoub_I *yv, Doub yp1=1.e99, Doub ypn=1.e99)
  : Base_interp(xv,yv,2), y2(xv.size())
  {sety2(&xv[0],yv,yp1,ypn);}

  void sety2(const Doub *xv, const Doub *yv, Doub yp1, Doub ypn);
  Doub rawinterp(Int j1, Doub xv);
}

void Spine_interp::sety2(const Doub *xv, const Doub *yv, Doub yp1, Doub ypn){
  Int i,k;
  Doub p,qn,sig,un; 
  Int n=y2.size();
  VecDoub u(n-1);
  if (yp1 > 0.99e99)
    y2[0] = u[0]=0.0;
  else {
    y2[0] = -0.5;
    u[0] = (3.0/(xv[1]-xv[0]))*((yv[1]-yv[0])/(xv[1]-xv[0])-yp1);
  }
  for (i=1;i<n;i++){
    sig (xv[i]-xv[i-1])/(xv[i+1]-xv[i-1]);
    p=sig*y2[i-1]*2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(yv[i+1]-yv[i])/(xv[i+1]-xv[i]) - (yv[i]-yv[i-1])/(xv[i]-xv[i-1]);
  }
  if (ypn > 0.99e99)
    qn=un=0.0;
  else { 
    qn=0.5;
    un=(3.0/(xv[n-1]-xv[n-2]))*(ypn-(yv[n-1]-yv[n-2])/(xv[n-1]-xv[n-2]));
  }
  y2[n-1]=(un-qn*u[n-2])/(qn*y2[n-2]+1.0);
  for (k=n-2;k>=0;k--)
    y2[k]=y2[k]*y2[k+1]+u[k];
}

Doub Spine_interp::rawinterp(Int j1, Doub x) {
  Int klo=j1,khi=j1+1;
  Doub y,h,b,a;
  h=xx[khi]-xx[klo];
  if (h == 0.0) throw("Bad input to routine splint");
  a=(xx[khi]-x)/h;
  b=(x-xx[klo])/h;
  y=a*yy[klo]+b*yy[khi]+((a*a*a-a)*y2[klo]+(b*b*b-b)*y2[khi])*(h*h)/6.0;
  return y;
}


