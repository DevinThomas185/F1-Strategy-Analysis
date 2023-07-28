#ifndef GENETIC_ALGORITHM_MODEL_H
#define GENETIC_ALGORITHM_MODEL_H

#include "race_strategy_prediction.hpp"

struct StrategyModel {
};

struct StrategyScore {
    StrategyModel strategy_model;
    float score;
};

class GeneticAlgorithmModel
{
public:
    GeneticAlgorithmModel();

    void runUntilConvergence(float epsilon, int maxIterations);  // TODO: Need to define convergence
    void runNGenerations(int n);
    void runOneGeneration();

    StrategyModel getNRankStrategy(int n);
    StrategyModel getBestStrategy();


private:
    /**
     * @brief Initialise the population size
     * 
     * @param population_size The size of the population to consider
     */
    void initialise(int population_size, int elitism);

    void test();

    void selection();
    void crossover();
    void mutation();

    StrategyScore getNRankStrategyScore(int n);
    StrategyScore getBestStrategyScore();
    float getNRankScore(int n);
    float getBestScore();

    // Strategy and their evaluation score
    std::vector<StrategyScore> m_population;

    bool m_initialised;
    int m_population_size;

    float lastBestScore;
};

#endif // GENETIC_ALGORITHM_MODEL_H
