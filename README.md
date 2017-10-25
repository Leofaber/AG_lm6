# AG_lm6 1.0.7

AG_lm6 esegue una valutazione Li&Ma il cui output è il valore di significance statistica di una detection.
Per eseguire il software si deve esportare la variabile $PFILES in modo che punti alla cartella /conf

### Esempio di utilizzo

    ./bin/AG_lm6  log.txt  maps/T0.cts  maps/T0.exp  maps/T1.cts  maps/T1.exp  maps/T2.cts  maps/T2.exp  false  45  30  10  false true  true  d  160  d  

### Input:
  
    Output file name
  
    Path to T0.cts
  
    Path to T0.exp
      
    Path to T1.cts
  
    Path to T1.exp
        
    Path to T2.cts 
  
    Path to T2.exp
    
    Are T0,T1,T2 exp maps already normalized? (true/false)
  
    Galactic longitude of GRB centroid
  
    Galactic latitude of GRB centroid
  
    Li&Ma radius of analysis
    
      	
(OPZIONALI) -> è possibile specificare "d" per usare il valore di default
  	
    binSumOnNormalizedMap: se il valore è true calcola la bin-sum sulle exp normalizzate. (true/false) (default =true)
	
    createExpNormalizedMap : se il valore è true verrà scritta su file le mappe normalizzate per T0,T1 e T2. ( true/false ) ( default = false)
    
    createExpRatioMap: se il valore è "true", verrà scritta su file le mappe exp-ratio per T0,T1 e T2 ovvero quelle mappe in cui il valore di ogni pixel rappresenta il valore della valutazione exp-ratio calcolato sul medesimo pixel. ( true/false ) ( default = false)
    
    minThreshold: la soglia minima sotto la quale il pixel è considerato "bad" per il calcolo dell'exp-ratio ( double ) ( default = 120 )
	
    maxThreshold: la soglia minima sopra la quale il pixel è considerato "bad" per il calcolo dell'exp-ratio ( double ) ( default = 140 )

    squareSize: la dimensione in pixel del lato della regione (quadrato) su cui si calcola l'exp-ratio ( int ) ( default = 10 )

 	
### Output

    1) L'outuput di ExpRatioEvaluator -> https://github.com/Leofaber/ExpRatioEvaluator
    
    2) Un file che riporta i seguenti valori: 

  
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
                    

  

