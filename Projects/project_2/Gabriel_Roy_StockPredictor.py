import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

from Gabriel_Roy_utils import *

import yfinance as yf
import pandas_datareader.data as pdr

import warnings

warnings.filterwarnings('ignore')

from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn import metrics

from keras.models import Sequential
from keras.layers import LSTM, Dense, Dropout, Flatten


class StockPredictor:
    def __init__(self, start_date, end_date, ticker, flag):
        """
        Initializes the StockPredictor class and runs the classification algorithms.
        :param start_date: a string denoting the start date
        :param end_date: a string denoting the end date
        :param ticker: a string denoting the ticker symbol
        :param flag: a str denoting whether small or large dataset (must be one of `small` or `large`)
        """
        # Initialize the necessary vars
        self.start_date = start_date
        self.end_date = end_date
        self.ticker = ticker
        self.drop_cols = ["Open", "High", "Low", "Close", "Volume"]
        self.y_pred = {}
        self.metrics = {}
        self.models = {}
        self.opt_mod = None
        self.seed = 903308738
        self.flag = flag
        self.path = os.getcwd()

        # create directory to store truth tables
        if self.flag == "small":
            if os.path.exists(self.path + '/small_img'):
                self.img_path = self.path + '/small_img'
            else:
                os.makedirs(self.path + '/small_img')
                self.img_path = self.path + '/small_img'
        else:
            if os.path.exists(self.path + '/large_img'):
                self.img_path = self.path + '/large_img'
            else:
                os.makedirs(self.path + '/large_img')
                self.img_path = self.path + '/large_img'

        print("Obtaining Macro Data...")
        self.macro_df = self.get_macro_data()
        print("Obtaining Stock Data...")
        self.stock_df = self.get_raw_data()
        print("Feature Engineering Data...")
        self.stock_df = self.get_features(self.stock_df)
        print("Merging Datasets...")
        self.panel_data = self.merge_datasets()
        print("Cleaning Data...")
        self.panel_data = self.clean_features(self.panel_data)
        print("Creating Target Variable...")
        self.panel_data = self.get_labels()
        print("Creating Cleaned Model Inputs...")
        self.get_model_inputs()
        print("Running Models...")
        self.opt_stats = self.run_models()

        # store optimal model
        self.opt_stats.loc["Optimal Model"] = self.opt_mod

    def get_macro_data(self, tickers=['USREC', 'DFF', 'DCOILWTICO', 'UMCSENT', 'UNRATE']):
        """
        A function to obtain macroeconomic indicators
        :param tickers: a list of ticker sybmols of macro indicators
        :return: macroeconomic indicator dataframe
        """
        # recession, fed fund rate, crude oil, michigan index, unemployment rate
        macro_df = pdr.DataReader(tickers, 'fred', self.start_date, self.end_date)
        # handle missing data
        macro_df = macro_df.ffill()

        # obtain log returns of crude oil
        macro_df['DCOILWTICO'] = np.log(macro_df['DCOILWTICO']).diff()
        return macro_df

    def get_raw_data(self):
        """
        A function to get raw price series of a ticker extracted via yahoo finance API
        :return: a dataframe of the price series
        """
        stock_data = yf.download(self.ticker, self.start_date, self.end_date)
        stock_data = stock_data.drop(columns=['Close']).rename(columns={'Adj Close': 'Close'})
        # self.stock_cols = self.stock_data.columns.map('{0[0]}_{0[1]}'.format)
        # stock_data.columns = stock_cols
        return stock_data

    def get_features(self, df):
        """
        A function to feature engineer variables
        :param df: the dataframe to calculate statistical and technical indicators
        :return: dataframe with new featured variables
        """

        df[f'sma'], df[f'b_up'], df[f'b_down'] = get_BB(df[f'Close'])
        df[f'D+'], df[f'D-'], df[f'ADX'] = get_ADX(df[f'High'], df[f'Low'], df[f'Close'])
        df[f'macd'], df[f'macd_h'], df[f'macd_s'] = get_MACD(df[f'Close'])
        df[f'rsi'] = get_RSI(df[f'Close'])
        df[f'atr'] = get_ATR(df[f'High'], df[f'Low'], df[f'Close'])
        df[f'pivot'], df[f'r1'], df[f's1'], df[f'r2'], df[f's2'], \
            df[f'r3'], df[f's3'] = get_PIVOT(df[f'High'], df[f'Low'], df[f'Close'])

        df[f'ret_1d'] = np.log(df[f'Close']).diff(1)
        df[f'ret_1w'] = np.log(df[f'Close']).diff(5)
        df[f'ret_1m'] = np.log(df[f'Close']).diff(21)
        df[f'ret_3m'] = np.log(df[f'Close']).diff(60)
        df[f'ret_6m'] = np.log(df[f'Close']).diff(120)
        df[f'ret_1y'] = np.log(df[f'Close']).diff(250)

        df[f'std_1w'] = df[f'ret_1d'].rolling(5).std()
        df[f'std_1m'] = df[f'ret_1d'].rolling(21).std()
        df[f'std_3m'] = df[f'ret_1d'].rolling(60).std()
        df[f'std_6m'] = df[f'ret_1d'].rolling(120).std()
        df[f'std_1y'] = df[f'ret_1d'].rolling(250).std()

        df[f'vol_1d'] = np.log(df[f'Volume']).diff(1)
        df[f'vol_1w'] = np.log(df[f'Volume']).diff(5)
        df[f'vol_1m'] = np.log(df[f'Volume']).diff(21)
        df[f'vol_3m'] = np.log(df[f'Volume']).diff(60)
        df[f'vol_6m'] = np.log(df[f'Volume']).diff(120)
        df[f'vol_1y'] = np.log(df[f'Volume']).diff(250)

        df[f'vol_std_1w'] = df[f'vol_1d'].rolling(5).std()
        df[f'vol_std_1m'] = df[f'vol_1d'].rolling(21).std()
        df[f'vol_std_3m'] = df[f'vol_1d'].rolling(60).std()
        df[f'vol_std_6m'] = df[f'vol_1d'].rolling(120).std()
        df[f'vol_std_1y'] = df[f'vol_1d'].rolling(250).std()

        # drop unnecessary columns
        df = df.loc[:, ~df.columns.isin(self.drop_cols)]
        return df

    def merge_datasets(self):
        """
        A function to merge all the datasets with the indicators
        :return: merged dataframe
        """
        panel_data = self.stock_df.merge(self.macro_df, left_index=True, right_index=True, how="right")
        panel_data = panel_data.loc[:, ~panel_data.columns.isin(self.drop_cols)]
        return panel_data

    def clean_features(self, df, corr_drop=0.9):
        """
        Cleans the features in the passed dataframe
        :param df: a dataframe with all engineered features
        :param corr_drop: max value of correlation between stocks (if higher the feature will drop)
        :return: cleaned dataframe
        """
        # Handle missing data
        df = df.ffill().interpolate()
        df = df[df['ret_1y'].notna()]
        df = df.fillna(df.mean())

        # drop highly correlated columns
        df_corr = df.corr().abs()
        upper_triangular_df = df_corr.where(np.triu(np.ones(df_corr.shape), k=1).astype(np.bool))
        corr_cols = [col for col in upper_triangular_df.columns if any(upper_triangular_df[col] > corr_drop)]
        df = df.drop(columns=corr_cols, axis=1)
        return df

    def get_labels(self):
        """
        Function to create the response variable (y-variable) or dependent variable
        :return: dataframe with target variable
        """
        # must be 1 year so no cheating
        self.panel_data['Future_Yearly_Ret'] = self.panel_data['ret_1y'].shift(-250).apply(
            lambda x: 1 if x > 0 else 0)
        return self.panel_data

    def get_model_inputs(self, test_size=0.4):
        """
        A function to split training and testing variables (train = 60%, test = 40% default)
        :param test_size: the percentage of testing (defaults to 40%)
        """
        self.X = self.panel_data.loc[:, self.panel_data.columns != 'Future_Yearly_Ret']
        self.y = self.panel_data.loc[:, 'Future_Yearly_Ret']

        # last minute cleaning if needed
        self.X = self.X.replace([np.inf, -np.inf], np.nan)
        self.X = self.X.bfill()

        # split into training and testing
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(
            self.X, self.y, test_size=test_size, shuffle=False)

        # standardize the inputs
        sc = StandardScaler()
        self.X_train = sc.fit_transform(self.X_train)
        self.X_test = sc.transform(self.X_test)

    def get_LR(self, cv=5):
        """
        A function to implement Logistic Regression
        :param cv: Cross Validation Constant
        """
        # tune hyperparameters and use them dynamically
        lr = LogisticRegression()
        grid_dict = {"C": np.logspace(-3, 3, 7),
                     "penalty": ["l1", "l2", "elasticnet"],
                     "random_state": [self.seed]}
        lr_cv = GridSearchCV(lr, grid_dict, cv=cv)
        lr_cv.fit(self.X_train, self.y_train)

        optimal_lr = LogisticRegression(**lr_cv.best_params_)
        optimal_lr.fit(self.X_train, self.y_train)
        self.y_pred['LR'] = optimal_lr.predict(self.X_test)

        self.models['LR'] = optimal_lr

    def get_KNN(self, cv=5):
        """
        A function to implement K-Nearest-Neighbors
        :param cv: Cross Validation Constant
        """
        # tune hyperparameters and use them dynamically
        knn = KNeighborsClassifier()
        grid_dict = {"n_neighbors": np.linspace(5, 100, 5).astype(int),
                     "weights": ["uniform", "distance"],
                     "algorithm": ["ball_tree", "kd_tree", "brute"]}
        knn_cv = GridSearchCV(knn, grid_dict, cv=cv)
        knn_cv.fit(self.X_train, self.y_train)

        optimal_knn = KNeighborsClassifier(**knn_cv.best_params_)
        optimal_knn.fit(self.X_train, self.y_train)
        self.y_pred['KNN'] = optimal_knn.predict(self.X_test)

        self.models['KNN'] = optimal_knn

    def get_SVC(self, cv=5):
        """
        A function to implement Support Vector Machine
        :param cv: Cross Validation Constant
        """
        # tune hyperparameters and use them dynamically
        svc = SVC()
        grid_dict = {"C": [0.1, 1, 10, 100],
                     "gamma": [0.001, 0.01, 0.1, 1],
                     "kernel": ["rbf", "poly", "sigmoid"],
                     "random_state": [self.seed]}
        svc_cv = GridSearchCV(svc, grid_dict, cv=cv)
        svc_cv.fit(self.X_train, self.y_train)

        optimal_svc = SVC(**svc_cv.best_params_)
        optimal_svc.fit(self.X_train, self.y_train)
        self.y_pred['SVC'] = optimal_svc.predict(self.X_test)

        self.models['SVC'] = optimal_svc

    def get_RF(self, cv=5):
        """
        A function to implement Random Forest Classification
        :param cv: Cross Validation Constant
        """
        # tune hyperparameters and use them dynamically
        rf = RandomForestClassifier()
        grid_dict = {"n_estimators": [200, 500],
                     "criterion": ["gini", "entropy", "log_loss"],
                     "random_state": [self.seed]}
        rf_cv = GridSearchCV(rf, grid_dict, cv=cv)
        rf_cv.fit(self.X_train, self.y_train)

        optimal_rf = RandomForestClassifier(**rf_cv.best_params_)
        optimal_rf.fit(self.X_train, self.y_train)
        self.y_pred['RF'] = optimal_rf.predict(self.X_test)

        self.models['RF'] = optimal_rf

    def get_NN(self):
        """
        A function to implement LSTM Neural Network
        """
        # Fix shape of input data
        X_train = np.reshape(self.X_train,
                             (self.X_train.shape[0], self.X_train.shape[1], 1))

        X_test = np.reshape(self.X_test,
                            (self.X_test.shape[0], self.X_test.shape[1], 1))

        # Create NN structure
        nn = Sequential()
        nn.add(LSTM(units=32, return_sequences=True, input_shape=(X_train.shape[1], 1)))
        nn.add(LSTM(units=32))
        nn.add(Dropout(0.2))
        nn.add(Flatten())

        # output one value (Dense layer)
        nn.add(Dense(units=1, activation='hard_sigmoid'))

        nn.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy', 'Precision', 'Recall'])
        nn.fit(X_train, self.y_train, epochs=20, batch_size=32)
        print(nn.summary())

        # change predictions to binary
        nn_predictions = nn.predict(X_test)
        self.y_pred['NN'] = np.where(nn_predictions > np.median(nn_predictions), 1, 0).reshape(-1)

        self.models['NN'] = nn

    def get_report(self, model, model_name):
        """
        A function to obtain the classification report of each model used, uncomment the lines of code to print to console
        :param model: the ML model that was trained
        :param model_name: a string denoting the name of the model
        """

        if model_name == "NN":
            # print(f"Classification Report for NN\n\n")
            # print(metrics.classification_report(self.y_test, self.y_pred[model_name], target_names=['Bullish', 'Bearish']))
            #
            # cm = metrics.confusion_matrix(self.y_test, self.y_pred[model_name], labels=list)
            # plot_labels = ["Bullish", "Bearish"]
            # self.plot_nn_report(cm, plot_labels)
            print(
                "Skipping Result print to console due to assignment submission...uncomment lines above 337 to observe output!")

        else:

            # print(f"Classification Report for {model_name}\n\n")
            # print(metrics.classification_report(self.y_test, self.y_pred[model_name], target_names=['Bullish', 'Bearish']))
            # metrics.plot_confusion_matrix(model, self.X_test, self.y_test, cmap=plt.cm.Blues,
            #                               display_labels=['Bullish', 'Bearish'])
            #
            # plt.savefig(self.img_path + f"/{self.ticker}_{self.opt_mod}_Results")
            # plt.show()
            print(
                "Skipping Result print to console due to assignment submission...uncomment lines above 348 to observe output!")

    def get_metrics(self, model_name):
        """
        A function to obtain classification result metrics
        :param model_name: a string denoting the name of the ML model
        """
        self.metrics[model_name] = {"Accuracy": metrics.accuracy_score(self.y_test, self.y_pred[model_name]),
                                    "F1 Score": metrics.f1_score(self.y_test, self.y_pred[model_name]),
                                    "Precision": metrics.precision_score(self.y_test, self.y_pred[model_name]),
                                    "Recall": metrics.recall_score(self.y_test, self.y_pred[model_name]),
                                    "ROC AUC Score": metrics.roc_auc_score(self.y_test, self.y_pred[model_name])}
        print(f"{self.ticker} metrics successfully complete!")

    def run_models(self):
        """
        A function to run all the ML models and choose the optimal one among them
        :return: A Series object displaying all the classification stats of the forecast
        """
        # print("Running LR...")
        # self.get_LR()
        # print("Running KNN...")
        # self.get_KNN()
        print("Running SVC...")
        self.get_SVC()
        print("Running RF...")
        self.get_RF()
        # print("Running NN...")
        # self.get_NN()
        print("Creating Metrics Table")
        for model_name in self.y_pred:
            self.get_metrics(model_name)

        # get optimal model based on F1-Score
        opt_stats = self.get_optimal_model("F1 Score")
        # store optimal model
        self.opt_mod = opt_stats.name

        print("Displaying Report for Optimal Model:\n\n")
        self.get_report(self.models[self.opt_mod], self.opt_mod)

        # change name to ticker
        opt_stats.name = self.ticker
        return opt_stats

    def get_optimal_model(self, metric_name):
        """
        A function to obtain the optimal model
        :param metric_name: a string denoting the classification metric name
        :return: the optimal model series based on the metric name
        """
        self.metrics = pd.DataFrame(self.metrics)
        return self.metrics.iloc[:, self.metrics.loc[metric_name, :].argmax()]

    def plot_nn_report(self,
                       cm,
                       classes,
                       cmap=plt.cm.Blues):
        """
        A function to plot the truth table of the the NN output
        :param cm: confusion matrix output from model
        :param classes: target variable classes
        :param cmap: the color map of the truth table
        """
        import itertools
        plt.imshow(cm, interpolation='nearest', cmap=cmap)
        plt.colorbar()
        tick_marks = np.arange(len(classes))
        plt.xticks(tick_marks, classes)
        plt.yticks(tick_marks, classes)

        print(cm)

        thresh = cm.max() / 2

        for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
            plt.text(j, i, cm[i, j],
                     horizontalalignment="center",
                     color="white" if cm[i, j] > thresh else "black")

        plt.tight_layout()
        plt.savefig(self.img_path + f"/{self.ticker}_NN_Results")
        plt.show()


