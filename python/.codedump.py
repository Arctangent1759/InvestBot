from getcodes import GETCODES
GETPRICE_TEMPLATE = "http://download.finance.yahoo.com/d/quotes.csv?s={0}&f={1}"

def getParam(ticker_symbol,code):
    try:
        return [float(urlopen(GETPRICE_TEMPLATE.format(ticker_symbol,GETCODES[code]), timeout=0.5).read())]
    except URLError, ValueError:
        return [None]

def getCurrPrice(ticker_symbol):
    return getParam(ticker_symbol,"LastTrade(PriceOnly)")

def get200DayMovingAverage(ticker_symbol):
    return getParam(ticker_symbol,"200-dayMovingAverage")

def get50DayMovingAverage(ticker_symbol):
    return getParam(ticker_symbol,"50-dayMovingAverage")
