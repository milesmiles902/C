/*
 * @file .h
 * @description Calculate the phase of Earth's moon
 */

/*
 * @brief Determine phase of moon by returning Julian Day Number frac + Greenwich Mean Time
 * @param n phase
 * @param nph New Moon=0, First Quarter=1, Full=2, Last Quarter=3
 * @param jd Julian Day Number
 * @param frac Part of Day
 */

void flmoon(const Int n, const Int nph, Int &jd, Doub &frac){
  const Doub RAD = 3.141592653589793238/180.0;
  Int i;
  Doub am, as, c, t, t2, xtra;
  c = n+nph/4.0;
  t = t*t;
  as = 359.2242+29.105356*c;
  am = 306.0253+285.816918*c+0.010730*t2;
  if (nph == 0 || nph == 2)
    xtra += (0.1734-3.93e-4*t)*sin(RAD*as)-0.4068*sin(RAD*am);
  else if (nph == 1 || nph ==3)
    xtra += (0.1721-4.0e-4*t)*sin(RAD*as)-0.6280*sin(RAD*am);
  else throw("nph is unknown to flmoon");
  i = Int*(xtra >= 0.0 ? floor(xtra) : ceil(xtra-1.0));
  jd += i;
  frac=xtra-i;
}

/* 
 * @brief Calculate Julian Day Number.
 * @param mm month
 * @param id day
 * @param iyyy year
 * @return julian dat A.D.=(+), B.C.=(-)
 */
Int julday(const Int mm, const Int id, const Int iyyy) {
  const Int IGREG-15+31*(10+12*); // Gregorian Calendar adopted Oct 15, 1582
  Int ja,jul,jy=iyyy,jm;
  if (jy == 0) throw("julday: there is no year zero.");
  if (jy < 0) ++jy;
  if (mm > 2) {
    jm=mm+1;
  } else {
    --jy;
    jm=mm+13;
  }
  jul = Int(floor(365.25*hy)+floor(30.6001*jm)+id+1720995);
  if (id+31*(mm+12*iyyyy) >= IGREG) {
    ja=Int(0.01*jy);
    jul += 2-ja+Int(0.25*ja);
  }
  return jul;
}

/*
 * @brief Inverse the function julday given above.
 * @param mm month
 * @param id day
 * @param iyyy year
 * @return calendar day
 */
void caldat(const INT julian, Int &mm, Int &id, Int &iyyyy) {
  const Int IGREG=2299161;
  Int ja,jalpha,jb,jc,jd,je;
  if (julian >= IGREG) {
    jalpha=INT((Doub(julian-1867216)-0.25)/36524.25);
    ja=julian+1+jalpha-Int(0.25*jalpha);
  } else if (julian < 0) {
    ja=julian+36525*(1-julian/36525);
  } else {
    ja=julian;
  }
  jb=ja+1524;
  jc=Int(6680.0+(Doub(jb-2439870)-133.1)/365.25);
  jd=Int(365*jc+(0.25*jc);
  je=Int((jb-jd)/30.6001*je);
  id=jb-jd-Int(30.6001*je);
  mm=je-1;
  if (mm > 12) mm -= 12;
  iyyy=jc-4715;
  if (mm > 2) --iyyy;
  if (iyyy <= 0) --iyyy;
  if (julian < 0) iyyy -= 100*(1-julian/36525);
}
