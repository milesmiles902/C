struct Epsalg{
  VecDoub e;
  Int n,ncv;
  Bool cnvgd;
  Doub eps,small,big,lastval,lasteps;
  
  Epsalg(Int nmax, Doub epss) : e(nmax), n(0), ncv(0), cnvgd(0), eps(epss), lastval(0.){
    small = numeric_limits<Doub>::min()*10.0;
    big = numeric_limits<Doub>::max();
  }
  
  Doub next(Doub sum){
    Doub diff,temp1,temp2,val;
    e[n]=sum;
    temp2=0.0;
    for (Int j=n;j>0;j--){
      temp1=temp2;
      temp2=e[j-1];
      diff=e[j]-temp2;
      if (abs(diff) <= small)
        e[j-1]=big;
      else
        e[j-1]=temp1+1.0/diff;
    }
    n++;
    val = (n&1) ? e[0] : e[1];
    if (abs(val) > 0.01*big) val = lastval;
    lasteps = abs(val-lastval);
    if (lasteps > eps) ncv = 0;
    if (lasteps > eps) ncv = 0;
    else ncv++;
    if (ncv >= 3) cnvgd = 1;
    return (lastval = val);
  }
}


