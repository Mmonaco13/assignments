(* ******************************************** *)
(* Matthew Monaco CS 496 *)
(* I pledge my honor that I have abided by the
   Stevens Honor System. *)
(* ******************************************** *)

(* ******************************************** *)
(** Basic functions on finite automata *)
(* ******************************************** *)
(**
   Code stub for assignment 1
*)

type symbol = char
type input = char list

type state = string

(* transition function *)
type tf = (state * symbol * state) list

(* initial state * transition function * end state *)
type fa = { states: state list; start:state; tf: tf; final: state list}


(* ******************************************** *)
(* Examples of automata *)
(* ******************************************** *)

(*Valid*)
let a = {states = ["q0";"q1";"q2"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2"]}

(*InValid, q3, q4, q5 unreachable*)
let a2 = {states = ["q0";"q1";"q2";"q3";"q4";"q5"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q1")];
          final= ["q2";"q5"]
         }

(*Undeterministic*)
let a3 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [ ("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")
               ; ("q1",'c',"q3")];
          final= ["q2"]
         }
         
(*Missing Start State*)
let a4 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q5";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2"]
         }
         
(*Missing Final State*)
let a5 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q5"]
         }
         
(*Missing Second Final State*)
let a6 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2";"q5"]
         }

let tf_of_a = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")]



(* ******************************************** *)
(* Helper functions *)
(* ******************************************** *)

let input_of_string s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []


(* ******************************************** *)
(* Simulating automata *)
(* ******************************************** *)

let rec map : ('a -> 'b) -> 'a list -> 'b list = fun f xs ->
  match xs with
  | [] -> []
  | (x::xs) -> (f x)::(map f xs)

(* Apply Transition Function ****************** *)
let rec apply_transition_function : tf -> state -> symbol -> state option = fun ys o s ->
  match ys with
  | [] -> None
  | (orig, sym, dest)::xs ->
    if orig <> o
    then apply_transition_function xs o s
    else if sym = s
    then Some dest
    else apply_transition_function xs o s

(* Accept ************************************* *)
let rec filter orig = 
  match orig with
  |None -> "none"
  |Some x -> x

let rec acceptHelp : input -> state -> tf -> state list -> bool = fun inpStr curState tran fin ->
  match inpStr with
  |[] ->
    if List.mem curState fin
    then true
    else false
  |inp::tl ->
    if apply_transition_function tran curState inp = None
    then false
    else acceptHelp tl (filter (apply_transition_function tran curState inp)) tran fin

let rec accept : fa -> input -> bool = fun dfa inString ->
  match dfa with
  |{states: state list; start:state; tf: tf; final: state list} ->
    acceptHelp inString start tf final

(* Deterministic ****************************** *)
let rec comp : state -> symbol -> tf -> bool = fun state1 sym1 tl ->
  match tl with
  |[] -> true
  |(state2,sym2,state3)::xs ->
    if state1 <> state2
    then comp state1 sym1 xs
    else if sym1 = sym2
    then false
    else comp state1 sym1 xs

let rec deterHelp : tf -> bool = fun tranFunc ->
  match tranFunc with
  |[] -> true
  |[x] -> true
  |(curState,sym,nextState)::tl -> 
    if (comp curState sym tl)
    then deterHelp tl
    else false

let rec deterministic : fa -> bool = fun dfa ->
  match dfa with
  |{states: state list; start:state; tf: tf; final: state list} ->
    deterHelp tf

(* Valid ************************************* *)
let rec finValid : state list -> state list -> bool = fun finStates allStates ->
  match finStates with
  |[] -> true
  |x::xs ->
    if (List.mem x allStates)
    then finValid xs allStates
    else false

let rec valid: fa -> bool = fun dfa ->
  match dfa with
  |{states:state list; start:state; tf:tf; final:state list} 
    when (List.mem start states) = false -> false
  |{states:state list; start:state; tf:tf; final:state list}
    when (deterministic dfa) = false -> false
  |{states:state list; start:state; tf:tf; final:state list} ->   finValid final states

(* Reachable ********************************* *)
let rec updateTF : state -> state list -> tf -> tf = fun start badStates origTF ->
  match origTF with
  |[] -> []
  |(orig, sym, next)::xs when orig = start ->
    updateTF start (next::badStates) xs
  |(orig, sym, next)::xs when (List.mem orig badStates) ->
   if (List.mem next badStates)
   then updateTF start badStates xs
   else (start, sym, next)::(updateTF start badStates xs)
  |x::xs -> x::(updateTF start badStates xs)

let rec outStates : state -> tf -> state list = fun start tranFunc ->
  match tranFunc with
  |[] -> []
  |(orig, sym, next)::tl ->
    if start = orig
    then next::outStates start tl
    else outStates start tl

let rec convert : state -> state list -> tf -> state list = fun start badStates tranFunc ->
 match badStates with
 |[start] -> [start]
 |_ when badStates = 
   (List.append badStates (outStates start (updateTF start badStates tranFunc))) 
   -> badStates
 |_ -> convert start (List.append badStates (outStates start (updateTF start badStates tranFunc))) 
  (updateTF start badStates tranFunc) 

let rec reachable : fa -> state list = fun dfa ->
  match dfa with
  |{states:state list; start:state; tf:tf; final:state list} ->
    convert start (start::(outStates start tf)) tf 

(* Remove Dead States ************************ *)
let rec cleanTF : tf -> state list -> tf = fun oldTF goodStates ->
  match oldTF with
  |[] -> []
  |(orig, sym, dest)::tl ->
    if (List.mem orig goodStates) = false 
    then cleanTF tl goodStates
    else if (List.mem dest goodStates)
    then (orig, sym, dest)::cleanTF tl goodStates
    else cleanTF tl goodStates

let rec clean : state list -> state list -> state list = fun old goodStates ->
  match old with
  |[] -> []
  |x::xs -> 
    if (List.mem x goodStates)
    then x::clean xs goodStates
    else clean xs goodStates  

let rdsHelp : fa -> state list -> fa = fun dfa goodStates ->
  match dfa with
  |{states:state list; start:state; tf:tf; final:state list} ->
    {states = (clean states goodStates); start=start; tf = (cleanTF tf goodStates); final = (clean final goodStates)}

let rec remove_dead_states : fa -> fa = fun dfa ->
 match dfa with
 |{states:state list; start:state; tf:tf; final:state list} ->
   rdsHelp dfa (reachable dfa)
