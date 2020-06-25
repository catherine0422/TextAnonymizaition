#include "ConfusionMatrix.hpp"

#ifndef MULTICONFUSIONMATRIX_HPP
#define MULTICONFUSIONMATRIX_HPP

/**
  The MultiConfusionMatrix class .
*/
class MultiConfusionMatrix :public ConfusionMatrix{

    public:
        /**
          The standard constructor.
        */
        MultiConfusionMatrix(int label);
        /**
          The standard destructor.
        */
        ~MultiConfusionMatrix();

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

    private:
        /**
        The label used to check accuracy.
        */
        int m_label;
};

#endif    // END_MULTICONFUSIONMATRIX_HPP
