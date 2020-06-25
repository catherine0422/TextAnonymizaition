#include "Dataset.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>

#ifndef CLASSIFICATION_HPP
#define CLASSIFICATION_HPP

/** 
	The Classification class is an abstract class that will be the basis of the KnnClassification classe.
*/
class Classification{
protected:
    /**
      The pointer to a dataset.
    */
	Dataset* m_dataset;
    /**
      The column to do classification on.(supposed to be the last line)
    */
	int m_col_class;
public:
    /**
      The constructor sets private attributes dataset (as a pointer) and the column to do classification on (as an int).
    */
	Classification(Dataset* dataset);
    /**
      The dataset getter.
    */
	Dataset* getDataset();
    /**
      The col_class getter.
    */
	int getColClass();
    /**
      The Estimate method is virtual: it (could) depend(s) on the Classification model(s) implemented (here we use only the KnnClassification class).
    */
	virtual int Estimate(const Eigen::VectorXd & y , double threshold) = 0;
};

#endif //CLASSIFICATION_HPP
