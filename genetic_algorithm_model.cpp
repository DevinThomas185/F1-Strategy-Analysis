#include "genetic_algorithm_model.h"

GeneticAlgorithmModel::GeneticAlgorithmModel()
{

}

StrategyModel generateRandomStrategyModel() {
    StrategyModel strat = {};
    return strat;
}

void GeneticAlgorithmModel::initialise(int population_size, int elitism) {
    m_population_size = population_size;

    for (int i = 0; i < population_size; i++) {
        StrategyModel strat = generateRandomStrategyModel();

        m_population.push_back({
            .strategy_model = strat,
            .score = 0
        });
    }

    m_initialised = true;
}

void GeneticAlgorithmModel::runUntilConvergence(float epsilon, int maxIterations) {
    int iterations = 0;
    while (true)
    {
        runOneGeneration();

        // Reached convergence within epsilon
        if (abs(getBestScore() - lastBestScore) < epsilon) {
            return;
        }

        // If we have reached maximum number of iterations to reach convergence
        if (iterations == maxIterations) {
            return;
        }

        iterations++;
    }
}

void GeneticAlgorithmModel::runNGenerations(int n) {
    for (int i = 0; i < n; i++) {
        runOneGeneration();
    }
}

void GeneticAlgorithmModel::runOneGeneration() {
    if (!m_initialised) {
        return;
    }
    test();
    selection();
    crossover();
    mutation();
}

StrategyScore GeneticAlgorithmModel::getNRankStrategyScore(int n) {
    if (n >= m_population.size()) {
        return m_population.back();
    }

    return m_population[n];
}

StrategyScore GeneticAlgorithmModel::getBestStrategyScore() {
    return getNRankStrategyScore(0);
}

StrategyModel GeneticAlgorithmModel::getNRankStrategy(int n) {
    return getNRankStrategyScore(n).strategy_model;
}

StrategyModel GeneticAlgorithmModel::getBestStrategy() {
    return getNRankStrategy(0);
}

float GeneticAlgorithmModel::getNRankScore(int n) {
    return getNRankStrategyScore(n).score;
}

float GeneticAlgorithmModel::getBestScore() {
    return getNRankScore(0);
}



bool compareStrategyScores(StrategyScore a, StrategyScore b) {
    return a.score < b.score;
}

void GeneticAlgorithmModel::test() {

    // EXAMPLE CODE
    
    // Order the strategy models based on their performance
    sort(m_population.begin(), m_population.end(), compareStrategyScores);
}

void GeneticAlgorithmModel::selection() {

}

void GeneticAlgorithmModel::crossover() {

}

void GeneticAlgorithmModel::mutation() {
    
}
