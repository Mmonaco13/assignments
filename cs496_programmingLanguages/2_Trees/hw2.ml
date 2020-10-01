(* ******************************************* *)
(* Matthew Monaco 
   I pledge my honor that I have abided by the
   Stevens Honor System.                       *)
(* ******************************************* *)

(* Tree Type and Examples ******************** *)
type dTree = Empty | Node of char*dTree*dTree | Leaf of int

let tLeft = Node('w', Node('x', Leaf(2), Leaf(5)), Leaf(8))

let tRight = Node('w', Node('x', Leaf(2), Leaf(5)), Node('y', Leaf(7), Leaf(5)))

(* Additional Tools ************************** *)
let tLeaf = Leaf(2)

let boolParam = ['x';'y';'z']

let boolGraph = [([0;0;0], 0);
                 ([0;0;1], 1);
                 ([0;1;0], 1);
                 ([0;1;1], 0);
                 ([1;0;0], 1);
                 ([1;0;1], 0);
                 ([1;1;0], 0);
                 ([1;1;1], 1)]

(* dTree_height ****************************** *)
let rec dTree_height : dTree -> int = fun tree ->
  match tree with
  |Empty -> failwith "No Tree"
  |Leaf(x) -> 0
  |Node(c, leftTree, rightTree) -> 
   let rHeight = dTree_height rightTree
   in let lHeight = dTree_height leftTree
   in if lHeight > rHeight
   then 1 + lHeight
   else 1 + rHeight

(* dTree_size ******************************** *)
let rec dTree_size : dTree -> int = fun tree ->
  match tree with
  |Empty -> failwith "No Tree"
  |Leaf(x) -> 1
  |Node(c, leftTree, rightTree) ->
   1 + (dTree_size leftTree) + (dTree_size rightTree)

(* dTree_paths ******************************* *)
let rec pathHelp : dTree -> int list -> int list list = fun tree curPath ->
  match tree with
  |Empty -> failwith "No Tree"
  |Leaf(x) -> [curPath]
  |Node(c, leftTree, rightTree) ->
   List.append (pathHelp leftTree (List.append curPath [0])) 
   (pathHelp rightTree (List.append curPath [1]))

let rec dTree_paths : dTree -> int list list = fun tree ->
  pathHelp tree []

(* dTree_is_perfect ************************** *)
let rec perfectHelp : int list list -> bool = fun pathList ->
  match pathList with
  |[] -> failwith "No Tree"
  |[x] -> true
  |x::y::xs ->
   if (List.length x) = (List.length y)
   then perfectHelp (y::xs)
   else false

let rec dTree_is_perfect : dTree -> bool = fun tree ->
  perfectHelp (dTree_paths tree)

(* dTree_map ********************************* *)
let rec dTree_map : (char -> char) -> (int -> int) -> dTree -> dTree = fun f g t ->
  match t with
  |Empty -> failwith "No Tree"
  |Leaf(x) -> Leaf((g x))
  |Node(c, leftTree, rightTree) ->
   Node((f c), (dTree_map f g leftTree), (dTree_map f g rightTree))

(* list_to_tree ****************************** *)
let rec list_to_tree : char list -> dTree = fun charList ->
  match charList with
  |[] -> Leaf(0)
  |x::xs ->
   Node(x, (list_to_tree xs), (list_to_tree xs))

(* replace_leaf_at *************************** *)
let rec replaceHelp : dTree -> int list -> int -> dTree = fun t path n ->
  match t with
  |Empty -> failwith "No Tree"
  |Leaf(x) -> Leaf(n)
  |Node(c, lt, rt) ->
    match path with
    |[] -> failwith "Invalid Path"
    |x::xs ->
     if x = 0
     then Node(c, (replaceHelp lt xs n), rt)
     else Node(c, lt, (replaceHelp rt xs n))

let rec replace_leaf_at : dTree -> (int list * int) list -> dTree = fun t g ->
  match g with
  |[] -> t
  |(path, n)::tl -> replace_leaf_at (replaceHelp t path n) tl

(* bt_to_dTree ******************************* *)
let rec bf_to_dTree : ((char list)*((int list*int) list)) -> dTree = fun pe ->
  let (param,graph) = pe
  in replace_leaf_at (list_to_tree param) graph 
