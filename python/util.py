ema=[];
def exponentialMovingAverage(s,i,period):
    roi = s[:period]
    sma = sum(roi)/len(roi)
    multiplier = (2/(period+1))

def simpleMovingAverage(s,i,period):
    roi = s[i:i+period]
    return sum(roi)/len(roi)


