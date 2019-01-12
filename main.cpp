#include <iostream>
#include <fstream>

#include "FastaParser.h"
#include "Viterbi.h"
#include "ViterbiLogOdds.h"
#include "MleEstimator.h"

int main() {

    FastaParser parser("../database/pairs/HIV1_REF_2010/p1.fasta");

    const std::vector<Sequence *> sequences = parser.parse();

    for (int i = 0; i < sequences.size(); ++i) {
        Sequence *s = sequences.at(i);

        std::cout << s->getDescription() << std::endl;

        for (int j = 0; j < s->getSequence().size(); ++j) {
            std::cout << s->getSequence().at(j) << std::flush;
        }
        std::cout << std::endl << std::endl;
    }
//
//    const float transition_prob[3] = { 0.00170081, 0.00721899, 0.0255121 };
//
//
//    const float emission_prob[5][5] = {
//            { 0.071791, 0.047737, 0.073646, 0.052003, 0.000989 },
//            { 0.034875, 0.040440, 0.044707, 0.025723, 0.000186 },
//            { 0.065855, 0.032464, 0.067029, 0.040749, 0.000742 },
//            { 0.047242, 0.033762, 0.039327, 0.031227, 0.000124 },
//            { 0.016696, 0.007853, 0.013542, 0.007297, 0 }
//    };
//
//    const float transmission_prob[3][3] = {
//            { 0.889107, 0.001361, 0.001663 },
//            { 0.001361, 0.000983, 0 },
//            { 0.004233, 0, 0.050042 }
//    };


    //ViterbiLogOdds viterbi(transition_prob, emission_prob, 0.01);

    //viterbi.alignSequences(sequences.at(0), sequences.at(1));


    auto *mleEstimator = new MleEstimator("../database/outputs_mafft/upcase/");
    mleEstimator->estimate();


    auto *logOdds = new ViterbiLogOdds(mleEstimator->getAveragedTransitionProbabilities(),
                                                        mleEstimator->getEmissionProbabilities(),
                                                        mleEstimator->getLookupTable(), 0.01);

    logOdds->alignSequences(sequences.at(0), sequences.at(1));

    return 0;
}
