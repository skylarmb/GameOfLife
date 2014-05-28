Total time spent on development: 35 hours

Tested on the following. We do not guarantee it will work on your OS or machine. 
	
	Haskell: Windows 8 with GHCi 7.6.3 and modules installed via Cabal
	
	C: UCSC Unix server and provided GCC compiler
	
	Scala: Windows 8 with Scala 1.10.3
	
	
Usage: 	pentomino.txt is an example world provided for your testing.
		Feel free to modify it to create new world seeds as long as
		you keep the line length and number of lines the same. 
	
	Haskell:	> ghc -O2 GOL.hs
				> GOL.exe "pentomino.txt" 500

	C:			> gcc -std=c99 -o GOL GOL.c
				> ./GOL pentomino.txt 500
				
	Scala		> scalac -optimise GOL.scala
				> scala Main pentomino.txt 500
				
