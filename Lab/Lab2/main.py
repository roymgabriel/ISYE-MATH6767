from BSM import BSM
from utils import helper_functions
import pandas_datareader as pdr

def main():
    print("Read CSV file...")
    # Initialize necessary variables
    filepath = "./spy_options.csv"
    print("Done!\n")
    print("Initializing Variables:")
    start_K, end_K = 250.0, 500.0
    r = 0.0366  # 1-month risk free rate
    S = pdr.get_data_yahoo("SPY")['Adj Close'][-1] # pulls latest SPY price
    print(f"start_K: {start_K}, end_K: {end_K}, r={r}, S={S}\n")

    print("Manipulating DataFrame...")
    # Use imported classes to get data and manipulate it
    hf = helper_functions(filepath=filepath)
    df = hf.load_csv()
    df = hf.expand_df(df, start_K, end_K)

    for i in range(df.shape[0]):
    # create BSM class with new parameters
        K = df.loc[i, 'strike']
        T = df.loc[i, 'T']
        option_type = df.loc[i, 'option_type']
        bsm = BSM(S=S, K=K, r=r, T=T, option_type=option_type)

        # get underlying option price to reverse engineer iv
        true_option_price = float(df.loc[i, 'mid'])

        # get IV
        df.loc[i, 'vol'] = bsm.get_iv(true_option_price)

    print("Printing DataFrame:\n")
    print(df)

    print("Visualizing volatility smiles...\n")
    hf.plot_smile(df)

if  __name__ == "__main__":
    main()