# Project 2: Predicting Stock Returns using Data Analysis and Machine Learning
This project is to predict stock price returns in financial markets based on the application of machine learning models.
The focus will be geared towards the basic steps that are required for carrying out a data analysis project and
implementation of the machine learning models, followed by analysis of their advantages/disadvantages.

## Required Packages
`python 3.7+`, `pandas`, `numpy`, `matplotlib`, `pandas_datareader`, `sklearn`, `warnings`, `yfinance`, `itertools`.

Note that the `itertools` package is only needed if you are running the neural network and desire to see the prediction
truth table.

## Required Datasets

The files: `tickers.nasd.csv`, `tickers.nyse.csv`, `tickers.csv` must be in the same directory as
`Gabriel_Roy_StockPredictor.py`. Further, to be able to run `Gabriel_Roy_StockPredictor.py`, the file
`Gabriel_Roy_utils.py` must be in the same directory as well.

The Jupyter Notebook `Gabriel_Roy_Project2.ipynb` shows a visualization and analyzes of the output from the model.

## Description

The main class to import is `StockPredictor` from the `Gabriel_Roy_StockPredictor.py` file.
It requires a start date, an end date, a ticker symbol, and a flag denoting whether you are passing the large
or small ticker sample dataset.

Once the class is initialized, it immediately feature engineers variables (macroeconomic indicators
and statistical, technical indicators) while handling missing data and normalizing the data when appropriate.
It then outputs the results to a csv file in the same directory for each dataset (samll and large). It is worth noting that
the truth tables are saved to the `small_img` and `large_img` directories if needed. The classification reports can be
printed to console if you uncomment the code. Lastly, more models have been already implemented for the user, such as
LSTM Neural Network, Logistic Regression, and K-Nearest Neighbor. The user can freely uncomment the code and use those models
if they wish.

## Running the code

Best if used with PyCharm or VS Code. However, you can run the code from terminal/CMD as well by navigating
to the directory where the `Gabriel_Roy_StockPredictor.py` is located and running the python command.