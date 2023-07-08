#include "compiled_protos/RaceWeekend.pb.h"
#include "enums.hpp"


struct LapStrategy {
    uint32_t targetLapTimeMS;
    ActualTyreCompound tyreCompound;
};

struct Strategy
{
    std::vector<LapStrategy> perLapStrategy;

    bool isPitLap(int lapNumber) {
        lapNumber--; // Make 0 indexed

        if (lapNumber == 0) return false;

        return (perLapStrategy[lapNumber - 1].tyreCompound != perLapStrategy[lapNumber].tyreCompound);
    }

    uint8_t nextPitStop(int currentLap) {
        for (size_t i = currentLap; i < perLapStrategy.size(); i++) {
            if (isPitLap(i)) return i;
        }
        return 0;
    }
};

class RaceStrategyPredictor
{
public:
    RaceStrategyPredictor();
    ~RaceStrategyPredictor();

    /**
     * @brief Predict the initial race strategy using the race weekend data generated
     * during the practice sessions
     * 
     * @param[in] raceWeekend The race weekend data loaded from the protobuf file 
     */
    void predictStrategy(RaceWeekend);
    
    /**
     * @brief Update the current strategy using the live data coming from the game
     * 
     */
    void updateStrategy(); // TODO: Define the data that comes into this function

    /**
     * @brief Get the current strategy prediction being run
     * 
     */
    Strategy getStrategy() {
        return currentStrategy;
    };

private:
    Strategy currentStrategy;
};