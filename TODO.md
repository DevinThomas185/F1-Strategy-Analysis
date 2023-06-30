# TODO

## Bugs

- If listening after already starting the race, using own player in race, the name does not appear in participants packet

- Tyre degradation and fuel degradation are too frequently recorded (record once per lap or a few times per lap)

- Telemetry traces sometimes randomly reset mid lap

- Fuel and tyre degradation graphs need to clear the regression lines after changing stint number / stint type / session.

- Fuel estimate for race seems to be far too high

- The positions table for non-race sessions is broken (interval)

- Attempting to start recording a stint after starting listening, but not receiving any packets, should not crash the program

- Fix the Jeddah track being too high

## Features

- Show marshal flags
- Put vertical lines for each turn on the graphs
- Tyre strategy for entire race
- Overlay traces of telemetry
- Add support for F1 23 packets
- Add current setup for car
- Add time delta to the steering wheel
- Ability to write to already loaded files
