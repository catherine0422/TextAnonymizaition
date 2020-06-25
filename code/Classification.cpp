#include "Classification.hpp"
#include "Dataset.hpp"

Classification::Classification(Dataset* dataset) {
    m_dataset = dataset;
    m_col_class = dataset->getDim()-1;
}

Dataset* Classification::getDataset(){
    return m_dataset;
}

int Classification::getColClass(){
    return m_col_class;
}