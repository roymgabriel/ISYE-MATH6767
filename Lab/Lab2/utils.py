import pandas as pd
from datetime import datetime
import matplotlib.pyplot as plt

class helper_functions:
    def __init__(self, filepath: str):
        self.filepath = filepath
        
    def load_csv(self):
        cols = ['contractSymbol', 'strike', 'lastPrice', 'impliedVolatility', 'bid', 'ask']
        return pd.read_csv(self.filepath, usecols=cols)

    def slice_df(self, df: pd.DataFrame, start_K: float, end_K: float):
        return df[(df['strike'] >= start_K) & (df['strike'] <= end_K)]

    def manipulate_string(self, s: str):
        if 'C' in s:
            return s.split("SPY")[1].split("C")[0]
        else:
            return s.split("SPY")[1].split("P")[0]

    def get_option_type(self, df: pd.DataFrame):
        df['option_type'] = df['contractSymbol'].apply(lambda x: "C" if "C" in x else "P")
        return df

    def get_T(self, df: pd.DataFrame)-> pd.DataFrame:
        df['T'] = df['contractSymbol'].apply(self.manipulate_string)
        df['T'] = pd.to_datetime(df['T'], format="%y%m%d")
        df['T'] = df['T'].apply(lambda x: abs(x - datetime.today()).days / 252)
        return df



    def get_mid(self, df: pd.DataFrame):
        df['mid'] = (df['bid'] + df['ask']) / 2
        return df

    def expand_df(self, df:pd.DataFrame, start_K, end_K):
        df = self.slice_df(df, start_K, end_K)
        df = self.get_option_type(df)
        df = self.get_T(df)
        df = self.get_mid(df)
        return df

    def plot_smile(self, df: pd.DataFrame):
        plt.figure(figsize=(16, 9))
        plt.plot(df['strike'], df['vol'], label='Calculated IV')
        plt.plot(df['strike'], df['impliedVolatility'], label='True IV')
        plt.title("Volatility Smile/Skew of Options with Same Expiration")
        plt.xlabel("Strike")
        plt.ylabel("Implied Volatility")
        plt.legend()
        plt.savefig("Vol_Smile")
        plt.show()
    

