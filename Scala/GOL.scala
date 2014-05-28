import Array._
import util.control.Breaks._

class World(seed: List[(Int, Int)], size: Int) {
	private val board = ofDim[Boolean](size, size)
	seed foreach (cell => makeCell(cell._1, cell._2))
 
	def evolve = {
		val newWorld = new World(Nil, size)
		for (x <- (0 to size-1); y <- (0 to size-1)){
			if (isAlive(x, y) && neighbors(x, y) == 2 || neighbors(x, y) == 3)
				newWorld.board(x)(y) = true
			if (!isAlive(x, y) && neighbors(x, y) == 3) 
				newWorld.board(x)(y) = true
		}
		newWorld
	}
  
	private def neighbors(x: Int, y: Int): Int = {
		var total = 0
		for(i <- (x - 1 to x + 1); j <- (y - 1 to y + 1)){
			if(i < 0 || i >= size || j < 0 || j >= size || (i == x && y == j)){}
			else if (isAlive(i,j)) total += 1
		}
		return total
	}
		  
	private def isAlive(x: Int, y: Int): Boolean =
	board(x)(y)
 
	private def makeCell(x: Int, y: Int) =
	board(x)(y) = true
  
	private def readCell(cell: String): Boolean = cell match {
		case "#" => true
		case _ => false
	}
	
	def showWorld = {
		var s = ""
		for(i <- (0 to size-1)) {
			for(j <- (0 to size-1)){
				if(board(i)(j)) s += "@"
				else s += " "
			}
			s += "\n"
		}
		print(s)
		println
	}
}

object Main extends App {
	val fileContent = io.Source.fromFile(args(0)).mkString
	val stringArray = fileContent.split("\n")
	val size = stringArray(0).length
	var worldList = (1,1)::Nil
	worldList = Nil
	for (i <- (0 to size-2))
		for(j <- (0 to size-2))
			if(stringArray(i)(j) == '#') 
				worldList = (i,j)::worldList 
	print(worldList);
	var world = new World(worldList, size)
	world.showWorld
	for (x <- 1 to getValue(args(1))){
		world = world.evolve
		Thread.sleep(100)
		world.showWorld
	}
	def getValue(s: String): Int = s match {
		case Int(x) => x
		case _ => sys.error("ERROR: arg(1) is not a number")
	}
}

object Int {
	def unapply(s : String) : Option[Int] = try {
		Some(s.toInt)
	} catch {
		case _ : java.lang.NumberFormatException => None
	}
}
