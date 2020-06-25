#include "BinaryConfusionMatrix.hpp"
#include <iostream>

using namespace std;

BinaryConfusionMatrix::BinaryConfusionMatrix():ConfusionMatrix() {
}

BinaryConfusionMatrix::~BinaryConfusionMatrix() {
}

void BinaryConfusionMatrix::AddPrediction(int true_label, int predicted_label) {
    m_confusion_matrix[true_label][predicted_label]++;
}

void BinaryConfusionMatrix::PrintEvaluation() const{
    // Prints the confusion matrix
    cout <<"\t\tPredicted\n";
    cout <<"\t\t0\t1\n";
    cout <<"Actual\t0\t"
        <<GetTN() <<"\t"
        <<GetFP() <<endl;
    cout <<"\t1\t"
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

