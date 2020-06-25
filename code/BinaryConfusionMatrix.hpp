#include "ConfusionMatrix.hpp"

#ifndef BINARYCONFUSIONMATRIX_HPP
#define BINARYCONFUSIONMATRIX_HPP

/**
  The BinaryConfusionMatrix class .
*/
class BinaryConfusionMatrix: public ConfusionMatrix{

    public:
        /**
          The standard constructor.
        */
        BinaryConfusionMatrix();
        /**
          The standard destructor.
        */
        ~BinaryConfusionMatrix();

        /**
          Adding a single observation to the (unnormalized) confusion matrix:
        @param true_label (int) the true label of the new point to add to the confusion matrix.
        @param predicted_label (double) the threshold above which class label '1' will be predicted.
        */
        void AddPrediction(int true_label, int predicted_label);

        /**
          Prints the confusion matrix and the evaluation metrics.
        */
        void PrintEvaluation() const;


};

#endif    // END_BINARYCONFUSIONMATRIX_HPP
