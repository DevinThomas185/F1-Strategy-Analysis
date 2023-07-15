# F1 Strategy Analysis

The EA Sports F1 games have the ability to broadcast telemetry data about your race to a computer. However, there is a lack of software that utilises this essential data.

This software was designed to consume and display data output by the F1 games. Live race data can be viewed by a race engineer to analyse the current race performance.

Additionally, the race engineer can record practice session laps and allocate them to 'stint's such as race or qualifying simulations. By producing a protobuf file from the recording, we can achieve a much smaller file size than its JSON copy. Recorded laps can later be loaded back in to be analysed later.

### Supported F1 Versions

- F1 22
- F1 23 (with F1 22 Output)

## Features

### Positions table and weather forecast

![](/demo_images/Positions.png "Positions Table and Weather Forecast")

### Car damage and steering wheel data

![](/demo_images/Damage.png "Car Damage and Steering Wheel")

### Telemetry traces

![](/demo_images/TelemetryTraces.png "Telemetry Traces")

### Lap history table

![](/demo_images/LapHistory.png "Lap History")

### Track map

![](/demo_images/TrackMap.png "Track map")

#### Completed Track Maps

Only some of the track maps have been drawn and added to the software. These are listed below. The remaining tracks to be added are listed [here](#incomplete-track-maps).

- Bahrain International Circuit (Bahrain)
- Jeddah Corniche Circuit (Saudi Arabia)
- Albert Park (Australia)

### Lap recording

![](/demo_images/LapRecording.png "Lap recording")

### Recorded telemetry

![](/demo_images/RecordedTelemetry.png "Recorded Telemetry")

### Live Strategy

![](/demo_images/LiveStrategy.png "Live Strategy")

## Upcoming Features

[List of upcoming features](TODO.md#features)

## Recently Complete Features

- Table to display the predicted pit stops
- Display the starting fuel amount for the race
- Add different tyres to Live Strategy tab
- Add tyre degradation to Live Strategy tab
- Add fuel usage graphing to Live Strategy tab
- Add Live Strategy tab
- IP and Port changable in settings bar
- Albert Park (Australia) track added
- Pressures added to damage tab
- Current tyres with tyre age added to positions table
- Jeddah Corniche Circuit (Saudi Arabia) track added
- Safety car announcements

### Incomplete Track Maps

- Baku City Circuit (Azerbaijan)
- Miami International Autodrome (Miami)
- Imola Circuit (Emilia Romagna)
- Circuit de Monaco (Monaco)
- Circuit de Barcelona-Catalunya (Spain)
- Grand Prix Circuit Gilles Villeneuve (Canada)
- Red Bull Ring (Austria)
- Silverstone Circuit (Britain)
- Hungaroring (Hungary)
- Circuit de Spa-Francorchamps (Belgium)
- Circuit Zandvoort (Netherlands)
- Monza Circuit (Italy)
- Marina Bay Street Circuit (Singapore)
- Lusail International Circuit (Qatar)
- Circuit of the Americas (USA)
- Autodromo Hermanos Rodriguez (Mexico)
- Interlagos Circuit (Brazil)
- Las Vegas Street Circuit (Las Vegas)
- Yas Marina Circuit (Abu Dhabi)
- Portimao (Portugal)
- Shanghai (China)
- Paul Ricard (France)
