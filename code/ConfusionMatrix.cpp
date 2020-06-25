#include "ConfusionMatrix.hpp"
#include <iostream>

using namespace std;

ConfusionMatrix::ConfusionMatrix() {
    // Populate 2x2 matrix with 0s 
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            m_confusion_matrix[i][j]=0;
        }
    }
}

ConfusionMatrix::~ConfusionMatrix() {
}


int ConfusionMatrix::GetTP() const {
    return m_confusion_matrix[1][1];
}

int ConfusionMatrix::GetTN() const {
   return m_confusion_matrix[0][0];
}

int ConfusionMatrix::GetFP() const {
    return m_confusion_matrix[0][1];
}

int ConfusionMatrix::GetFN() const {
   return m_confusion_matrix[1][0];
}

double ConfusionMatrix::f_score() const {
    return (2*precision()*detection_rate())/(precision()+detection_rate());
}

double ConfusionMatrix::precision() const {
    return (double)GetTP()/(GetTP()+GetFP());

}

double ConfusionMatrix::error_rate() const {
    return (double)(GetFP()+GetFN())/(GetTP()+GetFP()+GetTN()+GetFN());
}

double ConfusionMatrix::detection_rate() const {
    return (double)GetTP()/(GetTP()+GetFN());
}

double ConfusionMatrix::false_alarm_rate() const {
    return (double)GetFP()/(GetFP()+GetTN());
}
