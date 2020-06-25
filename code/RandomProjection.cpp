#include "RandomProjection.hpp"
#include <Eigen/Dense> // for MatrixXd
#include <Eigen/SparseCore> // for SparseMatrix
#include <Eigen/Core> // for MatrixXd
#include <iostream> // for cout
#include <random> // for random number generators
#include <chrono> 

using namespace std;
 
Eigen::MatrixXd RandomProjection::RandomGaussianMatrix(int d, int projection_dim) {
    // Random number generator initialization
    default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    // Distribution declaration
    normal_distribution<double> distribution(0,1.0/std::sqrt(projection_dim));
    // The projection matrix as a d x projection_dim Eigen::MatrixXd 
    // (could probably made more efficient since it does not have to be dynamically sized)
    Eigen::MatrixXd M(d, projection_dim);
    M.setZero();
    for(int i=0;i<d;i++){
        for(int j=0;j<projection_dim;j++)
            M(i, j) = distribution(generator);
    }
    return M;
}

Eigen::MatrixXi RandomProjection::RandomRademacherMatrix(int d, int projection_dim) {
    // Random number generator initialization
    default_random_engine generator_sign;
    generator_sign.seed(std::chrono::system_clock::now().time_since_epoch().count());
    // Distribution declaration
    std::bernoulli_distribution distribution_sign(0.5);
    // Same for bit
    default_random_engine generator_bit;
    generator_bit.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::bernoulli_distribution distribution_bit(1.0/3.0);
    // The projection matrix as a d x projection_dim Eigen::SparseMatrix<bool> 
    Eigen::MatrixXi projection_matrix(d, projection_dim);
    projection_matrix.setZero();
    for (int i=0; i<d; ++i) {
        for (int j=0; j<projection_dim; ++j) {
            // Random number generation and matrix filling
            bool sign = distribution_sign(generator_sign);
            bool bit = distribution_bit(generator_bit);
            // To fill an entry of a SparseMatrix, we need the coeffRef method
            if (sign & bit) {
                projection_matrix(i,j) = 1;
            } else if (bit) {
                projection_matrix(i,j) = -1;
            }
        }
    }
    return projection_matrix;
}

RandomProjection::RandomProjection(int original_dimension, int col_class, int projection_dim, std::string type_sample) {
    // Initialize private attributes
    m_original_dimension = original_dimension;
    m_col_class = col_class;
    m_projection_dim = projection_dim;
    m_type_sample = type_sample;

    if(type_sample=="Gaussian"){
        m_projection=RandomGaussianMatrix(original_dimension,projection_dim);
    }else{
        Eigen::MatrixXi projection_int=RandomRademacherMatrix(original_dimension,projection_dim);
        Eigen::MatrixXd projection(original_dimension,projection_dim);
        for(int i=0;i<original_dimension;i++){
            for(int j=0;j<projection_dim;j++){
                projection(i,j)=(double)projection_int(i,j);
            }
        }
        m_projection=projection;
    }

}

void RandomProjection::ProjectionQuality(Dataset *dataset) {
    Dataset projected_dataset = Project(dataset);

    std::cout << "Calculating mean pairwise distance in the original dataset (this may take time):" << std::endl;

    // The cumulative norm between all pairs of points
    double sum_norm = 0.0;

    // TODO - Optional Exercise 2 : A costly loop over all pairs of points
    int n = dataset->getNbrSamples();
    int d = dataset->getDim();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double ele_norm=0;
            for(int k=0;k<d;k++){

                ele_norm+=pow(dataset->getInstance(i)[k]-dataset->getInstance(j)[k],2);
            
            }
            ele_norm=std::sqrt(ele_norm);
            sum_norm+=ele_norm;
        }
    }
    // Number of pairs of points
    sum_norm/=n*(n-1)/2;

    std::cout << sum_norm << std::endl;

    // Same for projected data
    std::cout << "Calculating mean pairwise distance in the projected dataset:" << std::endl;

    double sum_norm_projected = 0.0;

    // TODO - Optional Exercise 3: A costly loop over all pairs of points
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double ele_norm=0;
            for(int k=0;k<m_projection_dim;k++){
                ele_norm+=pow(projected_dataset.getInstance(i)[k]-projected_dataset.getInstance(j)[k],2);
            }
            ele_norm=std::sqrt(ele_norm);
            sum_norm_projected+=ele_norm;
        }
    }

    sum_norm_projected/=n*(n-1)/2;

    std::cout << sum_norm_projected << std::endl;
}

Dataset RandomProjection::Project(Dataset *dataset) {
    if (dataset->getDim()-1 < m_projection_dim) {
        std::cerr << "Impossible to project on higher dimensions!" << std::endl;
    }

    // Gathering all columns in a Eigen::Matrix
    Eigen::MatrixXd data(dataset->getNbrSamples(), dataset->getDim());
    for (int i=0; i<dataset->getNbrSamples(); i++) {
        std::vector<double> sample = dataset->getInstance(i);
        for (int j=0; j<dataset->getDim()-1;j++) {
            data(i,j) = sample[j];
        }
        // The col_class goes first
        data(i,dataset->getDim()-1) = sample[dataset->getDim()-1];
    }

    // Matrix multiplication except col_class
    Eigen::MatrixXd projected_data = data.block(0,0,dataset->getNbrSamples(),dataset->getDim()-1) * m_projection;

    projected_data.conservativeResize(projected_data.rows(), projected_data.cols()+1);
    // std::cout<<projected_data<<std::endl;
    projected_data.col(projected_data.cols()-1) = data.col(dataset->getDim()-1);

    // Attribute m_dataset of class Dataset is a std::vector< std::vector<double> >
    std::vector< std::vector<double> > _dataset;
    // Resize and fill it e.g. with 0s (to avoid Segmentation Faults)
	_dataset.resize(projected_data.rows(), std::vector<double>(projected_data.cols(), 0));
    // Copy each element
	for(size_t i = 0; i < _dataset.size(); i++){
		for(size_t j = 0; j < _dataset.front().size(); j++)
			_dataset[i][j] = projected_data(i,j);
    }


    // Call to constructor
    Dataset dataset_class(_dataset);

    return dataset_class;
}

int RandomProjection::getOriginalDimension() {
    return m_original_dimension;
}

int RandomProjection::getColClass() {
    return m_col_class;
}

int RandomProjection::getProjectionDim(){
    return m_projection_dim;
}

std::string RandomProjection::getTypeSample(){
    return m_type_sample;
}

Eigen::MatrixXd RandomProjection::getProjection(){
    return m_projection;
}
