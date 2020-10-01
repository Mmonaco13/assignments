barrier(0,N,[]) ->
    barrier(N,N,[]);
barrier(0,N,[H|T]) ->
    H!{self(), ok},
    barrier(0,N,T);
barrier(M,N,L) ->
    receive
        {P,reached} ->
            barrier(M-1,N,lists:append(L, [P]))
    end.
    
pass_barrier(B) ->
    B!self(),reached,
    receive
        {B,ok} ->
            ok
    end.

client(B, Letter, Number) ->
    io:format("~p ~q ~n",[self(),Letter]),
    pass_barrier(B),
    io:format("~p ~q ~n",[self(),Number]),
    %%pass_barrier(B),
    %%client(B,Letter,Number).
    
start() ->
    B = spawn(?MODULE, barrier, [N,N,[]]),
    spawn(?MODULE,client,[B,"a",1]),
    spawn(?MODULE,client,[B,"b",2]),
    spawn(?MODULE,client,[B,"c",3]),
    
    
    
%%producers/consumers
buffer(Size, Producers, Consumers, Max) ->
    receive
        {From,startProduce} when Size+Producers<Max->
            {self(),ok},
            buffer(Size,Producers+1, Consumers, Max)

producer(B) ->
    B!{self(), startProduce},
    receive{B,ok} ->
            %%produce
            B!{self(),endProduce}
    end.

consumer(B) ->
    B!{self(), startConsume},
    receive{B,ok} ->
            %%consume
            B!{self(),endConsume}
    end.

start(NP,NC,Size) ->
    B = spawn(?MODULE,buffer,[0,0,0,Size]),
    [producer(B) || _ <- lists:seq(1,NP)],
    [consumer(B) || _ <- lists:seq(1,NC)].