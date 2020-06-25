EIGEN=../../lecture6/eigen-eigen-323c052e1731
ANN_INCLUDE=../../lecture6/ann_1.1.2/include
ANN_LIB=../../lecture6/ann_1.1.2/lib

all: test_dataset anonymization binary_prediction multi_prediction roc_curve random_projection

Dataset.o: Dataset.cpp
	g++ -c -I$(EIGEN) -Wall -Wextra Dataset.cpp

Classification.o: Classification.cpp
	g++ -c -I$(EIGEN) -Wall -Wextra Classification.cpp
	
KnnClassification.o: KnnClassification.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra KnnClassification.cpp

RandomProjection.o: RandomProjection.cpp
	g++ -c -I$(EIGEN) -std=c++11 -Wall -Wextra RandomProjection.cpp		

BinaryKnnClassification.o: BinaryKnnClassification.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra BinaryKnnClassification.cpp

MultiKnnClassification.o: MultiKnnClassification.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra MultiKnnClassification.cpp

ConfusionMatrix.o: ConfusionMatrix.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra ConfusionMatrix.cpp	

BinaryConfusionMatrix.o: BinaryConfusionMatrix.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra BinaryConfusionMatrix.cpp	

MultiConfusionMatrix.o: MultiConfusionMatrix.cpp
	g++ -c -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra MultiConfusionMatrix.cpp	

test_dataset: test_dataset.cpp Dataset.o
	g++ -I$(EIGEN) -Wall -Wextra test_dataset.cpp Dataset.o -o test_dataset

anonymization: anonymization.cpp 
	g++ -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra anonymization.cpp -o anonymization -L$(ANN_LIB) -lANN

binary_prediction: binary_prediction.cpp BinaryConfusionMatrix.o ConfusionMatrix.o BinaryKnnClassification.o KnnClassification.o Classification.o Dataset.o
	g++ -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra binary_prediction.cpp BinaryConfusionMatrix.o ConfusionMatrix.o BinaryKnnClassification.o KnnClassification.o Classification.o Dataset.o -o binary_prediction -L$(ANN_LIB) -lANN

multi_prediction: multi_prediction.cpp MultiConfusionMatrix.o ConfusionMatrix.o MultiKnnClassification.o KnnClassification.o Classification.o Dataset.o
	g++ -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra multi_prediction.cpp MultiConfusionMatrix.o ConfusionMatrix.o MultiKnnClassification.o KnnClassification.o Classification.o Dataset.o -o multi_prediction -L$(ANN_LIB) -lANN

roc_curve: roc_curve.cpp BinaryConfusionMatrix.o ConfusionMatrix.o BinaryKnnClassification.o KnnClassification.o Classification.o Dataset.o
	g++ -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra roc_curve.cpp BinaryConfusionMatrix.o ConfusionMatrix.o BinaryKnnClassification.o KnnClassification.o Classification.o Dataset.o -o roc_curve -L$(ANN_LIB) -lANN

random_projection: random_projection.cpp RandomProjection.o BinaryConfusionMatrix.o ConfusionMatrix.o BinaryKnnClassification.o knnClassification.o Classification.o Dataset.o
	g++ -I$(EIGEN) -I$(ANN_INCLUDE) -Wall -Wextra random_projection.cpp RandomProjection.o ConfusionMatrix.o BinaryConfusionMatrix.o BinaryKnnClassification.o knnClassification.o Classification.o Dataset.o -o random_projection -L$(ANN_LIB) -lANN


.PHONY: all clean

clean:
	rm -f *.o
	rm -f test_dataset
	rm -f anonymization
	rm -f binary_prediction
	rm -f multi_prediction
	rm -f roc_curve
	rm -f random_projection