%%  Matthew Monaco
%%  I pledge my honor that I have abided by the Stevens Honor System
-module(watcher).
-compile(export_all).
-author("Matthew Monaco").

watcher(Num_sensors, ID_mult) ->
    Sensor_pid = spawn_sensors(Num_sensors, ID_mult, []),
    io:fwrite("Starting: watching sensors ~p~n",[Sensor_pid]),
    watcher_loop(Sensor_pid).

spawn_sensors(Num_sensors, ID_mult, L) when Num_sensors > 0 ->
    ID = (10*ID_mult) + Num_sensors,
    Watch = self(),
    {Pid, _} = spawn_monitor(fun() -> apply(fun sensor:sensor/2, [Watch, ID]) end),
    spawn_sensors(Num_sensors - 1, ID_mult, lists:append(L, [{ID, Pid}]));
spawn_sensors(_Num_sensors, _ID_mult, L) ->
    L.

watcher_loop(Pids) ->
    process_flag(trap_exit, true),
    receive
        %%{Id, Measurement}
        {_Sensor, report, Response} ->
            {Id, Measurement} = Response,
            io:fwrite("Sensor ~p reports measurement ~p~n",[Id, Measurement]),
            NewPids = Pids;
        {'DOWN', _Ref, process, Pid, anomalous_reading} ->
            {ID,_} = lists:keyfind(Pid,2,Pids),
            io:fwrite("Sensor ~p died due to anomalous reading~n",[ID]),
            
            Watch = self(),
            {Pid2, _} = spawn_monitor(fun() -> apply(fun sensor:sensor/2, [Watch, ID]) end),

            NewPids = lists:append(lists:delete({ID, Pid}, Pids), [{ID, Pid2}]),
            io:fwrite("Sensor restarted: ~p~n",[NewPids])
    end,
    watcher_loop(NewPids).
