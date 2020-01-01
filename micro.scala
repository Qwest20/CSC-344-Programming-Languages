import scala.util.matching.Regex

  // Unambiguous grammar
  // E -> T + E | T
  // T -> Const | Var

  // Easier to parse grammar
  // S -> E$
  // E -> Terminal E2
  // E2 -> + E
  // E2 -> NIL
  // Terminal -> Const
  // Terminal -> Val

  //Microproject grammar
  //S -: E$
  //E -: T E2
  //E2 -: + E
  //E2 -: NIL
  //Terminal -: Const
  //Terminal -: Val
  //AND THESE NEW ELEMENTS!
  //T -: Terminal T2
  //T2 -: * T
  //T2 -: NIL

  //S (input) class
  //We define S as abstract, because we don't know what S will be when the program is finished
  //We define other classes as case classes, because we know exactly what type of output they'll have
  abstract class S {
    def eval(env: Main.Environment): Int
  }

  //Terminal class
  //this is defined as abstract, because we don't know if a terminal will output a var or a const.
  abstract class Terminal extends S {
    def eval(env: Main.Environment): Int
  }

  //E Case class, which holds 2 parameters
  //Updated version checks to see if the left is of type T and applies the eval accordingly
  //This is a case class, because we know that an E will have a T and an optional E2.
  case class E(l: T, right: Option[E2]) extends S {
    def eval(env: Main.Environment): Int = {
      val a1: Int = l match {
        case t:T => t.eval(env)
      }
      right match {
        case Some(r) => a1 + r.eval(env)
        case None => a1
      }
    }
  }

  //T Case class, which holds 2 parameters
  //Updated version now treats T as if it were E in the original program, but reads a T2 instead of an E2
  //In addition, T2 will multiply instead of add when going deeper into the tree
  //T is a case class, because we know that it will have a Terminal and an optional T2
  case class T(l: Terminal, right: Option[T2]) extends S {
    def eval(env: Main.Environment): Int = {
      val a1: Int = l match {
        case v:Var => v.eval(env)
        case c:Const => c.eval(env)
      }
      right match {
        case Some(r) => a1 * r.eval(env)
        case None => a1
      }
    }
  }

  //E2 Case class
  //We know this is a case class, because we can say for certain that this will result us with a "+E"
  case class E2(l: E) extends S {
    def eval(env: Main.Environment): Int = l.eval(env)
  }
  //Var Case class
  //We know this is a case class, because we can say for certain that this will result us with a variable
  case class Var(n: String) extends Terminal {
    def eval(env: Main.Environment): Int = env(n)
  }
  //Const Case class
  //We know this is a case class, because we can say for certain that this will result us with a constant
  case class Const(v: Int) extends Terminal {
    def eval(env: Main.Environment): Int = v
  }
  //T2 Case class
  //Updated version works just like E2, but evaluates a T instead of an E
  //We know this is a case class, because we can say for certain that this will result us with a "*T"
  case class T2(l: T) extends S {
    def eval(env: Main.Environment): Int = l.eval(env)
  }

  class RecursiveDescent(input:String) {

    //values that represent possible variables and constants
    val constregex: Regex = "^[0-9]+".r
    val varregex: Regex = "^[A-Za-z]+".r

    //index in the expression
    var index = 0

    //parse the input
    def parseS(): S = parseE()

    //parse the expression from a T and an E2
    def parseE(): E = E(parseT(), parseE2())

    //parse the E2 to give us another E or NIL
    def parseE2(): Option[E2] = {
      if (index < input.length && input(index) == '+'){
        index+=1; // Advance past +
        Some(E2(parseE()))
      }
      else None
    }

    //parse the terminal
    def parseTerminal(): Terminal = {
      // Get the unparsed part of the string.
      val currStr = input.substring(index)

      // Get either the const or var which is there.
      val consts = constregex.findAllIn(currStr)
      if (consts.hasNext){
        //if this is a constant
        //set a temporary string to store the value
        val const: String = consts.next()
        //bump the index
        index += const.length()
        //set the const for returning
        Const(const.toInt)
      }
      else {
        //if this is a variable, first look for variables instead
        val vars = varregex.findAllIn(currStr)
        //set a temporary string to store the value
        val varname = vars.next()
        //bump the index
        index += varname.length()
        //set the var for returning
        Var(varname)
      }
    }

    //Updated version: Will parse a Terminal on the left and a T2 on the right
    //Works just like E, but with a T2 on the right
    def parseT(): T = T(parseTerminal(), parseT2())

    //Updated version: Will parse an optionally existing T2
    //Works just like E2, but with multiplication instead of addition
    def parseT2(): Option[T2]={
      if (index < input.length && input(index) == '*'){
        index+=1; // Advance past *
        Some(T2(parseT()))
      }
      else None
    }
  }

  object Main {
    //An environment is a sort of expression that is (in this case) inserted in order to express a variable becoming a value!
    //It's like a map (sort of. Maybe more of an abstract map...)!
    //This basically says, when this environment is called, make a string into a specified int!
    type Environment = String => Int

    def main(args: Array[String]){
      //Here, we define our environment
      val env: Environment = { case "x" => 5 case "y" => 7 }

      //EXAMPLES TO CALL
      //addition example
      val additionRD = new RecursiveDescent("5+6+7+y")
      //multiplication example
      val multiplicationRD = new RecursiveDescent("y*7")

      //parse the expressions
      val addExpRD :S = additionRD.parseE()
      val multExpRD :S = multiplicationRD.parseE()

      //print the results
      println("addExpRD")
      println(addExpRD)
//      println("addExpRD.eval(env)")
//      println(addExpRD.eval(env))
      println("multExpRD")
      println(multExpRD)
//      println("multExpRD.eval(env)")
//      println(multExpRD.eval(env))
    }
  }