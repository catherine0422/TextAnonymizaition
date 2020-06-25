
#include "KnnClassification.hpp"
#include <iostream>
#include <ANN/ANN.h>

 
KnnClassification::KnnClassification(int k, Dataset* dataset)
: Classification(dataset) {
    m_k=k;
    int d=dataset->getDim();
    int n=dataset->getNbrSamples();
    int col_class=d-1;

    ANNpointArray dataPts;
    dataPts = annAllocPts(n,d-1);	
    for(int i=0;i<n;i++){
        for(int j=0;j<col_class;j++){
            dataPts[i][j]=dataset->getInstance(i)[j];
        }
        for(int j=col_class+1;j<d;j++){
            dataPts[i][j-1]=dataset->getInstance(i)[j];
        }
    }
    m_kdTree = new ANNkd_tree(dataPts,n,d-1);
} 

KnnClassification::~KnnClassification() {
    delete m_kdTree;
	annClose();	
}


int KnnClassification::getK() {
    return m_k;
}

ANNkd_tree* KnnClassification::getKdTree() {
    return m_kdTree;
}
