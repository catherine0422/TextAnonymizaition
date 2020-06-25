#include "MultiConfusionMatrix.hpp"
#include <iostream>

using namespace std;

MultiConfusionMatrix::MultiConfusionMatrix(int label):ConfusionMatrix() {
    m_label=label;
}

MultiConfusionMatrix::~MultiConfusionMatrix() {
}

void MultiConfusionMatrix::AddPrediction(int true_label, int predicted_label) {
    if(true_label!=m_label){
        if(predicted_label!=m_label){
            m_confusion_matrix[0][0]++;
        }else{
            m_confusion_matrix[0][1]++;
        }
    }else{
        if(predicted_label!=m_label){
            m_confusion_matrix[1][0]++;
        }else{
            m_confusion_matrix[1][1]++;
        }
    }
}

void MultiConfusionMatrix::PrintEvaluation() const{
    // Prints the confusion matrix
    cout <<"\t\tPredicted\n";
    cout <<"\t\tothers\t"<<m_label<<"\n";
    cout <<"Actual\tothers\t"
        <<GetTN() <<"\t"
        <<GetFP() <<endl;
    cout <<"\t"<<m_label<<"\t"
        <<GetFN() <<"\t"
        <<GetTP() <<endl <<endl;
    // Prints the estimators
    cout <<"Error rate\t\t"
        <<error_rate() <<endl;
    cout <<"False alarm rate\t"
        <<false_alarm_rate() <<endl;
    cout <<"Detection rate\t\t"
        <<detection_rate() <<endl;
    cout <<"F-score\t\t\t"
        <<f_score() <<endl;
    cout <<"Precision\t\t"
        <<precision() <<endl;
}
