#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/** @file
*/

// Prints correct usage
void msg(char* argv[]) {
    std::cout << "Usage: " << argv[0] << "<original_text> <predicted_label> <label_to_anonymize> [ <anonymized_text> ]" << std::endl;
}

int main(int argc, char* argv[]) {

    std::cout << "\n******** Reading the arguments *********\n" << std::endl;

    if (argc < 4) {
		msg(argv);
		return 1;
    }

    // Tests value of original_text
    std::string data_original=argv[1];
    std::ifstream input(data_original);
    if (input.fail()) {
		std::cout<<"Cannot read from file "<<data_original<<" !"<<std::endl;
        msg(argv);
		exit(1);
	}

    // Tests value of predicted_label
    std::string predicted_label=argv[2];
    std::ifstream label(predicted_label);
    if (label.fail()) {
		std::cout<<"Cannot read from file "<<predicted_label<<" !"<<std::endl;
        msg(argv);
		exit(1);
	}

    // Tests value of label_to_anonymize
    int label_to_anonymize=atoi(argv[3]);
	if (label_to_anonymize<0) { 
		std::cout<<"Invalid value of label_to_anonymize:"<<label_to_anonymize<<std::endl;
		msg(argv);
		return 1;
	}

    // Tests value of anonymized_text
    std::ofstream output;
    if(argc==5){
        output.open(argv[4], std::ofstream::out | std::ofstream::app);
    }else{
        output.open(data_original+"_anonymized.txt", std::ofstream::out | std::ofstream::app);
        std::cout<< "No file name specified for anonymized output, it will be saved as "<< data_original <<"_anonymized.txt"<<std::endl;
        if(output.fail()){
            std::cout<<"Cannot write into the file "<<data_original<<"_anonymized.txt !"<<std::endl;
            msg(argv);
            exit(1);
        }
    }
    std::ofstream outpu_original(data_original+"_original.txt");
    std::cout<< "The original text will be saved as "<< data_original <<"_original.txt"<<std::endl;
    
    // Anonymize the original text 
    std::string line_text,line_label, word;
    std::cout << "********* Anonymizing the text *********\n" << std::endl;
    int row=0;
    while (getline(input, line_text)) {
        if(line_text==""){
            //test if the line is empty
            output<<" ";
            outpu_original<<" ";
        }else{
            stringstream s(line_text);
            //get the word(first element in a line)
            getline(s, word, ' ');
            if(word=="-DOCSTART-"){
                //test if it's a new document
                output<<endl;
                output<<endl;
                outpu_original<<endl;
                outpu_original<<endl;
            }else{
                getline(label, line_label);
                if(atoi(line_label.c_str())==label_to_anonymize){
                    //if the predicted lable is 1(person), anonymize the word
                    output<<"***"<<" ";
                }else{
                    output<<word<<" ";
                }
                outpu_original<<word<<" ";
            }
        }
        row++;
	}
    std::cout<<"Anonymization finish, the anonymized text is saved at: "<<data_original<<"_anonynized.txt"<<std::endl;
    std::cout<<"The original text is saved at: "<<data_original<<"_original.txt"<<std::endl;
	input.close();
    output.close();
    outpu_original.close();
    std::cout << "\n**************** Finish ****************" << std::endl;
}