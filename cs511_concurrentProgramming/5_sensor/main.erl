%%  Matthew Monaco
%%  I pledge my honor that I have abided by the Stevens Honor System.
-module(main).
-compile(export_all).
-author("Matthew Monaco").

start() ->
    {ok , [N]} = io:fread("enter number of sensors> ", "~d"),
    if N =< 1 ->
        io:fwrite("setup: range must be at least 2~n", []);
    true ->
        Num_watchers = 1 + (N div 10),
        setup_loop(N, Num_watchers)
    end.

setup_loop(Num_sensors, Num_watchers) when Num_watchers > 0 ->
    Extra = (Num_sensors rem 10),
    if Extra =/= 0 ->
        _Pid = spawn(fun() -> apply(fun watcher:watcher/2, [Extra, Num_watchers - 1]) end),
        %%spawn(?MODULE, watcher, [Extra, Num_watchers - 1]),
        setup_loop(Num_sensors - Extra, Num_watchers - 1);
    true ->
        _Pid = spawn(fun() -> apply(fun watcher:watcher/2, [10, Num_watchers - 1]) end),
        %%spawn(?MODULE, watcher, [10, Num_watchers - 1]),
        setup_loop(Num_sensors - 10, Num_watchers - 1)
    end;
setup_loop(_Num_sensors, _Num_watchers) ->
    ok.
