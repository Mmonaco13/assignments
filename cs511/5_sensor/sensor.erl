%%  Matthew Monaco
%% I pledge my honor that I have abided by the Stevens Honor System
-module(sensor).
-compile(export_all).
-author("Matthew Monaco").

sensor(Watcher, Id) ->
    %% Generate a random measurement
    Measurement = rand:uniform(11),

    case Measurement == 11 of
        true ->
            %% Crash with the report "anomalous_reading"
            exit(anomalous_reading);
        false ->
            %% Report measurement to watcher process
            Watcher!{self(), report, {Id, Measurement}}
        end,

    Sleep_time = rand:uniform(10000),
    timer:sleep(Sleep_time),
    sensor(Watcher, Id).
