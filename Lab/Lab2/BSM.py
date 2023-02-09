import numpy as np
from scipy.stats import norm

class BSM:
    def __init__(self, S=100, K=100, T=0.1, r=0.04, option_type="C"):
        self.S = S
        self.K = K
        self.T = T
        self.r = r
        # self.vol = vol
        self.option_type = option_type
        self.N = norm.cdf

    def price_option(self, vol):
        self.d1 = (np.log(self.S / self.K) + (self.r + (vol ** 2) / 2) * self.T) / (vol * np.sqrt(self.T))
        self.d2 = self.d1 - vol * np.sqrt(self.T)

        if self.option_type.upper() == "C":
            return self.S * self.N(self.d1) - self.K * np.exp(-self.r * self.T)* self.N(self.d2)
        elif self.option_type.upper() == "P":
            return self.K * np.exp(-self.r * self.T) * self.N(-self.d2) - self.S * self.N(-self.d1)
        else:
            raise ValueError(f"Option Type Input {self.option_type} is incorrect! Must be 'c' or 'p'")

    def get_iv(self, true_option_price):
        # Initialize volatility vector
        v = np.arange(0.01, 0.99, 0.001)

        # initialize local minima
        temp_min = 999999
        for vol in v:
            OP = self.price_option(vol)
            if abs(true_option_price - OP) < temp_min:
                temp_vol = vol
                temp_min = abs(true_option_price - OP)

        return temp_vol

    # def get_iv(self, S, K, r, T, option_type, error_tolerance = 0.00001, epochs = 200, start_vol = 0., end_vol = 0.4):
    #     for i in range(epochs):
    #         bsm_high = BSM(S=S, K=K, r=r, T=T, vol=end_vol, option_type=option_type)
    #         bsm_low = BSM(S=S, K=K, r=r, T=T, vol=start_vol, option_type=option_type)
    #
    #         upper_bound = bsm_high.price_option()
    #         lower_bound = bsm_low.price_option()
    #
    #         vol = start_vol + (S - lower_bound) * ((end_vol - start_vol) / (upper_bound - lower_bound))
    #         bsm = BSM(S=S, K=K, r=r, T=T, vol=vol, option_type=option_type)
    #         new_price = bsm.price_option()
    #
    #         if end_vol - start_vol < error_tolerance:
    #             return vol
    #         elif (new_price >= S):
    #             end_vol = vol
    #         else:
    #             start_vol = vol
    #     return vol



