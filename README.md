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

### Python part

1. using label_preprocess.py to choose the wanted labels and adjust the label file accordingly:
   * As the input guide says, input first the absolute address with ' \ ' in the end
   * input the label names which you want to recognized, splitted with ' , '. Not-mentioned labels will be assigned to 0.
2. using PCA_.py to do a dimentionality reduction  to the data.
   * As the input guide says, input first the absolute address with ' \ ' in the end
   * input the target dimentionality of output data.
3. using npy_to_csv.py to transfer the npy files into csv files.

### C++ part

1. Using binary calssification to do the prediction:

   ```
   ./binary_prediction <k> <train_representation> <train_label> <test_representation> <test_label> [ <path_output_of_predicted_label> ]
   ```

   * Representation is the transformation of tokens done by "BERT"
   * The predicted labels of "test_representation" will be saved at "path_output_of_predicted_label".

2. Using Multivarious classification to do the prediction:

   ```
   ./multi_prediction <k> <train_representation> <train_label> <test_representation> <test_label> <label_to_evaluate_accuracy> <number_of_labels>[ <path_output_of_predicted_label> ]
   ```

   * The predicted labels of "test_representation" will be saved at "path_output_of_predicted_label".

3. Do the projection of dataset:

   ```
   ./random_projection <k> <projection_dim> <train_representation> <train_label> <test_representation> <test_label> <sampling>
   ```

   * "sampling" can be set as "Gaussian" or "Rademacher".
   * The projected "train_representation" and "test_representation" will be saved as "train_representation_projected_[projection_dimention]" and "test_representation_projected_[projection_dimention]".

4. Using a predicted label to do the anonymization:

   ```
   ./anonymization <original_text> <predicted_label> <label_to_anonymize> [ <output_path_of_anonymized_text> ]
   ```

   * The anonymized text will be saved at "output_path_of_anonymized_text".

5. Making a roc curve :

   ```
   ./roc_curve <k> <train_representation> <train_label> <test_representation> <test_label> <num_points> [<output_file>]
   ```

   * number_points on the roc_curve will be saved at "output_file".

## Example

We use the data "mail" to give an example of usage.

1. To do the projection of dataset:

   ```
   ./random_projection 3 10 ../data/test/mail_train_rep.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep.csv ../data/test/mail_test_label.csv Gaussian
   ```

   * Then you can see the file "mail_test_rep_projected_d10.csv" and "mail_train_rep_projected_10.csv" in ../data/test.

2. To use the binary classification:

   ```
   ./binary_prediction 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv
   ```

   * Then you can see the file "mail_test_label_predicted.csv" in ../data/test.

3. To use the multivarious classification:

   ```
   ./multi_prediction 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv 1 2
   ```

   * Then you can see the file "mail_test_label_multi_predicted.csv" in ../data/test.

4. To make the roc curve:

   ```
   ./roc_curve 3 ../data/test/mail_train_rep_projected.csv ../data/test/mail_train_label.csv ../data/test/mail_test_rep_projected.csv ../data/test/mail_test_label.csv 5 
   ```

   * Then you can see the file "mail_test_label_roc_d10.csv" in ../data/test.

5. To anonymize a text:

   ```
   ./anonymization ../data/eng.testa ../data/binary_labels.testa.csv 1
   ```

   * Then you can see the file "eng.testa_anonymized.txt" in ../data.

