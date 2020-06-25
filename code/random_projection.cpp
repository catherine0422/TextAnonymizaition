#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Dataset.hpp"
#include "RandomProjection.hpp"
#include "BinaryKnnClassification.hpp"
#include "BinaryConfusionMatrix.hpp"
#include <cstdlib>
using namespace std;

/** @file
*/

// Prints correct usage
void msgleave(char* argv[]) {
        std::cout << "Usage: " << argv[0] << " <k> <projection_dim> <train_representation> <train_label> <test_representation> <test_label> <sampling> " << std::endl;
}

int main(int argc, char* argv[]) {
    // Tests correct usage
	if (argc < 8) {
		msgleave(argv);
		return 1;
	}
		
    // Puts train file in a Dataset object
    std::string train_representation=argv[3];
    train_representation=train_representation.substr(0, train_representation.length()-4);
    std::string test_representation=argv[5];
    test_representation=test_representation.substr(0, test_representation.length()-4);
	Dataset train_dataset(argv[3],argv[4]);
	Dataset class_dataset(argv[5],argv[6]);

    // Tests value of projection_dim (should be > 1 < dimension of dataset)
	int projection_dim=atoi(argv[2]);
	if ((projection_dim<1) | (projection_dim>=train_dataset.getDim()-1)) { 
		std::cout<<"Invalid value of projection_dim."<<std::endl;
		msgleave(argv);
		return 1;
	}

    // Tests value of k (should be > 1)
	int k=atoi(argv[1]);
	if (k<1) { 
		std::cout<<"Invalid value of k."<<std::endl;
		msgleave(argv);
		return 1;
	}

    // Tests value of sampling (should be "Gaussian" or "Rademacher")
	std::string sampling=argv[7];
	if ((sampling!="Gaussian") & (sampling!="Rademacher")) { 
		std::cout<<"Invalid value of sampling."<<std::endl;
		msgleave(argv);
		return 1;
	}
    
    // Checks which column is the class label
    int col_class=train_dataset.getDim()-1;


    // Prints dimension
	train_dataset.Show(false);  // only dim and samples

	// Random projection
    std::cout << "Performing Random Projection" << std::endl;
    clock_t t_random_projection = clock();
	RandomProjection projection(train_dataset.getDim()-1, col_class, projection_dim, sampling);
    col_class=projection_dim;
    t_random_projection = clock() - t_random_projection;
    std::cout << endl
         <<"Execution time: "
         <<(t_random_projection*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";
    //projection.ProjectionQuality();


    // Performing Knn on projected data
    std::cout << "Performing Knn on projected data" << std::endl;
    clock_t t_knn_train_projected = clock();
    Dataset projection_dataset = projection.Project(&train_dataset);
    train_representation+="_projected_d"+to_string(projection_dim)+".csv";
    projection_dataset.Save(train_representation.c_str());
    projection_dataset.Show(false);
    BinaryKnnClassification knn_class_projected(k, &projection_dataset, 0);
    t_knn_train_projected = clock() - t_knn_train_projected;
    std::cout << endl
         <<"Execution time: "
         <<(t_knn_train_projected*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";

    // Knn test on projected data
    std::cout << "Predicting Knn on projected data" << std::endl;
    BinaryConfusionMatrix confusion_matrix_projected;
    Dataset projection_test_dataset = projection.Project(&class_dataset);
    test_representation+="_projected_d"+to_string(projection_dim)+".csv";
    projection_test_dataset.Save(test_representation.c_str());
    clock_t t_knn_test_projected = clock();
        for (int i=0; i<projection_test_dataset.getNbrSamples(); i++) {
            if(i%100==0){
                std::cout<<"predicting sample No."<<i<<std::endl;
            }
            std::vector<double> sample = projection_test_dataset.getInstance(i);
            Eigen::VectorXd query(projection_test_dataset.getDim()-1);
            int true_label=sample[col_class];
            for (int j=0; j<projection_test_dataset.getDim()-1; j++) {
                query[j] = sample[j];
            }
        int predicted_label = knn_class_projected.Estimate(query);
        confusion_matrix_projected.AddPrediction(true_label, predicted_label);
    }
    t_knn_test_projected = clock() - t_knn_test_projected;
    std::cout << endl
         <<"Execution time: "
         <<(t_knn_test_projected*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";
    confusion_matrix_projected.PrintEvaluation();


}