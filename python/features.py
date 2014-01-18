from urllib2 import urlopen, URLError

GET_HISTORY = "http://ichart.finance.yahoo.com/table.csv?s={0}"

COMMON_EMAS

class StockFeatureExtractor:
    def __init__(self,ticker_symbol):
        responseText = [tuple(j for j in i.split(",")) for i in (urlopen(GET_HISTORY.format(ticker_symbol), timeout=0.5).read().strip().split()[2:])]
        self.data={}
        for date,opn,high,low,close,volume,adjClose in responseText:
            key = date(*(int(i) for i in date.split("-")))
            self.data[key]={
                "open":float(opn),
                "high":float(high),
                "low":float(low),
                "close":float(close),
                "volume":float(volume),
                "adjClose":float(adjClose),
                "ema":{},
            }


StockFeatureExtractor("goog")
