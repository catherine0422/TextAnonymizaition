#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Dataset.hpp"
#include "BinaryKnnClassification.hpp"
#include "BinaryConfusionMatrix.hpp"

using namespace std;

// Prints correct usage
void msg(char* argv[]) {
        std::cout << "Usage: " << argv[0] << " <k> <train_representation> <train_label> <test_representation> <test_label> <num_points> [<output_file>]" << std::endl;
}

int main(int argc, char* argv[]) {

    std::cout << "\n******** Reading the arguments *********\n" << std::endl;

    // Checks the number of input arguments
    if (argc < 7) {
        msg(argv);
        return 1;
    }

    // Number of nearest neighbours for k-NN
    int k = atoi(argv[1]);
    if (k<1) {
        std::cout<<"Invalid value of k."<<std::endl;
        msg(argv);
        return 1;
    }

    std::cout << "\n*********** Creating dataset ***********\n" << std::endl;
    // Puts train and test files in a Dataset object
    Dataset train_dataset(argv[2],argv[3]);
    Dataset class_dataset(argv[4],argv[5]);

    // Prints dimension
    std::cout<<"Train data: ";
	train_dataset.Show(false);  // only dim and samples
    std::cout<<"Test data: ";
	class_dataset.Show(false);  // only dim and samples

 
    //Tests value of output
    std::string test_label=argv[5];
    test_label=test_label.substr(0, test_label.length()-4);
    std::ofstream out;
    if(argc==8){
        out.open(argv[7], std::ofstream::out);
    }else{
        out.open(test_label+"_roc_k"+to_string(k)+".csv", std::ofstream::out);
        std::cout<< "No file name specified for out, it will be saved as "<< test_label <<"_roc_k"<<k<<".csv"<<std::endl;
        if(out.fail()){
            std::cout<<"Cannot write into the file "<<test_label <<"_roc_k"<<k<<".csv"<<std::endl;
            msg(argv);
            exit(1);
        }
    }

    // Number of points to generate the ROC curve
    int num_points = atoi(argv[6]);



    // The last column is the class label
    int col_class=train_dataset.getDim()-1;

    // Checks if train and test are same format
    assert(train_dataset.getDim() == class_dataset.getDim());

    // Generates the list of thresholds
    double *thresholds=new double[num_points-2];
    for(int i=1;i<num_points-1;i++){
        thresholds[i-1]=(double)i/(num_points-1);
    }

    // A confusion matrix for each threshold
    BinaryConfusionMatrix* confusion_matrices = new BinaryConfusionMatrix[num_points-2];

    // Message printing
    // std::cout<< "Computing k-NN classification (k="<< k << ", classification over column "<< col_class << ")..."<<std::endl;

    // A KNN model
    std::cout << "\n************ Performing Knn ************" << std::endl;
    BinaryKnnClassification knn_class(k, &train_dataset, 2);

    // Prediction for each sample and each threshold
    std::cout << "************ Predicting Knn ************" << std::endl;
    for(int k=0;k<num_points-2;k++){
        std::cout<<"\npoint"<<k+1<<": threshold="<<thresholds[k]<<endl;
        for(int i=0;i<class_dataset.getNbrSamples();i++){
            std::vector<double> sample = class_dataset.getInstance(i);
            Eigen::VectorXd query(class_dataset.getDim()-1);
            int true_label=sample[col_class];
            for (int j=0; j<train_dataset.getDim()-1; j++) {
                query[j] = sample[j];
            }
            int predicted_label = knn_class.Estimate(query,thresholds[k]);
            confusion_matrices[k].AddPrediction(true_label, predicted_label);
        }
        confusion_matrices[k].PrintEvaluation();
    }

    // Adds (1,1) to ROC curve
    out << 1 <<"\t";
    out << 1 << endl;
    // Print the couples 'false alarm rate' 'detection rate'
    for (int t = 0; t < num_points-2; t++) {
        out << confusion_matrices[t].false_alarm_rate() <<"\t";
        out << confusion_matrices[t].detection_rate() <<endl;
    }
    // Adds (1,1) to ROC curve
    out << 0 << "\t";
    out << 0 << endl;

    // Frees the allocated memory
    delete[] confusion_matrices;
    delete[] thresholds;
    out.close();

    return 0;
}

