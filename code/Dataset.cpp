
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Dataset.hpp"

using namespace std;
int Dataset::getNbrSamples() {
	return m_nsamples;
}

int Dataset::getDim() {
	return m_dim;
}

Dataset::~Dataset() {
	// All attributes have destructors
}

void Dataset::Show(bool verbose) {
	std::cout<<"Dataset with "<<m_nsamples<<" samples, and "<<m_dim<<" dimensions."<<std::endl;
	if (verbose) {
		for (int i=0; i<m_nsamples; i++) {
			for (int j=0; j<m_dim; j++) {
				std::cout<<m_instances[i][j]<<" ";
			}
			std::cout<<std::endl;		
		}
	}
}

Dataset::Dataset(const char* representation_file,const char* label_file)
 {
	m_nsamples = 0;
	m_dim = -1;

	std::ifstream rep(representation_file);
	std::ifstream lab(label_file);
	
	if (rep.fail()) {
		std::cout<<"Cannot read from file "<<representation_file<<" !"<<std::endl;
		exit(1);
	}

	if (lab.fail()) {
		std::cout<<"Cannot read from file "<<label_file<<" !"<<std::endl;
		exit(1);
	}
	
	
	std::vector<double> row; 
    std::string line_rep, line_lab, word; 

	while (getline(rep, line_rep)) {
		getline(lab, line_lab);
		if(line_lab==""){
			std::cerr << "ERROR, inconsistent dataset: reprensentation file and label file has different number of samples." << std::endl;
        	exit(-1);
		}
		row.clear();
        std::stringstream s(line_rep);
        int ncols = 0;
        while (getline(s, word, ',')) { 
            // add all the column data 
            // of a row in representation to a vector 
            double val = std::atof(word.c_str());
            row.push_back(val);
            ncols++;
        }
		// add the lable at last of the vector 
		int val_label=std::atoi(line_lab.c_str());
		row.push_back(val_label);
		ncols++;
        m_instances.push_back(row);
        if (m_dim==-1) m_dim = ncols;
        else if (m_dim!=ncols) {
        	std::cerr << "ERROR, inconsistent dataset: there is a row with different dimension." << std::endl;
        	exit(-1);
        }
		m_nsamples ++;
	}
	rep.close();
	lab.close();
}

Dataset::Dataset(const std::vector<std::vector<double> > &vector_of_vector) {
	m_instances = vector_of_vector;
	m_dim = vector_of_vector[0].size();
	m_nsamples = vector_of_vector.size();
}

std::vector<double> Dataset::getInstance(int i) {
	return m_instances[i];
}

void Dataset::Save(const char *file_name){
	std::ofstream output(file_name);
	for(int i=0;i<m_nsamples;i++){
		std::vector<double> sample = m_instances[i];
		for(int j=0;j<m_dim-1;j++){
			output<<sample[j];
			output<<",";
		}
		output<<endl;
	}
	output.close();
}