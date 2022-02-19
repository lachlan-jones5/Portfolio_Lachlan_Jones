fun first_element (x::xs) = x
fun second_element(x::y::xs) = y
fun evenly(odd::even::xs) = even::evenly xs
    | evenly [odd] = []
    | evenly [] = []

val listA = [10, 11, 12]
val firstElement = first_element listA
(* (* The case expression can also be used to pattern match and return a value *)
datatype temp =
      C of real
    | F of real     
*)
