#include "compiled_protos/RaceWeekend.pb.h"

class RaceStrategyPredictor {
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

private:

};