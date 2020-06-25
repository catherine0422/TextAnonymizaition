#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Dataset.hpp"
#include "BinaryKnnClassification.hpp"
#include "BinaryConfusionMatrix.hpp"
#include <cstdlib>
using namespace std;

/** @file
*/

// Prints correct usage
void msg(char* argv[]) {
    std::cout << "Usage: " << argv[0] << " <k> <train_representation> <train_label> <test_representation> <test_label> [ <predicted_label> ]" << std::endl;
}

int main(int argc, char* argv[]) {

    std::cout << "\n******** Reading the arguments *********\n" << std::endl;

    if (argc < 6) {
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

    //Tests value of predicted_label
    std::string test_label=argv[5];
    test_label=test_label.substr(0, test_label.length()-4);
    std::ofstream output;
    if(argc==7){
        output.open(argv[6], std::ofstream::out);
    }else{
        output.open(test_label+"_predicted.csv", std::ofstream::out);
        std::cout<< "No file name specified for output, it will be saved as "<< test_label <<"_predicted.csv"<<std::endl;
        if(output.fail()){
            std::cout<<"Cannot write into the file "<<test_label <<"_predicted.csv"<<std::endl;
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
    for(int i=2;i<20;i++){
        k=i;
            std::cout << "\n********** Performing Knn k ************" << std::endl;
    clock_t t_knn_train = clock();
    BinaryKnnClassification knn_class(k, &train_dataset,2);
    t_knn_train = clock() - t_knn_train;
    std::cout << endl
        <<"Execution time: "
        <<(t_knn_train*1000)/CLOCKS_PER_SEC
        <<"ms\n\n";

    // Knn test 
    std::cout << "************ Predicting Knn ************" << std::endl;
    BinaryConfusionMatrix confusion_matrix;
    clock_t t_knn_test = clock();
    int *predicted_label=new int[class_dataset.getNbrSamples()];
    for (int i=0; i<class_dataset.getNbrSamples(); i++) {
        // if(i%100==0){
        //     std::cout<<"predicting sample No."<<i<<std::endl;
        // }
        std::vector<double> sample = class_dataset.getInstance(i);
        Eigen::VectorXd query(class_dataset.getDim()-1);
        int true_label=sample[col_class];
        for (int j=0; j<train_dataset.getDim()-1; j++) {
            query[j] = sample[j];
        }
        predicted_label[i] = knn_class.Estimate(query);
        //predicted_label[i] = knn_class.Estimate(query);
        confusion_matrix.AddPrediction(true_label, predicted_label[i]);
    }
    output<<confusion_matrix.precision();
    t_knn_test = clock() - t_knn_test;
    std::cout << endl
        <<"Execution time: "
        <<(t_knn_test*1000)/CLOCKS_PER_SEC
        <<"ms\n\n";
    confusion_matrix.PrintEvaluation();
    std::cout<<"\n"<<std::endl;
        
    }




    // //write the predicted label into the output file
    // for(int i=0;i<class_dataset.getNbrSamples();i++){
    //     output<<predicted_label[i]<<" ";
    //     output<<endl;
    // }
    output.close();

    std::cout<<"Prediction finish, the predicted label is saved as: "<< test_label <<"_predicted.csv"<<std::endl;
    std::cout << "\n**************** Finish ****************" << std::endl;

}