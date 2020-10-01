-module(hello_world).
-compile(export_all).


hello() ->
    io:format("hello matthew~n").

say_hello() ->
	io:format("hello again~n").

mkLeaf(N) ->
	{node, N, {empty}, {empty}}.

aTree() ->
	{node, 7, mkLeaf(2), {node, 9, mkLeaf(8),{empty}}}.

foldT(_F,A,{empty}) ->
	A;
foldT(F,A,{node,D,LT,RT}) ->
	F(D,foldT(F,A,LT),foldT(F,A,RT)).

test() ->
	foldT(fun (X,AL,AR) -> [X|AL++AR] end, [], aTree()).

is_empty({empty}) ->
    true;
is_empty({node,_,_,_}) ->
    false.