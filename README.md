# AG_lm6 1.0.7

AG_lm6 esegue una valutazione Li&Ma il cui output è il valore di significance statistica di una detection.
Per eseguire il software si deve esportare la variabile $PFILES in modo che punti alla cartella /conf

### Utilizzo


### Input:
  
    Output file name
  
    Path to T0.cts
  
    Path to T0.exp
    
    Path to T1.cts
  
    Path to T1.exp
    
    Path to T2.cts 
  
    Path to T2,exp
  
    Galactic longitude of GRB centroid
  
    Galactic latitude of GRB centroid
  
    Li&Ma radius of analysis
    
    normalize (true/false): if true we assert that the exp maps given in input are NOT normalized. ExpRatioEvaluator will perform a normalization of the exp maps.
    
    createExpRatioMap (true/false): if true ExpRatioEvaluator will create the exp-ratio map.
  	
(OPZIONALI) -> è possibile specificare "d" per usare il valore di default
  	
    minThreshold: la soglia minima sotto la quale il pixel è considerato "bad" per il calcolo dell'exp-ratio ( double ) ( default = 120 )
	
	  maxThreshold: la soglia minima sopra la quale il pixel è considerato "bad" per il calcolo dell'exp-ratio ( double ) ( default = 140 )

	  squareSize: la dimensione in pixel del lato della regione (quadrato) su cui si calcola l'exp-ratio ( int ) ( default = 10 )

### Esempio di utilizzo

	./bin/AG_lm6 ../log.txt ../maps/T0.cts ../maps/T0.exp ../maps/T1.cts ../maps/T1.exp ../maps/T2.cts ../maps/T2.exp 45 30 10 true true d 150 d 
 	
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
                    

  

