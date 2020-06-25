#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#ifndef DATASET_HPP
#define DATASET_HPP


/**
  The Dataset class encapsulates a dataset in a vector of vectors and provides a kind of interface to manipulate it.
*/
class Dataset {
    public:
        /**
          The constructor needs the paths of the representation_file and the label_file 
          as a string. The label is placed at the last column.
        */
        Dataset(const char* representation_file, const char* label_file);
        /**
          The constructor of Dataset from a vector of vector (needed for RandomProjection).
        */
        Dataset(const std::vector<std::vector<double> > &vector_of_vector);
        /**
          Standard destructor
        */
        ~Dataset();
        
        /**
          The Show method displays the number of instances and columns of the Dataset.
          @param verbose If set to True, the Dataset is also printed.
        */
        void Show(bool verbose);
        /**
          Save the dataset in a file
          @param file_name is the path to save the dataset.
        */
        void Save(const char *file_name);
        /**
         Returns a copy of an instance.
        @param i Instance number (= row) to get.
        */
    	  std::vector<double> getInstance(int i);
        /**
          The getter to the number of instances / samples.
        */
    	  int getNbrSamples();
        /**
          The getter to the dimension of the dataset.
        */
    	  int getDim();

    private:
        /**
          The dimension of the dataset.
        */
		    int m_dim;
        /**
          The number of instances / samples.
        */
		    int m_nsamples;
        /**
          The dataset is stored as a vector of double vectors.
        */
        std::vector<std::vector<double> > m_instances;
};
#endif //DATASET_HPP
