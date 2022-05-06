datatype temp = C of real | F of real
val t: temp = C 45.0

fun temp_to_f t = 
    case t of
        C x => x * 1.8 + 32.0
    |   F x => x

val new = temp_to_f t

(* ------- *)

fun rgbToTup {b, g, r} = (r, g, b)
val y = {r = 1, b = 2, g = 3}
val p = rgbToTup y
val num  = #r y : int
val printnum = Int.toString(num) ^ "\n"
val _ = print printnum

(* Higher order functions: Functions can take other functions as arguments.
   Functions are just other kinds of values, and functions don't need names
   to exist.  Functions without names are called "anonymous functions" or
   lambda expressions or closures (since they also have a lexical scope). *)