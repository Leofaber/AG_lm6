# AG_lm6 1.0.5

Se il software non è installato, per eseguirlo si deve entrare nella cartella /bin altrimenti non trova il file .par

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
  * true/false: if true, ExpRatioEvaluator will perform a normalization of the exp maps 
  	
  	(Opzionali)
  	
  * minTreshold (0 di default)
  * maxTreshold (100 di default)    

  Output:                                           Example:
  
  * tstart T0.......................................416529609.0
  * tstop T0........................................416530609.0
  * numero di fotoni T0.............................2.00
  * numero fotoni esposizione T0  (expBinSumT0).....7151.20
  * fotoni/esposizione T0...........................0.0002796734
  * exp-ratio-T0....................................100
    
  * tstart T1.......................................416529609.0
  * tstop T1........................................416530609.0
  * numero di fotoni T1           (ctsBinSumT1).....1.00
  * numero fotoni esposizione T1  (expBinSumT1).....7151.20
  * exp-ratio-T1....................................100
    
  * tstart T2.......................................416529609.0
  * tstop T2........................................416530609.0
  * numero di fotoni T2           (ctsBinSumT2).....1.00
  * numero fotoni esposizione T2  (expBinSumT2).....7151.20
  * exp-ratio-T2.,,,................................100
  
  * alpha = expBinSumT0 / expBgSum..................0.50
  * off = ctsBinSumT1 + ctsBinSumT2.................off 2
  * expBgSum = expBinSumT1 + expBinSumT2............14302.40
  * bkg rate = off / expBgSum.......................0.0001398367
  * sigma di Li&Ma..................................0.6863906633
                    

  

