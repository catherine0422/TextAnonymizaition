#include <Eigen/Dense>
#include <Eigen/Core>
#include "Dataset.hpp"
#include "KnnClassification.hpp"
#include <ANN/ANN.h>

#ifndef MultiKNNCLASSIFICATION_HPP
#define MultiKNNCLASSIFICATION_HPP

/**
  The MultiKnnClassification class inherits from the KnnClassification class, adds the number of labels.
*/
class MultiKnnClassification : public KnnClassification {
private:
    /**
      The number of labels.
    */
	int m_n_label;
public:  
    /**
      The constructor needs:
     @param n_label: The number of labels
    */
	MultiKnnClassification(int k, Dataset* dataset,int n_label);
    /**
      The standard destructor.
    */
	~MultiKnnClassification();
    /**
      The predicted label for a new instance depending on the chosen thresholds:
     @param x the new instance which output we wish to predict, as a VectorXd of class Eigen.
     @param threshold the threshold in majority vote.
     @returns the prediction as an integer
    */
  int Estimate(const Eigen::VectorXd & x, double threshold=0.5);
    /**
      The getter for the number of lables
    */
  int getNLabel();
};

#endif //MultiKNNCLASSIFICATION_HPP