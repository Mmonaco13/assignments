-module(server).

-export([start_server/0]).

-include_lib("./defs.hrl").

-spec start_server() -> _.
-spec loop(_State) -> _.
-spec do_join(_ChatName, _ClientPID, _Ref, _State) -> _.
-spec do_leave(_ChatName, _ClientPID, _Ref, _State) -> _.
-spec do_new_nick(_State, _Ref, _ClientPID, _NewNick) -> _.
-spec do_client_quit(_State, _Ref, _ClientPID) -> _NewState.

start_server() ->
    catch(unregister(server)),
    register(server, self()),
    case whereis(testsuite) of
	undefined -> ok;
	TestSuitePID -> TestSuitePID!{server_up, self()}
    end,
    loop(
      #serv_st{
	 nicks = maps:new(), %% nickname map. client_pid => "nickname"
	 registrations = maps:new(), %% registration map. "chat_name" => [client_pids]
	 chatrooms = maps:new() %% chatroom map. "chat_name" => chat_pid
	}
     ).

loop(State) ->
    receive 
	%% initial connection
	{ClientPID, connect, ClientNick} ->
	    NewState =
		#serv_st{
		   nicks = maps:put(ClientPID, ClientNick, State#serv_st.nicks),
		   registrations = State#serv_st.registrations,
		   chatrooms = State#serv_st.chatrooms
		  },
	    loop(NewState);
	%% client requests to join a chat
	{ClientPID, Ref, join, ChatName} ->
	    NewState = do_join(ChatName, ClientPID, Ref, State),
	    loop(NewState);
	%% client requests to join a chat
	{ClientPID, Ref, leave, ChatName} ->
	    NewState = do_leave(ChatName, ClientPID, Ref, State),
	    loop(NewState);
	%% client requests to register a new nickname
	{ClientPID, Ref, nick, NewNick} ->
	    NewState = do_new_nick(State, Ref, ClientPID, NewNick),
	    loop(NewState);
	%% client requests to quit
	{ClientPID, Ref, quit} ->
	    NewState = do_client_quit(State, Ref, ClientPID),
	    loop(NewState);
	{TEST_PID, get_state} ->
	    TEST_PID!{get_state, State},
	    loop(State)
    end.

%% executes join protocol from server perspective
do_join(ChatName, ClientPID, Ref, State) ->
    case maps:is_key(ChatName, State#serv_st.chatrooms) of
        false -> 
            %%spawn(?MODULE, start_chatroom, [ChatName]),
            Pid = spawn(fun() -> apply(fun chatroom:start_chatroom/1, [ChatName]) end),
            catch(unregister(list_to_atom(ChatName))),
            register(list_to_atom(ChatName), Pid),
    
            NewState = State#serv_st{chatrooms = maps:put(ChatName, whereis(list_to_atom(ChatName)), State#serv_st.chatrooms)},
            NewState2 = NewState#serv_st{registrations = maps:put(ChatName, [], NewState#serv_st.registrations)};
        _ -> 
            NewState2 = State
    end,
    
    ClientNick = maps:find(ClientPID, State#serv_st.nicks),
    whereis(list_to_atom(ChatName))!{self(), Ref, register, ClientPID, ClientNick},
    {X, OldRegList} = maps:find(ChatName, NewState2#serv_st.registrations),
    NewRegList = lists:append(OldRegList, [ClientPID]),
    NewState3 = NewState2#serv_st{registrations = maps:update(ChatName, NewRegList, NewState2#serv_st.registrations)},
    NewState3.

%% executes leave protocol from server perspective
do_leave(ChatName, ClientPID, Ref, State) ->
    RoomPID = maps:find(ChatName, State#serv_st.chatrooms),
    {X, OldRegList} = maps:find(ChatName, State#serv_st.registrations),
    NewRegList = lists:delete(ClientPID, OldRegList),
    NewState = State#serv_st{registrations = maps:update(ChatName, NewRegList, State#serv_st.registrations)},
    whereis(list_to_atom(ChatName))!{self(), Ref, unregister, ClientPID},
    ClientPID!{self(), Ref, ack_leave},
    NewState.
    
%% notifies list of chatrooms of a changed nickname
nickNote(_Ref, _ClientPID, _NewNick, []) ->
    ok;
nickNote(Ref, ClientPID, NewNick, [H|T]) ->
    whereis(list_to_atom(H))!{self(), Ref, update_nick, ClientPID, NewNick},
    nickNote(Ref, ClientPID, NewNick, T).

%% executes new nickname protocol from server perspective
do_new_nick(State, Ref, ClientPID, NewNick) ->
    Pre = fun(H) -> H == NewNick end,
    %%case lists:keymember(NewNick, 1, maps:values(State#serv_st.nicks)) of
    case lists:any(Pre, maps:values(State#serv_st.nicks)) of
            false -> 
                NewState = State#serv_st{nicks = maps:update(ClientPID, NewNick, State#serv_st.nicks)},
                Pred = fun(K,V) -> lists:keymember(ClientPID, 1, V) end,
                ChatList = maps:keys(maps:filter(Pred, State#serv_st.registrations)),
                nickNote(Ref, ClientPID, NewNick, ChatList),
                ClientPID!{self(), Ref, ok_nick},
                NewState;
            _ -> 
                ClientPID!{self(), Ref, err_nick_used},
                State
    end.

%% executes client quit protocol from server perspective
do_client_quit(State, Ref, ClientPID) ->
    io:format("server:do_client_quit(...): IMPLEMENT ME~n"),
    State.
