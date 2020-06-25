#include <Eigen/Dense>
#include <Eigen/Core>
#include "Dataset.hpp"
#include "Classification.hpp"
#include <ANN/ANN.h>

#ifndef KNNCLASSIFICATION_HPP
#define KNNCLASSIFICATION_HPP

/**
  The KnnClassification class inherits from the Classification class, adds the number of neighbours k, the kdTree obtained from the ANN library, and a bunch of methods.
*/
class KnnClassification : public Classification {
protected:
    /**
      The number of neighbours k to compute.
    */
	int m_k;
      /**
      The kdTree obtained from the ANN library.
    */
	ANNkd_tree* m_kdTree;
public:  
    /**
      The constructor needs:
     @param k the number of neighbours
     @param dataset the pointer to a dataset of class Dataset
    */
	KnnClassification(int k, Dataset* dataset);
    /**
      The standard destructor.
    */
	~KnnClassification();
    /**
      The predicted label for a new instance depending on the chosen thresholds:
     @param x the new instance which output we wish to predict, as a VectorXd of class Eigen.
     @param threshold the threshold in majority vote.
     @returns the prediction as an integer
    */
  virtual int Estimate(const Eigen::VectorXd & x, double threshold)=0;
    /**
      The getter for the number of neighbors
    */
  int getK();
    /**
      The getter for the kdtree
    */
  ANNkd_tree* getKdTree();
};

#endif //KNNCLASSIFICATION_HPP
