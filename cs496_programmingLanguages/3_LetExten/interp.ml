(***********************************************************************)
(* Matthew Monaco
   I pledge my honor that I have abided by the Stevens Honor System    *)
(***********************************************************************)
open Ast
open Ds

let rec eval (en:env) (e:expr):exp_val =
  match e with
  | Int n           -> NumVal n
  | Var x           -> lookup en x
  | Let(x, e1, e2)  ->
    let v1 = eval en e1  in
    eval (extend_env en x v1) e2
  | IsZero(e1)      ->
    let v1 = eval en e1  in
    let n1 = numVal_to_num v1 in
    BoolVal (n1 = 0)
  | ITE(e1, e2, e3) ->
    let v1 = eval en e1  in
    let b1 = boolVal_to_bool v1 in
    if b1 then eval en e2 else eval en e3
  | Sub(e1, e2)     ->
    let v1 = eval en e1 in
    let v2 = eval en e2  in
    NumVal ((numVal_to_num v1) - (numVal_to_num v2))
  | Add(e1, e2) ->
    let v1 = eval en e1 in
    let v2 = eval en e2  in
    NumVal ((numVal_to_num v1) + (numVal_to_num v2))
  | Div(e1, e2) ->
    let v1 = eval en e1 in
    let v2 = eval en e2  in
    NumVal ((numVal_to_num v1) / (numVal_to_num v2))
  | Mul(e1, e2) ->
    let v1 = eval en e1 in
    let v2 = eval en e2  in
    NumVal ((numVal_to_num v1) * (numVal_to_num v2))
  | Abs(e1) ->
    let n1 = eval en e1 in
    (match n1 with
    | NumVal(n) ->
      if n > 0
      then NumVal n
      else NumVal (-1 * n)
    | _ -> failwith("Expected a Num"))
  | Cons(e1, e2) ->
    let n1 = eval en e1 in
    let n2 = eval en e2 in
    (match n2 with
    | ListVal(n) -> ListVal(n1::n)
    | _ -> failwith("Expected a List"))
  | Hd(e1) ->
    let n1 = eval en e1 in
    (match n1 with
    | ListVal(n) -> List.hd n
    | _ -> failwith("Expected a List"))
  | Tl(e1) ->
    let n1 = eval en e1 in
    (match n1 with
    | ListVal(n) -> ListVal(List.tl n)
    | _ -> failwith("Expected a List"))
  | Empty(e1) -> (* supports both lists and trees *)
    let n1 = eval en e1 in
    (match n1 with
    | ListVal(n) ->
      if n = []
      then BoolVal true
      else BoolVal false
    | TreeVal(t) ->
      if t = Empty
      then BoolVal true
      else BoolVal false
    | _ -> failwith("Expected a List or Tree"))
  | EmptyList -> ListVal []
  | EmptyTree -> TreeVal Empty
  | Node(e1,lt,rt) ->
    let n1 = eval en e1 in
    let ltr = eval en lt in
    let rtr = eval en rt in
    (match ltr,rtr with
    | TreeVal(l),TreeVal(r) -> TreeVal (Node(n1,l,r))
    | _ -> failwith("Expected a Tree"))
  | CaseT(target,emptycase,id_e,id_lt,id_rt,nodecase) ->
    let e1 = eval en target in
    (match e1 with
    | TreeVal(Empty) -> eval en emptycase
    | TreeVal(Node(ev1,ev2,ev3)) ->
      let nEnv =
      (extend_env
        (extend_env
          (extend_env en id_e ev1)
        id_lt (TreeVal ev2))
      id_rt (TreeVal ev3)) in
      eval nEnv nodecase
    | _ -> failwith("Expected a Tree"))


(***********************************************************************)
(* Everything above this is essentially the same as we saw in lecture. *)
(***********************************************************************)

(* Parse a string into an ast *)
let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast


(* Interpret an expression *)
let interp (e:string):exp_val =
  e |> parse |> eval (empty_env ())
