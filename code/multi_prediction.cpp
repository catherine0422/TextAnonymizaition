#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Dataset.hpp"
#include "MultiKnnClassification.hpp"
#include "MultiConfusionMatrix.hpp"
#include <cstdlib>
using namespace std;

/** @file
*/

// Prints correct usage
void msg(char* argv[]) {
    std::cout << "Usage: " << argv[0] << " <k> <train_representation> <train_label> <test_representation> <test_label> <label_to_evaluate_accuracy> <number_of_labels>[ <predicted_label> ]" << std::endl;
}

int main(int argc, char* argv[]) {

    std::cout << "\n******** Reading the arguments *********\n" << std::endl;

    if (argc < 8) {
		msg(argv);
		return 1;
    }

    // Tests value of k (should be > 1)
    int k=atoi(argv[1]);
	if (k<1) { 
		std::cout<<"Invalid value of k:"<<k<<std::endl;
		msg(argv);
		return 1;
	}

    //Tests value of label_to_evaluate_accuracy
    int label=atoi(argv[6]);
    if (label<0) { 
		std::cout<<"Invalid value of label_to_evaluate_accuracy:"<<label<<std::endl;
		msg(argv);
		return 1;
	}

    //Tests value of number_of_labels
    int n_label=atoi(argv[7]);
    if (n_label<1) { 
		std::cout<<"Invalid value of number_of_labels:"<<n_label<<std::endl;
		msg(argv);
		return 1;
	}

    //Tests value of predicted_label
    std::string test_label=argv[5];
    test_label=test_label.substr(0, test_label.length()-4);
    std::ofstream output;
    if(argc==9){
        output.open(argv[8], std::ofstream::out );
    }else{
        output.open(test_label+"_multi_predicted.csv", std::ofstream::out);
        std::cout<< "No file name specified for output, it will be saved as "<<test_label <<"_multi_predicted.csv"<<std::endl;
        if(output.fail()){
            std::cout<<"Cannot write into the file "<<test_label  <<"_multi_predicted.csv"<<std::endl;
            msg(argv);
            exit(1);
        }
    }
    
    // Puts train and test file in a Dataset object
    std::cout << "\n*********** Creating dataset ***********\n" << std::endl;
	Dataset train_dataset(argv[2],argv[3]);
	Dataset class_dataset(argv[4],argv[5]);

    // Prints dimension
    std::cout<<"Train data: ";
	train_dataset.Show(false);  // only dim and samples
    std::cout<<"Test data: ";
	class_dataset.Show(false);  // only dim and samples
    
    // The last column is the class label
    int col_class=train_dataset.getDim()-1;


    
    // Performing Knn 
    std::cout << "\n************ Performing Knn ************" << std::endl;
    clock_t t_knn_train = clock();
    MultiKnnClassification knn_class(k, &train_dataset,n_label);
    t_knn_train = clock() - t_knn_train;
    std::cout << endl
         <<"Execution time: "
         <<(t_knn_train*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";

    
    // Knn test 
    std::cout << "************ Predicting Knn ************" << std::endl;
    MultiConfusionMatrix confusion_matrix(label);
    clock_t t_knn_test = clock();
    int *predicted_label=new int[class_dataset.getNbrSamples()];
    for (int i=0; i<class_dataset.getNbrSamples(); i++) {

        std::vector<double> sample = class_dataset.getInstance(i);
        Eigen::VectorXd query(class_dataset.getDim()-1);
        int true_label=sample[col_class];
        for (int j=0; j<train_dataset.getDim()-1; j++) {
            query[j] = sample[j];
        }
        
        predicted_label[i] = knn_class.Estimate(query);
        output<<predicted_label[i]<<" ";
        output<<endl;
        confusion_matrix.AddPrediction(true_label, predicted_label[i]);
    }


    
    t_knn_test = clock() - t_knn_test;
    std::cout << endl
         <<"Execution time: "
         <<(t_knn_test*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";
    confusion_matrix.PrintEvaluation();
    std::cout<<"\n"<<std::endl;



    output.close();

    std::cout<<"Prediction finish, the predicted label is saved as: "<< test_label <<"_multi_predicted.csv"<<std::endl;
    std::cout << "\n**************** Finish ****************" << std::endl;

}