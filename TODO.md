# To Do List

## Bugs

- Strategy prediction for lap time regressions are invalid as some stints may be completed on used tyres and different fuel loads so these must be taken into account
- Software crashes when clicking Predict Strategy without loading in a race recording
- Fix to tyre wear in damage tab
- If listening after already starting the race, using own player in race, the name does not appear in participants packet
- Tyre degradation and fuel degradation are too frequently recorded (record once per lap or a few times per lap)
- Telemetry traces sometimes randomly reset mid lap
- Fuel and tyre degradation graphs need to clear the regression lines after changing stint number / stint type / session.
- Fuel estimate for race seems to be far too high
- The positions table for non-race sessions is broken (interval)
- Attempting to start recording a stint after starting listening, but not receiving any packets, crashes the program
- Fix the Jeddah track being too high
- Tyre life for front left seems to not be updating all the time - intermittent and instant on crash
- Positions change during practice shows +255
- Need a stop button to end a stint early or to change to a new one?
- Telemetry traces need to be aligned
- Fuel prediction seems to be far too high (176kg predicted vs 105kg actual for Bahrain)
- Interval times seem to be a bit dodgy - reporting 0.x00, 0.x01, 0.x02
- Changing of sessions whilst listening causes the software to crash
- Race simulation randomly split into two stints

## Features

- Spamming predict strategy messes up the graphs and the predicted lap times
- Remove fuel prediction from the Recorded Laps Tab
- Add session timer for practice and qualifying
- Add tyre strategy in a graphical way to the Live Strategy tab
- Add current tyres and tyre age to live strategy tab
- Reorganise the live strategy tab
- Add lap details to the recorded telemetry tab to see details when overlay included such as lap time and sector times
- Flags for each marshal zone
- Put vertical lines for each turn on the graphs
- Add support for F1 23 packets
- Add current setup for car
- Add time delta to the steering wheel
- Ability to write to already loaded files
- Recording of the race and qualifying sessions
