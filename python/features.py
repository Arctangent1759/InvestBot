from urllib2 import urlopen, URLError
import datetime

GET_HISTORY = "http://ichart.finance.yahoo.com/table.csv?s={0}"


class StockFeatureExtractor:
    COMMON_EMAS = [8,12,26,50,200]
    SMOOTHING_FACTORS = {i:(2.0/(1.0+i),1.0-(2.0/(1.0+i))) for i in COMMON_EMAS}
    def __init__(self,ticker_symbol):
        responseText = [tuple(j for j in i.split(",")) for i in (urlopen(GET_HISTORY.format(ticker_symbol), timeout=0.5).read().strip().split()[2:])]
        self.data={}
        self.dateList=[]
        self.lastUpdate = datetime.date.today()

        prev_emas={}

        count = 0
        for i in reversed(xrange(len(responseText))):
            date,opn,high,low,close,volume,adjClose = responseText[i]
            key = datetime.date(*(int(j) for j in date.split("-")))
            self.data[key]={
                "open":float(opn),
                "close":float(close),
                "high":float(high),
                "low":float(low),
                "volume":float(volume),
                "adjClose":float(adjClose),
                "ema":{},
                "sma":{},
            }
            self.dateList.append(key)
            for per in self.COMMON_EMAS:
                mult = self.SMOOTHING_FACTORS[per]
                arrSlice = [float(j[-1]) for j in responseText[i:min(i+per,len(responseText))]]
                sma=float(sum(arrSlice))/len(arrSlice)
                if count >= per:
                    ema = mult[1]*prev_emas[per] + mult[0] * float(adjClose)
                else:
                    ema = sma
                prev_emas[per] = ema
                self.data[key]["ema"][per]=ema
                self.data[key]["sma"][per]=sma
            count+=1

    def update(self):
        if datetime.date.today()!=self.lastUpdate:
            self.__init__();

    def getParam(self, date, param):
        while date not in self.data:
            date-=datetime.timedelta(1)
        return self.data[date][param]
    
    def getOpen(self, date):
        return self.getParam(date,"open")

    def getClose(self, date):
        return self.getParam(date,"close")

    def getHigh(self, date):
        return self.getParam(date,"high")

    def getLow(self, date):
        return self.getParam(date,"low")

    def getVolume(self, date):
        return self.getParam(date,"volume")

    def getAdjClose(self, date):
        return self.getParam(date,"adjClose")

    def getEmas(self,date):
        return self.getParam(date,"ema")

    def getSmas(self,date):
        return self.getParam(date,"sma")

    def getEma(self,date,num):
        return self.getParam(date,"ema")[num]

    def getSma(self,date,num):
        return self.getParam(date,"sma")[num]

    def __str__(self):
        out=""
        for date in self.dateList:
            data = self.data[date]
            out += "{0} {1} {2}\n".format(data["adjClose"],data["sma"][200],data["ema"][200])
        return out;

s = StockFeatureExtractor("goog")
print s.getEmas(datetime.date.today())
print s.getSmas(datetime.date.today())
