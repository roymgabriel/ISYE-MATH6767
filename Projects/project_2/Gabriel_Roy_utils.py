import pandas as pd
import numpy as np

# create TA indicators

def get_SMA(close, window):
    """
    A function to calculate the Simple Moving Average
    :param close: close price series
    :param window: moving window
    :return: the Simple Moving Average mean
    """
    return close.rolling(window).mean()

def get_BB(close, window=10, width=1.5):
    """
    A function to calculate Bollinger Bands
    :param close: close price series
    :param window: moving window
    :param width: bollinger band width
    :return: Bollinger Band indicators
    """
    sma = get_SMA(close, window)
    p_std = close.rolling(window).std()
    b_up = sma + p_std * width
    b_down = sma - p_std * width
    return sma, b_up, b_down

def get_ADX(high, low, close, lb=10):
    """
    A function to calculate Average Directional Index
    :param high: high price series
    :param low: low price series
    :param close: close price series
    :param lb: rolling window
    :return: ADX results
    """
    dm_plus = high.diff()
    dm_minus = low.diff()
    dm_plus[dm_plus < 0] = 0
    dm_minus[dm_minus > 0] = 0

    tr1 = pd.DataFrame(high - low)
    tr2 = pd.DataFrame(abs(high - close.shift(1)))
    tr3 = pd.DataFrame(abs(low - close.shift(1)))
    frames = [tr1, tr2, tr3]
    tr = pd.concat(frames, axis = 1, join = 'inner').max(axis = 1)
    atr = tr.rolling(lb).mean()

    plus_di = 100 * (dm_plus.ewm(alpha = 1/lb).mean() / atr)
    minus_di = abs(100 * (dm_minus.ewm(alpha = 1/lb).mean() / atr))
    dx = (abs(plus_di - minus_di) / abs(plus_di + minus_di)) * 100
    adx = ((dx.shift(1) * (lb - 1)) + dx) / lb
    adx_smooth = adx.ewm(alpha = 1/lb).mean()
    return plus_di, minus_di, adx_smooth

def get_MACD(close, span=10, min_p=10):
    """
    A function to calculate Moving Average Convergence Divergence
    :param close: close price series
    :param span: moving window for exponential weighted moving average
    :param min_p: minimum periods
    :return: MACD results
    """
    k = close.ewm(span=span, adjust=False, min_periods=min_p).mean()
    d = close.ewm(span=span*2, adjust=False, min_periods=min_p*2).mean()
    macd = k-d
    macd_s = macd.ewm(span=span-1, adjust=False, min_periods=min_p-1).mean()
    macd_h = macd - macd_s
    return macd, macd_h, macd_s

def get_RSI(close, periods = 10):
    """
    A function to calculate Relative Strength Index
    :param close: close price series
    :param periods: window for EWM
    :return: RSI results
    """
    prc_chg = np.log(close).diff()
    up = prc_chg.clip(lower=0)
    down = -prc_chg.clip(upper=0)
    ma_up = up.ewm(com = periods - 1, adjust=True, min_periods = periods).mean()
    ma_down = down.ewm(com = periods - 1, adjust=True, min_periods = periods).mean()
    rsi = ma_up / ma_down
    rsi = 100 - (100/(1 + rsi))
    return rsi

def get_ATR(high, low, close, window=10):
    """
    A function to calculate Average True Range
    :param high: high price series
    :param low: low price series
    :param close: close price series
    :param window: moving window
    :return: ATR results
    """
    HML = high - low
    HMC = np.abs(high - close.shift())
    LMC = np.abs(low - close.shift())
    TR = np.max(pd.concat([HML, HMC, LMC], axis=1), axis=1)
    ATR = TR.rolling(window).sum()/window
    return ATR

def get_PIVOT(high, low, close):
    """
    A function to calculate Pivot Points
    :param high: high price series
    :param low: low price series
    :param close: close price series
    :return: pivot points results
    """
    pivot = (high + low + close) / 3
    r1 = 2*pivot - low
    s1 = 2*pivot - high
    r2 = pivot + high - low
    s2 = pivot - high + low
    r3 = pivot + 2*(high - low)
    s3 = pivot - 2*(high - low)
    return pivot, r1, s1, r2, s2, r3, s3

