#include "nr3.h"
#include <cmath>
#include "psplot.h"
#include <string>

void psplot_example(){
  VecDoub x1(500),x2(500),y1(500),y2(500),y3(500),y4(500);
  for(Int i=0;i<500;i++){
    x1[i]=5.*i/499;
    y1[i]=exp(-0.5*x1[i]);
    y2[i]=exp(-0.5*SQR(x1[i]));
    y3[i]=exp(-0.5*sqrt(5.-x1[i]));
    x2[i]=cos(0.062957*i);
    y4[i]=sin(0.088141*i);
  }
  char page[] = "d:\\nr3\\newchap20\\myplot.ps";
  PSpage pg(page);
  PSplot plot1(pg,100.,500.,100.,500.);
  plot1.setlimits(0.,5.,0.,1.);
  plot1.frame();
  plot1.autoscales();
  char xaxis[] = "abscissa";
  plot1.xlabel(xaxis);
  char yaxis[] = "ordinate";
  plot1.ylabel(yaxis);
  plot1.lineplot(x1,y1);
  char dash1[]="2 4";
  plot1.setdash(dash1);
  plot1.lineplot(x1,y2);
  char dash2[]="6 2 4 2";
  plot1.setdash(dash2);
  plot1.lineplot(x1,y3);
  char dash3[]="";
  plot1.setdash(dash3);
  plot1.pointsymbol(1.,exp(-0.5),72,16.);
  plot1.pointsymbol(2.,exp(-1.),108,12.);
  plot1.pointsymbol(2.,exp(-2.),115,12.);
  char font1[]="dingbat 72";
  plot1.label(font1,1.1,exp(-0.5));
  char font2[]="dingbat 108";
  plot1.label(font2,2.1,exp(-1.));
  char font3[]="dingbat 115";
  plot1.label(font3,2.1,exp(-2.));
  
  PSplot plot2(pg,325.,475.,325.,475.);
  plot2.clear();
  plot2.setlimits(-1.2,1.2,-1.2,1.2);
  plot2.frame();
  plot2.scales(1.,0.5,1.,0.5);
  plot2.lineplot(x2,y4);
 
  pg.close();
  pg.display();
}

int main(){
  psplot_example();
}
