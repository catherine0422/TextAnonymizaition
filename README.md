# README

## Background

This program can be used to anonymize the personal information in the text. 
It uses the dataset ConLL2003 preprocessed on using "BERT".

## Requirement

1. Python
2. C++
3. Ann
4. Eigen

## Installation 

1. Install [Eigen](https://www.enseignement.polytechnique.fr/informatique/INF442/TD/TD6/eigen-eigen-323c052e1731.tar)

2. Install [ANN](https://www.cs.umd.edu/users/mount/ANN/Files/1.1.2/ann_1.1.2.zip)

3. Enter into the folder "code", according to where you install it, change the paths of Eigen and Ann in the Makefile.

   ```
   EIGEN = your path of folder "eigen-eigen-323c052e1731"
   ANN_INCLUDE = your path of folder "ann_1.1.2/include"
   ANN_LIB = your path of folder "ann_1.1.2/lib"
   ```

4. Run Makefile.

## Usage 

We need to tap commands in the command line.

1. Using binary calssification to do the prediction:

		```
./binary_prediction <k> <train_representation> <train_label> <test_representation> <test_label> [ <path_output_of_predicted_label> ]
	```
	
	
	1) Representation is the transformation of tokens done by "BERT"
	2) The predicted labels of "test_representation" will be saved at "path_output_of_predicted_label".
	
2. Using Multivarious classification to do the prediction:

  	```
  	./multi_prediction <k> <train_representation> <train_label> <test_representation> <test_label> <label_to_evaluate_accuracy> <number_of_labels>[ <path_output_of_predicted_label> ]
  	```
  	
  	  1) The predicted labels of "test_representation" will be saved at "path_output_of_predicted_label".
  	
3. Do the projection of dataset:

   ```
   ./random_projection <k> <projection_dim> <train_representation> <train_label> <test_representation> <test_label> <sampling>
   ```


     1) "sampling" can be set as "Gaussian" or "Rademacher".
     2) The projected "train_representation" and "test_representation" will be saved as "train_representation_projected_[projection_dimention]"
   and "test_representation_projected_[projection_dimention]".

4. Using a predicted label to do the anonymization:

   ```
   ./anonymization <original_text> <predicted_label> <label_to_anonymize> [ <output_path_of_anonymized_text> ]
   ```

   1) The anonymized text will be saved at "output_path_of_anonymized_text".

5. Making a roc curve :	

   ```
   ./roc_curve <k> <train_representation> <train_label> <test_representation> <test_label> <num_points> [<output_file>]
   ```

   1) #number_of_points on the roc_curve will be saved at "output_file".

## Example 

We use the data "mail" to give an example of usage.

1. To do the projection of dataset:

   ```
   ./random_projection 3 10 ../data/test/mail_train_rep.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep.csv ../data/test/mail_test_label.csv Gaussian
   ```

   1) Then you can see the file "mail_test_rep_projected_d10.csv" and "mail_train_rep_projected_10.csv" in ../data/test.

2. To use the binary calssification:

  	```
  	./binary_prediction 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv
  	```
  	
  	1) Then you can see the file "mail_test_label_predicted.csv" in ../data/test.
  	
3. To use the multivarious classification:

  ```
  ./multi_prediction 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv 1 2
  ```

  1) Then you can see the file "mail_test_label_multi_predicted.csv" in ../data/test.

4. To make the roc curve:

  ```
  ./roc_curve 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv 5 
  ```

  1) Then you can see the file "mail_test_label_roc_d10.csv" in ../data/test.

5. To anonymize a text:

  ```
  ./anonymization ../data/eng.testa ../data/binary_labels.testa.csv 1
  ```

  1) Then you can see the file "eng.testa_anonymized.txt" in ../data.



