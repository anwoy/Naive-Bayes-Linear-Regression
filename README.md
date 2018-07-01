# Naive-Bayes-Linear-Regression

## About
Designed for cases where massive number of predictors are present. Code learns model parameters using iterative Expectation-Maximization method and handles missing data within Bayesian framework. Designed for massive datasets which can’t be loaded onto main memory in one go – batch wise processing is done for training model parameters.

## compile
```
g++ source.cpp -o nblr
```
## usage
```
nblr --convert_to_binary <textfile> <binarydatfilename>
nblr --convert_to_text <binarydatfile> <textfilename>
nblr --learnML <preddatfile> <Otxtfile> <MOdatfiletosavein>
nblr --learnML <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>
nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfiletosavein>
nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>
nblr --predict <preddatfile> <Onewtxtfilename> <MOdatfile>
nblr --displayMO <MOdatfile>
```
### predictors text file format
```
<number of rows>
<number of columns>
data
```
