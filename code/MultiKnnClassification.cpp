
#include "MultiKnnClassification.hpp"
#include <iostream>
#include <ANN/ANN.h>

 
MultiKnnClassification::MultiKnnClassification(int k, Dataset* dataset,int n_label)
: KnnClassification(k,dataset) {
    m_n_label=n_label;
} 

MultiKnnClassification::~MultiKnnClassification() {

}

int MultiKnnClassification::Estimate(const Eigen::VectorXd & x, double threshold) {
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
    int *pro=new int[m_n_label];
    for(int i=0;i<m_k;i++){
        int index=(int)m_dataset->getInstance(nnIdx[i])[m_col_class];
        pro[index]++;
    }
    int label=0;
    // std::cout<<"index: "<<0<<"; value:"<<pro[0]<<std::endl;
    for(int i=1;i<m_n_label;i++){
        // std::cout<<"index: "<<i<<"; value:"<<pro[i]<<std::endl;
        if(pro[i]>pro[label]){
            label=i;
        }
    }
    // std::cout<<"chosse index: "<<label<<std::endl;

    // clean things up
    delete [] nnIdx;
    delete [] dists;
    delete queryPt;
    return label;

}

int MultiKnnClassification::getNLabel() {
    return m_n_label;
}

