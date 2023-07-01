# To Do List

## Bugs

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

## Features

- Add lap details to the recorded telemetry tab to see details when overlay included
- Flags for each marshal zone
- Put vertical lines for each turn on the graphs
- Tyre strategy for entire race
- Add support for F1 23 packets
- Add current setup for car
- Add time delta to the steering wheel
- Ability to write to already loaded files
- Race strategy prediction
- Recording of the race and qualifying sessions
