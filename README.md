# AG_lm6 1.0.1

Per eseguire il programma si deve entrare nella cartella /bin e chiamare l'eseguibile altrimenti non trova il file .par

  Input:
  * Output file name
  * Path to T0.cts
  * Path to T0.exp
  * Path to T1.cts
  * Path to T1.exp
  * Path to T2.cts 
  * Path to T2,exp
  * Galactic longitude of GRB centroid
  * Galactic latitude of GRB centroid
  * Li&Ma radius of analysis   

  Output:                                           Example:
  
  * tstart T0.......................................416529609.0
  * tstop T0........................................416530609.0
  * numero di fotoni T0.............................2.00
  * numero fotoni esposizione T0  (expBinSumT0).....7151.20
  * fotoni/esposizione T0...........................0.0002796734
  
  * tstart T1.......................................416529609.0
  * tstop T1........................................416530609.0
  * numero di fotoni T1           (ctsBinSumT1).....1.00
  * numero fotoni esposizione T1  (expBinSumT1).....7151.20
  
  * tstart T2.......................................416529609.0
  * tstop T2........................................416530609.0
  * numero di fotoni T2           (ctsBinSumT2).....1.00
  * numero fotoni esposizione T2  (expBinSumT2).....7151.20
  
  * alpha = expBinSumT0 / expBgSum..................0.50
  * off = ctsBinSumT1 + ctsBinSumT2.................off 2
  * expBgSum = expBinSumT1 + expBinSumT2............14302.40
  * bkg rate = off / expBgSum.......................0.0001398367
  * sigma di Li&Ma..................................0.6863906633
                    

  

