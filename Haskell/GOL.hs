import Data.Array
import qualified Data.Text as T
import Control.Concurrent as C
import System.Environment

data Cell = Alive | Dead 									--Schroedinger's cell?
  deriving (Eq,Show)

type World = Array (Int,Int) Cell 							--The world is a grid of cells

readWorld :: IO ()
readWorld = do
	[f,n] <- getArgs
	w <- readFile f
	let board = makeWorld $ lines w
	let ntimes = read n :: Int
	evolve board ntimes
	return ()

makeWorld :: [String] -> World
makeWorld l = listArray ((1,1),(size,size)) list where
	size = length $ l !! 1									--calculate size of the grid based on first row
	list = concatMap (map g) l 								--convert ' ' and '#' into Alive and Dead
	g '.' = Dead
	g _ = Alive

evolveWorld :: World -> World
evolveWorld w = listArray (bounds w) newWorld where
	size = getSize w
	newWorld = [evolveCell w x y | x <- [1..size], y <- [1..size]]

evolveCell :: World -> Int -> Int -> Cell
evolveCell w x y = cell where
	cell 	| check x y == 1 && (neighbors == 2 || neighbors == 3) = Alive
			| check x y == 0 && neighbors == 3 = Alive
			| otherwise = Dead
	neighbors = sum [check (x + xOff) (y + yOff) |
                    xOff <- [-1, 0, 1], yOff <- [-1, 0, 1],
					not (xOff == 0 && yOff == 0)] 
	check x y 	| x < 1 || x > getSize w = 0
				| y < 1 || y > getSize w = 0
				| w!(x,y) == Alive = 1
				| otherwise = 0

getSize :: World -> Int
getSize w = size where
	b@((_,_),(size,_)) = bounds w

showWorld :: World -> IO ()
showWorld w = putStrLn $ T.unpack $ T.unlines rows where
	rows = T.chunksOf (getSize w) $ T.pack [ print x | x <- (elems w)] 
	print Dead = ' '
	print Alive = '█'

evolve :: World -> Int -> IO ()
evolve w n = mapM_ f $ take n $ iterate evolveWorld w
  where f g = do
        showWorld g
        C.threadDelay 100000

main = readWorld