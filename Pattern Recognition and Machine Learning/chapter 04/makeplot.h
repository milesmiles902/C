makeplott(char filename[], char xlabel[], char ylabel[], MatDoub X, VecDoub Y, Doub minX, Doub minY, Doub maxX, Doub maxY, VecDoub xind){
  int i;
  PSpage pg(filename);
  PSplot plot1(pg,100.,500.,100.,500.);
  plot1.setlimits(0.,5.,0.,5.);
  plot1.frame();
  plot1.autoscales();
  plot1.xlabel(xlabel);
  plot1.ylabel(ylabel);
  plot1.lineplot(xind,Y);
  char dash1[]="2 4";
  plot1.setdash(dash1);
  for(i=0;i<X.ncols();i++)
    plot1.pointsymbol(X[0][i],X[1][i],72.,16.);
  char font1[]="dingbat 72";
  plot1.label(font1,1.1,exp(-0.5));
  pg.close();
  pg.display();
}