if __name__ == "__main__":
    # Initializing Variables
    start_date = "2000-01-01"
    end_date = "2021-11-12"

    # Obtain Sample Stock Data and run the algorithm
    #
    # print("Obtaining sample stock data...")
    # sample_tickers = pd.read_csv("tickers.csv")['Ticker']
    # sample_results = pd.DataFrame()
    # print("Running algo on sample stock data...")
    # for stock in sample_tickers:
    #     print(f"\nStock: {stock}\n")
    #     try:
    #         SP = StockPredictor(start_date, end_date, stock, "small")
    #         sample_results = pd.concat([sample_results, SP.opt_stats], axis=1)
    #     except:
    #         print(f"Skipping {stock} due to error!")
    #         continue
    #
    # # Save results to csv
    # print("Saving results to csv...")
    # sample_results.T.to_csv("sample_results.csv")

    # Obtain Large Sample Stock Data and run the algorithm

    print("Obtaining large sample of stock data...")
    # large_sample_tickers = pd.read_pickle("sp500tickers.pickle")
    df1 = pd.read_csv("tickers_nasd.csv")
    df2 = pd.read_csv("tickers_nyse.csv")
    df = pd.concat([df1, df2], axis=0)

    # Sort large dataset by market cap and obtain top 100 stocks
    df = df.sort_values(by=['MarketCap'], ascending=False)
    large_sample_tickers = df['Symbol'][:250]

    large_sample_results = pd.DataFrame()
    print("Running algo on large sample stock data...")
    for stock in large_sample_tickers:
        print(f"\nStock: {stock}\n")
        try:
            SP = StockPredictor(start_date, end_date, stock, "large")
            large_sample_results = pd.concat([large_sample_results, SP.opt_stats], axis=1)
        except:
            print(f"Skipping {stock} due to error!")
            continue

    # Sort results based on F1 Score and save results to csv
    large_sample_results = large_sample_results.T.sort_values(by=['F1 Score'], ascending=False)
    print("Saving results to csv...")
    large_sample_results.to_csv("large_sample_results.csv")
    large_sample_results[:20].to_csv("Top20_large_sample_results.csv")
