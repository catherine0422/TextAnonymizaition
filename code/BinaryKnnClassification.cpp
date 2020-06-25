
#include "BinaryKnnClassification.hpp"
#include <iostream>
#include <ANN/ANN.h>

 
BinaryKnnClassification::BinaryKnnClassification(int k, Dataset* dataset,int n_label)
: KnnClassification(k,dataset) {
    m_n_label=n_label;
} 

BinaryKnnClassification::~BinaryKnnClassification() {

}

int BinaryKnnClassification::Estimate(const Eigen::VectorXd & x, double threshold) {
    ANNpoint queryPt;
    ANNidxArray	nnIdx;	
    ANNdistArray dists;
    queryPt = annAllocPt(x.size());
    for(int i=0;i<x.size();i++){
        queryPt[i]=x[i];
    }
    nnIdx = new ANNidx[m_k];
    dists = new ANNdist[m_k];	
    m_kdTree->annkSearch(queryPt,m_k,nnIdx,dists,0);
    double pro=0;
    for(int i=0;i<m_k;i++){
        pro+=m_dataset->getInstance(nnIdx[i])[m_col_class];
    }
    pro/=(double)m_k;

    // clean things up
    delete [] nnIdx;
    delete [] dists;
    delete queryPt;
    if(pro>=threshold){
        return 1;
    }else{
        return 0;
    }

}

int BinaryKnnClassification::getNLabel() {
    return m_n_label;
}

